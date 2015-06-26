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

#ifndef HEADER_PINGUS_PINGUS_PINGU_HPP
#define HEADER_PINGUS_PINGUS_PINGU_HPP

#include <memory>

#include "math/vector3f.hpp"
#include "pingus/direction.hpp"
#include "pingus/action_name.hpp"

class ActionHolder;
class SceneContext;

/** The class for managing one of the many penguins which are walking
    around in the World. All actions are handled by PinguAction
    objects. */
class Pingu
{
private:
  /** The uniq id of the Pingu, this is used to refer to the Pingu in
      a demo file or in a network connection */
  unsigned int id;

public:

  //FIXME make me private
  Direction direction;

  /** Creates a new Pingu at the given coordinates
      @param arg_id The uniq id of the pingu
      @param pos The start position of the pingu
      @param owner The owner id of the pingu (used for multiplayer) */
  Pingu (int arg_id);

  /** Destruct the pingu... */
  ~Pingu ();

  /// Returns the unique id of the pingu
  unsigned int  get_id (void);


private:
  Pingu (const Pingu&);
  Pingu& operator= (const Pingu&);
};

#endif

/* EOF */
