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

#include "pingus/pingu_action.hpp"

#include "pingus/collision_map.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_enums.hpp"
#include "pingus/action_name.hpp"
#include "pingus/world.hpp"
#include "pingus/worldobj.hpp"

#include "pingus/pingu_holder.hpp"

#include "ceuvars.h"

PinguAction::PinguAction(Pingu* p, ActionName::Enum t): pingu(p), type(t), name(ActionName::to_screenname(t)) {}

PinguAction::~PinguAction ()
{
}

void PinguAction::catch_pingus() {
  // FIXME: PinguHolder iterations should be handled otherwise ?
  PinguHolder* pingus = WorldObj::get_world()->get_pingus();
  for(PinguIter i = pingus->begin(); i != pingus->end(); ++i)
    catch_pingu(*i);
}

void PinguAction::catch_pingu(Pingu* p) {
  CatchedPingu catched;
  catched.action = this;
  catched.pingu = p;

  CatchedPingu* c = &catched;
  ceu_out_go(&CEUapp, CEU_IN_CATCH_PINGU, &c);
}

Vector3f PinguAction::get_center_pos() const {
  GetCenterPosPackage package(this, pingu->get_pos() + Vector3f(0, -16));
  GetCenterPosPackage* p = &package;
  ceu_out_go(&CEUapp, CEU_IN_ACTION_GET_CENTER_POS, &p);
  return p->result;
}

// Wrapper around the colmap, to get the pixels infront of the pingu,
// from is current position
int
PinguAction::rel_getpixel (int x, int y)
{
  // FIXME: Inline me
  return WorldObj::get_world()->get_colmap()->getpixel(static_cast<int>(pingu->get_x() + static_cast<float>((x * pingu->direction))),
                                                       static_cast<int>(pingu->get_y() - static_cast<float>(y)));
}

bool
PinguAction::head_collision_on_walk (int x, int y)
{
  int pixel = rel_getpixel(x, y + pingu_height);

  if (pixel != Groundtype::GP_NOTHING && !(pixel & Groundtype::GP_BRIDGE))
    return true;

  return false;
}

bool
PinguAction::collision_on_walk (int x, int y)
{
  bool collision = false;
  int pixel = Groundtype::GP_NOTHING;

  for (int pingu_y = 0; pingu_y <= pingu_height; ++pingu_y)
  {
    pixel = rel_getpixel(x, y + pingu_y);

    if (pixel != Groundtype::GP_NOTHING && pixel != Groundtype::GP_BRIDGE)
    {
      collision = true;
      break;
    }
  }

  return collision;
}

std::string PinguAction::get_name() const {
  return name;
}

ActionType PinguAction::get_activation_mode(ActionName::Enum action_name) {
  switch(action_name)
  {
    case ActionName::CLIMBER:
      return WALL_TRIGGERED;

    case ActionName::FLOATER:
      return FALL_TRIGGERED;

    default:
      return INSTANT;
  }
}

/* EOF */
