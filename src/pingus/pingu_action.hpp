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
  bool CATCHABLE, CHANGE_ALLOWED;
  std::string name;

protected:
  /** A pointer to the pingu, which hold the action. */
  Pingu*      pingu;

public:
  PinguAction(Pingu* p, ActionName::Enum t);
  virtual ~PinguAction();

  /// Gives the PinguAction class access to the data of the Pingu.
  void set_pingu (Pingu*);

  /** Get the pixel from the colmap, relative to the pingu position.

      @param x x is relative to the direction, so 1 is the pixel
      infront of the pingu

      @param y 1 is up, -1 is down
  */
  int  rel_getpixel (int x, int y);

  /** Checks if this action allows to be overwritten with the given new action */
  bool change_allowed(ActionName::Enum action);

  struct ChangeAllowedPackage {
    PinguAction* action;
    ActionName::Enum new_action;
    bool result;

    ChangeAllowedPackage(PinguAction* a, ActionName::Enum n, bool r):
      action(a), new_action(n), result(r) {};
  };

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

  virtual void catch_pingu(Pingu*);

  struct CatchedPingu {
    PinguAction* action;
    Pingu* pingu;
  };

  /** Return true if the pingu can be caught with the mouse and
      another action can be applied, false otherwise (exiter,
      splashed, etc.) */
  virtual bool catchable () { return CATCHABLE; }

  /// True if Pingu in specified position would bang its head if it were walking
  bool head_collision_on_walk (int x, int y);

  /// True if Pingu in specified position would have a collision if it were walking
  bool collision_on_walk (int x, int y);

  /** Move Pingu according to the forces applied to it */
  void move_with_forces ();

public:
  static ActionType get_activation_mode(ActionName::Enum action_name);

private:
  PinguAction (const PinguAction&);
  PinguAction& operator= (const PinguAction&);
};

#endif /* PINGU_ACTION_HH */

/* EOF */
