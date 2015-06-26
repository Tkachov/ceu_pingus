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

#include "pingus/worldobjs/spike.hpp"

#include "engine/display/scene_context.hpp"

#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"

#include "ceuvars.h"

namespace WorldObjs {

Spike::Spike (const FileReader& reader) :
  surface("traps/spike")
{
  reader.read_vector("position", pos);

  Spike* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_SPIKE, &self);
}

Spike::~Spike() {
  Spike* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_SPIKE, &self);
}


} // namespace WorldObjs

/* EOF */
