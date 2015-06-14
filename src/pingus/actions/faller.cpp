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

#include "pingus/actions/faller.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/colliders/pingu_collider.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_enums.hpp"
#include "pingus/world.hpp"
#include "pingus/worldobj.hpp"

#include "ceuvars.h"

namespace Actions {

Faller::Faller (Pingu* p) :
  PinguAction(p, ActionName::FALLER),
  faller(),
  tumbler(),
  mover(WorldObj::get_world(), Vector3f(0, 0, 0))
{
  // FIXME: add sprites for jumping here: if x_vel > y_vel, use them
}

Faller::~Faller() {}

bool
Faller::is_tumbling () const
{
  // If we are going fast enough to get smashed, start tumbling
  return (Math::abs(pingu->get_velocity().x) > deadly_velocity
          || Math::abs(pingu->get_velocity().y) > deadly_velocity);
}

bool
Faller::change_allowed (ActionName::Enum new_action)
{
  return
    new_action == ActionName::FLOATER ||
    new_action == ActionName::CLIMBER ||
    new_action == ActionName::BOMBER;
}

} // namespace Actions

/* EOF */
