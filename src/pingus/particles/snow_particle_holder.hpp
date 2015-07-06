#ifndef SNOW_PARTICLE_HOLDER_HPP
#define SNOW_PARTICLE_HOLDER_HPP

#include <vector>

#include "engine/display/sprite.hpp"
#include "math/vector3f.hpp"
#include "pingus/collision_mask.hpp"

class SceneContext;
class World;

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

namespace Particles {
  void SnowParticleHolder_add_particle(std::vector<SnowParticle>* particles, int x, int y, bool colliding);
  void SnowParticleHolder_update(std::vector<SnowParticle>* particles, World* world, CollisionMask* ground);
  void SnowParticleHolder_draw(std::vector<SnowParticle>* particles, SceneContext* gc, Sprite* snow1, Sprite* snow2, Sprite* snow3, Sprite* snow4, Sprite* snow5);
}

#endif