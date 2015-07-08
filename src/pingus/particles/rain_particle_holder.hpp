#ifndef RAIN_PARTICLE_HOLDER_HPP
#define RAIN_PARTICLE_HOLDER_HPP

#include <vector>

#include "engine/display/sprite.hpp"
#include "math/vector3f.hpp"
#include "pingus/world.hpp"
#include "engine/display/scene_context.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/globals.hpp"

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

#endif
