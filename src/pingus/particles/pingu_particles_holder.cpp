#include "pingus/particles/pingu_particles_holder.hpp"
#include "engine/display/scene_context.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/world.hpp"

namespace Particles {

void PinguParticleHolder_add_particle(std::vector<PinguParticle>* particles, int x, int y) {
    int i = 0;

    // fill gaps from dead entries
    for (std::vector<PinguParticle>::iterator it=particles->begin(); it != particles->end(); ++it) {
        if(!it->livetime) {
            *it = PinguParticle(x, y);
            ++i;
        }
    }

    // allocate space for all remaining particles at once
    particles->reserve(particles->size() + 50 - i);

    // create remaining entries
    for (; i < 50; ++i)
        particles->push_back(PinguParticle(x, y));
}

void PinguParticleHolder_update(std::vector<PinguParticle>* particles, World* world) {
    const float x_collision_decrease = 0.3f;
    const float y_collision_decrease = 0.6f;

  // update all contained particles
  for(std::vector<PinguParticle>::iterator it=particles->begin(); it != particles->end(); ++it) {
    // skip dead particles
    if(!it->livetime) continue;

    float tmp_x_add = 0.0f;
    float tmp_y_add = 0.0f;

    // Simulated gravity
    it->velocity.y += world->get_gravity();

    if (it->velocity.y > 0)
    {
      for (tmp_y_add = it->velocity.y; tmp_y_add >= 1.0; --tmp_y_add)
      {
        if (world->get_colmap()->getpixel(static_cast<int>(it->pos.x), static_cast<int>(it->pos.y)))
        {
          it->velocity.y *= -y_collision_decrease;
          tmp_y_add = -tmp_y_add;
          --it->pos.y;
          break;
        }
        ++it->pos.y;
      }
      it->pos.y += tmp_y_add;
    }
    else
    {
      for (tmp_y_add = it->velocity.y; tmp_y_add <= -1.0; ++tmp_y_add)
      {
        if (world->get_colmap()->getpixel(static_cast<int>(it->pos.x), static_cast<int>(it->pos.y)))
        {
          it->velocity.y *= -y_collision_decrease;
          tmp_y_add = -tmp_y_add;
          ++it->pos.y;
          break;
        }
        --it->pos.y;
      }
      it->pos.y += tmp_y_add;
    }

    if (it->velocity.x > 0)
    {
      for (tmp_x_add = it->velocity.x; tmp_x_add >= 1.0; --tmp_x_add)
      {
        if (world->get_colmap()->getpixel(static_cast<int>(it->pos.x), static_cast<int>(it->pos.y)))
        {
          it->velocity.x *= -x_collision_decrease;
          tmp_x_add = -tmp_x_add;
          --it->pos.x;
          break;
        }
        ++it->pos.x;
      }
      it->pos.x += tmp_x_add;
    }
    else
    {
      for (tmp_x_add = it->velocity.x; tmp_x_add <= -1.0; ++tmp_x_add)
      {
        if (world->get_colmap()->getpixel(static_cast<int>(it->pos.x), static_cast<int>(it->pos.y)))
        {
          it->velocity.x *= -x_collision_decrease;
          tmp_x_add = -tmp_x_add;
          ++it->pos.x;
          break;
        }
        --it->pos.x;
      }
      it->pos.x += tmp_x_add;
    }

    --it->livetime;
  }
}

void PinguParticleHolder_draw(std::vector<PinguParticle>* particles, SceneContext* gc, Sprite* surface) {
    for(auto it: *particles) {
        // skip dead particles
        if(!it.livetime) continue;

        gc->color().draw(*surface, it.pos);
    }
}

}