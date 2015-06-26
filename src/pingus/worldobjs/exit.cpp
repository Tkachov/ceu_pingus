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

#include "pingus/worldobjs/exit.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/collision_map.hpp"

#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"
#include "util/string_util.hpp"

#include "ceuvars.h"

namespace WorldObjs {

Exit::Exit(const FileReader& reader) :
  desc(),  
  owner_id(),
  sprite(),
  flag(),
  smallmap_symbol("core/misc/smallmap_exit")
{
  reader.read_vector("position", pos);
  reader.read_desc  ("surface",  desc);
  reader.read_int   ("owner-id", owner_id);

  // Set default owner ID to 0
  if (owner_id < 0 || owner_id > 3) owner_id = 0;

  flag = Sprite("core/misc/flag" + StringUtil::to_string(owner_id));

  sprite = Sprite(desc);

  Exit* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_EXIT, &self);
}

Exit::~Exit() {
  Exit* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_EXIT, &self);
}

void
Exit::on_startup ()
{
  CollisionMask mask(desc);
  world->get_colmap()->remove(mask,
                              static_cast<int>(pos.x) - sprite.get_width()/2,
                              static_cast<int>(pos.y) - sprite.get_height());
}

} // namespace WorldObjs

/* EOF */
