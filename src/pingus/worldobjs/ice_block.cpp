//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include "pingus/worldobjs/ice_block.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"
#include "util/log.hpp"

#include "ceuvars.h"

namespace WorldObjs {

IceBlock::IceBlock(const FileReader& reader) :  
  width(),
  block_sur("worldobjs/iceblock"),
  block_sur_cmap("worldobjs/iceblock_cmap")
{
  reader.read_vector("position", pos);
  if (!reader.read_int("repeat", width))
  {
    log_warn("old 'width' tag used");
    reader.read_int("width", width); 
  }

  IceBlock* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_ICE_BLOCK, &self);
}

IceBlock::~IceBlock() {
  IceBlock* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_ICE_BLOCK, &self);
}

void
IceBlock::on_startup ()
{
  world->put(block_sur_cmap,
             static_cast<int>(pos.x),
             static_cast<int>(pos.y),
             Groundtype::GP_GROUND);
}

} // namespace WorldObjs

/* EOF */
