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

#include "pingus/pingus_level.hpp"
#include "pingus/worldobj_factory.hpp"
#include "util/log.hpp"

#include "ceuvars.h"

World::World(const PingusLevel& plf):
  pingus_level(plf),
  colmap(),
  gravitational_acceleration(0.2f)
{
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

float World::get_gravity()
{
  return gravitational_acceleration;
}

/* EOF */
