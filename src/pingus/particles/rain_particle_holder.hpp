#ifndef RAIN_PARTICLE_HOLDER_HPP
#define RAIN_PARTICLE_HOLDER_HPP

#include <vector>

#include "engine/display/sprite.hpp"
#include "math/vector3f.hpp"
#include "pingus/world.hpp"

struct RainParticle {
  bool  alive;
  bool  splash;
  bool  use_rain2_surf;
  int   splash_counter;
  float splash_frame;

  // pos.z contains a modificator for x and y pos
  Vector3f pos;

  RainParticle(int x, int y):
    alive(true),
    splash(false),
    use_rain2_surf(false),
    splash_counter(0),
    splash_frame(0),
    pos(Vector3f(x, y))
  {
    use_rain2_surf = ((rand() % 3) == 0);
    pos.z = 1.0f + Math::frand() * 3.0f;
  }
};

namespace Particles {
  void RainParticleHolder_add_particle(std::vector<RainParticle>* particles, int x, int y);
  void RainParticleHolder_update(std::vector<RainParticle>* particles, World* world, Sprite* s3);
  void RainParticleHolder_draw(std::vector<RainParticle>* particles, World* world, SceneContext* gc, Sprite* s1, Sprite* s2, Sprite* s3);
}

#endif
