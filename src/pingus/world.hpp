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

#ifndef HEADER_PINGUS_PINGUS_WORLD_HPP
#define HEADER_PINGUS_PINGUS_WORLD_HPP

#include <string>
#include <vector>

#include "math/vector2i.hpp"
#include "pingus/collision_mask.hpp"
#include "pingus/groundtype.hpp"

class Vector3f;
class GroundMap;
class PinguHolder;
class PingusLevel;
class CollisionMap;
class Pingu;
class SceneContext;

class World;

/** The World holds all objects of the pingu enviroment.

    It holds the pingus, traps, exits, entrances, etc.. It keeps
    control that all objects become time to move and can catch each
    other. */
class World
{
private:
  Color ambient_light;

  /** groundmap for the pingus */
  GroundMap* gfx_map;

  int mwidth, mheight;

  /** manager class for the time in the pingus world */
  int game_time;
    
  PinguHolder* pingus;

  // Pointers which are references to objects from other classes
  CollisionMap* colmap;

  void init_worldobjs(const PingusLevel& plf);

  /** Acceleration due to gravity in the world */
  const float gravitational_acceleration;

public:
  World(const PingusLevel& level);
  virtual ~World();

  /** Returns the time passed since the level was started */
  int get_time();

  /** @return A pointer to the collision map used in this world */
  CollisionMap* get_colmap();

  /** @return A pointer to the gfx map used in this world */
  GroundMap* get_gfx_map();

  PinguHolder* get_pingus(void);

  /** Get the acceleration due to gravity in the world */
  float get_gravity();

private:
  World (const World&);
  World& operator= (const World&);
};

struct WorldGetSizePackage {
  World* world;
  int width, height;

  WorldGetSizePackage(World* w): world(w) {};
};

#endif

/* EOF */
