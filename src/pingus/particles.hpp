#ifndef PARTICLES_HPP
#define PARTICLES_HPP

#include <vector>

#include "engine/display/scene_context.hpp"
#include "engine/display/sprite.hpp"
#include "math/vector3f.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/collision_mask.hpp"
#include "pingus/globals.hpp"
#include "pingus/ground_map.hpp"

////// PINGU

struct PinguParticle {
    int  livetime;
    bool use_frame2;
    /// The current position of the particle
    Vector3f pos;

    /// The velocity of the particle
    Vector3f velocity;

    PinguParticle (int x, int y):
        livetime(50 + (rand() % 75)),
        use_frame2((rand() % 5) == 0),
        pos(Vector3f(x, y)),
        velocity(Vector3f(Math::frand() * 7 - 3.5f, Math::frand() * -9))
    {}
};

////// RAIN

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

////// SMOKE

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

////// SNOW

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
