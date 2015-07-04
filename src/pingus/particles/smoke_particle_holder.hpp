#ifndef SMOKE_PARTICLE_HOLDER_HPP
#define SMOKE_PARTICLE_HOLDER_HPP

#include <vector>

#include "engine/display/sprite.hpp"
#include "engine/display/scene_context.hpp"
#include "math/vector3f.hpp"

struct SmokeParticle {
  int    time;
  int    livetime;
  bool   use_surf2;
  Vector3f pos;
  Vector3f velocity;

  SmokeParticle (float x, float y, float vel_x, float vel_y):
    time(),
    livetime(),
    use_surf2(),
    pos(Vector3f(x, y)), 
    velocity(Vector3f(vel_x, vel_y))
  {
    time = livetime = 25 + (rand() % 10);
    use_surf2 = rand() % 2;
  }
};

namespace Particles {
  void SmokeParticleHolder_add_particle(std::vector<SmokeParticle>* particles, float x, float y, float vel_x, float vel_y);
  void SmokeParticleHolder_update(std::vector<SmokeParticle>* particles);
  void SmokeParticleHolder_draw(std::vector<SmokeParticle>* particles, SceneContext* gc, Sprite* s1, Sprite* s2);
}

#endif
