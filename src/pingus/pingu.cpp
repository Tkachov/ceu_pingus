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

#include "pingus/pingu.hpp"

#include <sstream>

#include "engine/display/scene_context.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/fonts.hpp"
#include "pingus/globals.hpp"
#include "pingus/world.hpp"
#include "pingus/worldobj.hpp"
#include "pingus/pingu_enums.hpp"

#include "util/log.hpp"

#include "ceuvars.h"

// Init a pingu at the given position while falling
Pingu::Pingu (int arg_id, const Vector3f& arg_pos, int owner):
  id(arg_id),
  owner_id(owner),
  pos_x(arg_pos.x),
  pos_y(arg_pos.y),
  direction()
{
  direction.left();
}

Pingu::~Pingu() {}

unsigned int
Pingu::get_id ()
{
  return id;
}

void
Pingu::set_x (float x)
{
  pos_x = x;
}

void
Pingu::set_y (float y)
{
  pos_y = y;
}

void
Pingu::set_pos (float x, float y)
{
  set_x (x);
  set_y (y);
}

void
Pingu::set_pos (const Vector3f& arg_pos)
{
  set_x (arg_pos.x);
  set_y (arg_pos.y);
}

// Set the action of the pingu (bridger, blocker, bomber, etc.)
// This function is used by external stuff, like the ButtonPanel, etc
// When you select a function on the button panel and click on a
// pingu, this action will be called with the action name
bool Pingu::request_set_action(ActionName::Enum action_name) {
  RequestSetActionPackage package(this, action_name);
  RequestSetActionPackage* p = &package;
  ceu_out_go(&CEUapp, CEU_IN_PINGU_REQUEST_SET_ACTION, &p);
  return package.result;
}

Vector3f
Pingu::get_pos () const
{
  return Vector3f(pos_x, pos_y, 0);
}

int
Pingu::get_owner ()
{
  return owner_id;
}

std::string
Pingu::get_owner_str ()
{
  std::ostringstream ostr;
  ostr << owner_id;
  return ostr.str();
}

/* EOF */
