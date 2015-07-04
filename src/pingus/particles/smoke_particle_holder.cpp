#include "pingus/particles/smoke_particle_holder.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/globals.hpp"
#include "pingus/world.hpp"

namespace Particles {

void SmokeParticleHolder_add_particle(std::vector<SmokeParticle>* particles, float x, float y, float vel_x, float vel_y) {
  // search for dead entry to replace
  for (std::vector<SmokeParticle>::iterator it=particles->begin(); it != particles->end(); ++it)
    if (!it->livetime)
    {
      *it = SmokeParticle(x, y, vel_x, vel_y);
      return;
    }

  // create new entry
  particles->push_back(SmokeParticle(x, y, vel_x, vel_y));
}

void SmokeParticleHolder_update(std::vector<SmokeParticle>* particles) {
  // update all contained particles
  for (std::vector<SmokeParticle>::iterator it=particles->begin(); it != particles->end(); ++it)
  {
    // skip dead particles
    if (!it->livetime)
      continue;

    it->pos.x += it->velocity.x;
    it->pos.y += it->velocity.y;
    it->pos.z = 1000; //z pos

    --it->livetime;
  }
}

void SmokeParticleHolder_draw(std::vector<SmokeParticle>* particles, SceneContext* gc, Sprite* surf1, Sprite* surf2) {
  for (std::vector<SmokeParticle>::iterator it=particles->begin(); it != particles->end(); ++it)
  {
    if (!it->livetime)
      continue;

    if (!it->use_surf2)
      gc->color().draw(*surf1, it->pos);
    else
      gc->color().draw(*surf2, it->pos);
  }
}

} // namespace Particles

/* EOF */
