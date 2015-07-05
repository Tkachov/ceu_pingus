//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "pingus/world.hpp"

#include <algorithm>

#include "engine/display/scene_context.hpp"
#include "engine/sound/sound.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/ground_map.hpp"
#include "pingus/particles/snow_particle_holder.hpp"

#include "pingus/pingu_holder.hpp"
#include "pingus/pingus_level.hpp"
#include "pingus/worldobj_factory.hpp"
#include "util/log.hpp"

#include "ceuvars.h"

World::World(const PingusLevel& plf) :
  ambient_light(Color(plf.get_ambient_light())),
  mwidth(plf.get_size().width),
  mheight(plf.get_size().height),
  game_time(0),
  do_armageddon(false),
  armageddon_count(0),  
  pingus(new PinguHolder(plf)),
  colmap(),
  gravitational_acceleration(0.2f)
{
  WorldObj::set_world(this);

  World* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_WORLD, &self);

  init_worldobjs(plf);
}

void World::init_worldobjs(const PingusLevel& plf) {
  const std::vector<FileReader>& objects = plf.get_objects();
  for(auto i: objects) WorldObjFactory::instance()->create(i);

  World* self = this;
  ceu_out_go(&CEUapp, CEU_IN_WORLD_STARTUP, &self);
}

World::~World() {
  World* self = this;  
  ceu_out_go(&CEUapp, CEU_IN_WORLD_DELETE, &self);
}

void World::draw(SceneContext& gc) {
  WorldDrawPackage package(this, &gc);
  WorldDrawPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_WORLD_DRAW, &pp);
}

void World::draw_smallmap(SmallMap* smallmap) {
  WorldDrawSmallmapPackage package(this, smallmap);
  WorldDrawSmallmapPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_WORLD_DRAW_SMALLMAP, &pp);
}

void World::update() {
  World* self = this;
  ceu_out_go(&CEUapp, CEU_IN_WORLD_UPDATE, &self);
}

PinguHolder*
World::get_pingus()
{
  return pingus;
}

int
World::get_width()
{
  assert(gfx_map);
  return gfx_map->get_width();
}

int
World::get_height()
{
  assert(gfx_map);
  return gfx_map->get_height();
}

int
World::get_time()
{
  return game_time;
}

void
World::armageddon(void)
{
  Sound::PingusSound::play_sound("goodidea");
  do_armageddon = true;
  armageddon_count = 0;
}

CollisionMap*
World::get_colmap()
{
  return colmap;
}

GroundMap*
World::get_gfx_map()
{
  return gfx_map;
}

void
World::play_sound(std::string name, const Vector3f& pos, float volume)
{
  // FIXME: Stereo is for the moment disabled
  /*
    Vector3f center = view->get_center();
    float panning = pos.x - center.x;
    panning /= view->get_width()/2;

    if (panning > 1.0f)
    panning = 1.0f;

    if (panning < -1.0f)
    panning = -1.0f;
  */
  float panning = 0.0f;

  Sound::PingusSound::play_sound(name, volume, panning);
}

float World::get_gravity()
{
  return gravitational_acceleration;
}

void
World::put(int x, int y, Groundtype::GPType p)
{
}

void
World::put(const CollisionMask& mask, int x, int y, Groundtype::GPType type)
{
  gfx_map->put(mask.get_surface(), x, y);
  colmap->put(mask, x, y, type);
}

void
World::remove(const CollisionMask& mask, int x, int y)
{
  gfx_map->remove(mask.get_surface(), x, y);
  colmap->remove(mask, x, y);
}

Vector2i
World::get_start_pos(int player_id)
{
  // FIXME: Workaround for lack of start-pos
  GetStartPosPackage package(this, player_id);
  GetStartPosPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_WORLD_GET_START_POS, &pp);
  return package.pos;
}

/* EOF */
