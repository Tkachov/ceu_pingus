#ifndef SNOW_PARTICLE_HOLDER_HPP
#define SNOW_PARTICLE_HOLDER_HPP

#include <vector>

#include "engine/display/sprite.hpp"
#include "math/vector3f.hpp"
#include "pingus/collision_mask.hpp"
#include "engine/display/scene_context.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/ground_map.hpp"
#include "pingus/world.hpp"

enum ParticleType { Snow1, Snow2, Snow3, Snow4, Snow5 };

struct SnowParticle {
  bool         alive;
  bool         colliding;
  ParticleType type;
  Vector3f       pos;
  Vector3f       velocity;

  SnowParticle(int x, int y, bool colliding_):
    alive(true),
    colliding(colliding_),
    type(Snow1),
    pos(Vector3f(x, y)),
    velocity(Vector3f(0.0f, 1 + (Math::frand() * 3.5f)))
  {
    switch (rand() % 10)
    {
      case 0:
        type = Snow1;
        break;
      case 1:
        type = Snow2;
        break;
      case 2:
      case 3:
        type = Snow3;
        break;
      case 5:
      case 6:
        type = Snow4;
      default:
        type = Snow5;
        break;
    }
  }
};

#endif