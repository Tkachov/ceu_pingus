//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "pingus/worldobjs/smasher.hpp"

#include <assert.h>

#include "engine/display/scene_context.hpp"
#include "engine/sound/sound.hpp"
#include "pingus/particles/smoke_particle_holder.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"
#include "util/log.hpp"

#include "ceuvars.h"

namespace WorldObjs {

Smasher::Smasher(const FileReader& reader) :
  sprite("traps/smasher"),
  pos()
{
  assert(sprite.get_frame_count() == 6);

  reader.read_vector("position", pos);

  Smasher* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_SMASHER, &self);
}

Smasher::~Smasher() {
  Smasher* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_SMASHER, &self);
}

float
Smasher::get_z_pos () const
{
  return pos.z;
}

void
Smasher::on_startup ()
{
  log_info("Drawing colmap entry");
  CollisionMask buf("traps/smasher_cmap");
  world->put(buf,
             static_cast<int>(pos.x),
             static_cast<int>(pos.y),
             Groundtype::GP_SOLID);
}

} // namespace WorldObjs

/* EOF */
