#ifndef PINGU_PARTICLES_HOLDER_HPP
#define PINGU_PARTICLES_HOLDER_HPP

#include <vector>

#include "engine/display/sprite.hpp"
#include "math/vector3f.hpp"

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

#endif
