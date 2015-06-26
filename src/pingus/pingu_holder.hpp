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

#ifndef HEADER_PINGUS_PINGUS_PINGU_HOLDER_HPP
#define HEADER_PINGUS_PINGUS_PINGU_HOLDER_HPP

#include <list>

#include "pingus/worldobj.hpp"

class PingusLevel;
class Vector3f;
class Pingu;

/** This class holds all the penguins in the world */
class PinguHolder : public WorldObj
{
private:
  /** The total number of pingus that will get released in this
      level */
  int number_of_allowed;

  /** Number of pingus in Ceu (synced by Ceu PinguHolder) */  
  int dead;
  int exited;
  int released;

public:
  PinguHolder(const PingusLevel&);
  ~PinguHolder();

  /*@{
    @name overloaded stuff for WorldObj
  */
  void draw (SceneContext& gc);

  /** Update all Pingus (this calls Pingu::update() which then calls
      PinguAction::update()) */
  void update();

  /** The z-pos at which the pingus gets draw.
      @return 50 */
  float get_z_pos() const;
  void set_pos(const Vector3f& p) { }
  Vector3f get_pos() const { return Vector3f(); }
  /*@}*/

  /** @return the number of pingus that have successfully exit this
      level */
  int  get_number_of_exited();

  /** @return the number of pingus that got killed */
  int  get_number_of_killed();

  /** @return the number of pingus that are still alive, this is shown
      in the PingusCounter panel as 'Out'. Exited pingus are *not*
      counted. FIXME: name should be different (out, active?!) */
  int  get_number_of_alive();

  /** @return the total number of pingus released, this is alive +
      killed + exited */
  int get_number_of_released();

  /** @return the maximal number of pingus that will get released in
      this level */
  int get_number_of_allowed();

  /** @return the id of the last pingu + 1 */
  unsigned int get_end_id();

private:
  PinguHolder (const PinguHolder&);
  PinguHolder& operator= (const PinguHolder&);
};

#endif

/* EOF */
