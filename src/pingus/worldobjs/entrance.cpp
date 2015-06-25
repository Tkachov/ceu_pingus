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

#include "pingus/worldobjs/entrance.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"
#include "util/log.hpp"

#include "ceuvars.h"

namespace WorldObjs {

Entrance::Entrance(const FileReader& reader) :
  direction(MISC),  
  release_rate(150),
  owner_id(0),
  smallmap_symbol("core/misc/smallmap_entrance"),
  surface()
{
  reader.read_int   ("owner-id",     owner_id);
  reader.read_vector("position",     pos);
  reader.read_int   ("release-rate", release_rate);

  // Set default owner ID to 0
  if (owner_id < 0 || owner_id > 3) owner_id = 0;

  std::string direction_str;
  reader.read_string("direction", direction_str);

  if (direction_str == "left")
    direction = LEFT;
  else if (direction_str == "right")
    direction = RIGHT;
  else if (direction_str == "misc")
    direction = MISC;
  else
  {
    log_error("unknown direction: '%1%'", direction_str);
    direction = MISC;
  }

  Entrance* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_ENTRANCE, &self);
}

Entrance::~Entrance() {
  Entrance* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_ENTRANCE, &self);
}

} // namespace WorldObjs

/* EOF */
