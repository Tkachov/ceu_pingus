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

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_BOMBER_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_BOMBER_HPP

#include "pingus/collision_mask.hpp"
#include "pingus/pingu_action.hpp"
#include "pingus/state_sprite.hpp"
#include "pingus/movers/linear_mover.hpp"

namespace Actions {

/** An action with lets the Pingu explode. After the explosion the the
    Pingu leaves a hole inside the ground. */
class Bomber: public PinguAction {
private:
  CollisionMask bomber_radius;  

  Sprite explo_surf;
  Movers::LinearMover mover;

public:
  Bomber(Pingu*);

  bool change_allowed(ActionName::Enum action) { return false; }

private:
  Bomber(const Bomber&);
  Bomber& operator=(const Bomber&);
};

} // namespace Actions

#endif

/* EOF */
