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
class PinguAction;
class SceneContext;

/** The class for managing one of the many penguins which are walking
    around in the World. All actions are handled by PinguAction
    objects. */
class Pingu
{
private:

  PinguAction* ceu_action;

  void replace_action(PinguAction* a);

  /** The uniq id of the Pingu, this is used to refer to the Pingu in
      a demo file or in a network connection */
  unsigned int id;

  /** The id of the owner of the pingus, used in multiplayer matches */
  int owner_id;

  float pos_x;
  float pos_y;

  Vector3f velocity;

public:

  struct RequestSetActionPackage {
    Pingu* pingu;
    ActionName::Enum action;
    bool result;

    RequestSetActionPackage(Pingu* p, ActionName::Enum a): pingu(p), action(a), result(false) {};
  };

  //FIXME make me private
  Direction direction;

  /** Creates a new Pingu at the given coordinates
      @param arg_id The uniq id of the pingu
      @param pos The start position of the pingu
      @param owner The owner id of the pingu (used for multiplayer) */
  Pingu (int arg_id, const Vector3f& pos, int owner);

  /** Destruct the pingu... */
  ~Pingu ();

  void die(); //notify Ceu to terminate the instance (reason: death)

  PinguAction* get_ceu_action();

  /** Return the logical pingus position, this is the position which
      is used for collision detection to the ground (the pingus
      feet) */
  Vector3f get_pos () const;

  /** Returns the visible position of the pingu, the graphical center
      of the pingu. */
  Vector3f get_center_pos ();

  /** Returns the x position of the pingu
   * For backward comp. only
   */
  const float& get_x () const { return pos_x; }

  /** Returns the y position of the pingu
      For backward comp. only */
  const float& get_y () const { return pos_y; }

  int get_xi () const { return static_cast<int>(pos_x); }
  int get_yi () const { return static_cast<int>(pos_y); }

  /// Returns the unique id of the pingu
  unsigned int  get_id (void);

  /// Set the pingu to the given coordinates
  void set_pos (float x, float y);
  void set_pos (int x, int y) { set_pos(static_cast<float>(x), static_cast<float>(y)); }

  void set_x (float x);

  void set_y (float y);

  /// Set the pingu to the given coordinates
  void set_pos (const Vector3f& arg_pos);

  Vector3f get_velocity () const { return velocity; }

  void set_velocity (const Vector3f& velocity_);

  /** Request an action to be set to the pingu, if its a persistent
      action, it will be hold back for later execution, same with a
      timed action, normal action will be applied if the current
      action allows that. */
  bool request_set_action (ActionName::Enum action_name);

  PinguAction* create_action2(ActionName::Enum action_);

  void apply_force (Vector3f);

  /** Indicate if the pingu's speed is above the deadly velocity */
  //bool is_tumbling () const;

  float get_z_pos () const { return 0; }

  /** @return The owner_id of the owner, only used in multiplayer
      configurations, ought to be 0 in single player */
  int get_owner ();

  /** @return The owner_id as a string. Only used in multiplayer
      configurations, ought to be "0" in single player */
  std::string get_owner_str ();

  bool   is_inside (int x1, int y1, int x2, int y2);

  /** @return the name of the action the Pingu currently has */
  ActionName::Enum get_action ();

private:
  Pingu (const Pingu&);
  Pingu& operator= (const Pingu&);
};

#endif

/* EOF */
