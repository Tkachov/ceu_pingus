#include "pingus/particles/snow_particle_holder.hpp"
#include "engine/display/scene_context.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/ground_map.hpp"
#include "pingus/world.hpp"

namespace Particles {

void SnowParticleHolder_add_particle(std::vector<SnowParticle>* particles, int x, int y, bool colliding) {
  // search for dead entry to replace
  for (std::vector<SnowParticle>::iterator it=particles->begin(); it != particles->end(); ++it)
    if (!it->alive) {
      *it = SnowParticle(x, y, colliding);
      return;
    }

  // create new entry
  particles->push_back(SnowParticle(x, y, colliding));
}

void SnowParticleHolder_update(std::vector<SnowParticle>* particles, World* world, CollisionMask* ground) {
  // update all contained particles
  for(std::vector<SnowParticle>::iterator it=particles->begin(); it != particles->end(); ++it) {
    // skip dead particles
    if(!it->alive) continue;

    it->pos.x += it->velocity.x;
    it->pos.y += it->velocity.y;

    if(it->pos.y > world->get_height()) {
      it->alive = false;
      continue;
    }

    it->velocity.x += (Math::frand() - 0.5f) / 10;
    if(it->colliding) {
      int pixel = world->get_colmap()->getpixel(static_cast<int>(it->pos.x), static_cast<int>(it->pos.y));
      if(pixel != Groundtype::GP_NOTHING && pixel != Groundtype::GP_WATER && pixel != Groundtype::GP_OUTOFSCREEN) {
        world->get_gfx_map()->put(ground->get_surface(), static_cast<int>(it->pos.x - 1), static_cast<int>(it->pos.y - 1));
        it->alive = false;
      }
    }
  }
}

void SnowParticleHolder_draw(std::vector<SnowParticle>* particles, SceneContext* gc, Sprite* snow1, Sprite* snow2, Sprite* snow3, Sprite* snow4, Sprite* snow5) {
  for (std::vector<SnowParticle>::iterator it=particles->begin(); it != particles->end(); ++it)
  {
    if (!it->alive)
      continue;

    switch (it->type)
    {
      case Snow1:
        gc->color().draw(*snow1, it->pos);
        break;
      case Snow2:
        gc->color().draw(*snow2, it->pos);
        break;
      case Snow3:
        gc->color().draw(*snow3, it->pos);
        break;
      case Snow4:
        gc->color().draw(*snow4, it->pos);
        break;
      case Snow5:
        gc->color().draw(*snow5, it->pos);
        break;
      default:
        assert(!"Invalid Snow-Type");
    }
  }
}

} // namespace Particles
