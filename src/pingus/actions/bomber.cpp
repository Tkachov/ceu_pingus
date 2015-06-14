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

#include "pingus/actions/bomber.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/colliders/pingu_collider.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_enums.hpp"
#include "pingus/world.hpp"
#include "pingus/worldobj.hpp"

namespace Actions {

Bomber::Bomber(Pingu* p):
  PinguAction(p, ActionName::BOMBER),
  bomber_radius("other/bomber_radius_gfx", "other/bomber_radius"),  
  explo_surf(Sprite("pingus/player" + pingu->get_owner_str() + "/explo")),
  mover(WorldObj::get_world(), Vector3f(0, 0, 0))
{}

} // namespace Actions

/* EOF */
