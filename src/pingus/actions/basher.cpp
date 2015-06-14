//  Pingus - A free Lemmings clone
//  Copyright (C) 1999-2007 Ingo Ruhnke <grumbel@gmx.de>
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

#include "pingus/actions/basher.hpp"

#include "engine/display/scene_context.hpp"
#include "engine/sound/sound.hpp"
#include "pingus/globals.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_enums.hpp"
#include "pingus/world.hpp"
#include "pingus/worldobj.hpp"
#include "util/log.hpp"

namespace Actions {

Basher::Basher (Pingu* p) :
  PinguAction(p, ActionName::BASHER),  
  bash_radius("pingus/common/bash_radius_gfx", "pingus/common/bash_radius"),  
  first_bash(true),
  bash_reach()
{
  assert(bash_radius.get_width() % 2 == 0);

  //sprite loading was here

  bash_reach = bash_radius.get_width();

  // Start a bash even so the action will stops instantly after the
  // first bash
  bash();
}

void
Basher::bash()
{
  WorldObj::get_world()->remove(bash_radius,
                                pingu->get_xi() - bash_radius.get_width() / 2,
                                pingu->get_yi() - bash_radius.get_height() + 1);
}

bool
Basher::have_something_to_dig()
{
  if (first_bash)
  {
    first_bash = false;
    return true;
  }
  else
  {
    // Check that there is something "within" the Basher's reach
    for(int x = 0; x <= bash_reach; ++x)
    {
      for (int y = min_bash_height; y <= max_bash_height; ++y)
      {
        if (rel_getpixel(x, y) == Groundtype::GP_GROUND)
        {
          log_debug("Basher: Found something to dig...");
          return true;
        }
      }
    }

    return false;
  }
}

} // namespace Actions

/* EOF */
