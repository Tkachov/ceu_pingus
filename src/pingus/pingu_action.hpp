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

#ifndef HEADER_PINGUS_PINGUS_PINGU_ACTION_HPP
#define HEADER_PINGUS_PINGUS_PINGU_ACTION_HPP

#include "math/vector3f.hpp"
#include "pingus/action_name.hpp"

class ActionHolder;
class SceneContext;
class Pingu;

enum ActionType
{
  INSTANT,
  WALL_TRIGGERED,
  FALL_TRIGGERED
};

/** This class provides an abstract interface for pingu actions. It is
    used to inherit classes which represent the actions. The actions
    are stored in a seperate library, have a look in actions/ for some
    examples. */
class PinguAction
{
private:
  ActionName::Enum type;
  std::string name;

protected:
  /** A pointer to the pingu, which hold the action. */
  Pingu*      pingu;

public:
  PinguAction(Pingu* p, ActionName::Enum t);
  virtual ~PinguAction();

  /** Get the pixel from the colmap, relative to the pingu position.

      @param x x is relative to the direction, so 1 is the pixel
      infront of the pingu

      @param y 1 is up, -1 is down
  */
  int  rel_getpixel (int x, int y);

  Vector3f get_center_pos() const;

  struct GetCenterPosPackage {
    const PinguAction* action;
    Vector3f result;

    GetCenterPosPackage(const PinguAction* a, Vector3f v):
      action(a), result(v) {};
  };


  /** The name of the action, this is used in the CaputreRectangle, so
      it can contain more than just the name */
  std::string get_name() const;

  /// The type of the action
  ActionName::Enum get_type () const { return type; }

  ///catching Pingus:
  void catch_pingus();

  void catch_pingu(Pingu*);

  struct CatchedPingu {
    PinguAction* action;
    Pingu* pingu;
  };

  /// True if Pingu in specified position would bang its head if it were walking
  bool head_collision_on_walk (int x, int y);

  /// True if Pingu in specified position would have a collision if it were walking
  bool collision_on_walk (int x, int y);

public:
  static ActionType get_activation_mode(ActionName::Enum action_name);

private:
  PinguAction (const PinguAction&);
  PinguAction& operator= (const PinguAction&);
};

#endif /* PINGU_ACTION_HH */

/* EOF */
