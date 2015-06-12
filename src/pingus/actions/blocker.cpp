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

#include "pingus/actions/blocker.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"

namespace Actions {

void Blocker::catch_pingus() {
  // FIXME: PinguHolder iterations should be handled otherwise
  PinguHolder* pingus = WorldObj::get_world()->get_pingus();
  for(PinguIter i = pingus->begin(); i != pingus->end(); ++i)
    catch_pingu(*i);
}

bool
Blocker::standing_on_ground()
{
  return (rel_getpixel(0,-1) !=  Groundtype::GP_NOTHING);
}

void
Blocker::catch_pingu(Pingu* target)
{
  if (target != pingu) // avoid 'self' catch
  {
    if (target->get_x () > pingu->get_x () - 16
        && target->get_x () < pingu->get_x () + 16
        && target->get_y () > pingu->get_y () - 32
        && target->get_y () < pingu->get_y () + 5
      )
    {
      if (target->get_x () > pingu->get_x ()) {
        target->direction.right();
      } else {
        target->direction.left();
      }
    }
  }
}

} // namespace Actions

/* EOF */
