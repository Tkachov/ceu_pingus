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

#include "pingus/actions/basher.hpp"
#include "pingus/actions/bridger.hpp"
#include "pingus/actions/climber.hpp"
#include "pingus/actions/faller.hpp"
#include "pingus/actions/floater.hpp"

#include "util/log.hpp"

#include "ceuvars.h"

using namespace Actions;

// Init a pingu at the given position while falling
Pingu::Pingu (int arg_id, const Vector3f& arg_pos, int owner):
  ceu_action(0),
  wall_action(),
  wall_action_set(false),
  fall_action(),
  fall_action_set(false),
  previous_action(ActionName::FALLER),
  id(arg_id),
  owner_id(owner),
  status(PS_ALIVE),
  pos_x(arg_pos.x),
  pos_y(arg_pos.y),
  velocity(0, 0, 0),
  direction()
{
  direction.left();

  ceu_action = create_action2(ActionName::FALLER); //so get_ceu_action() never fails

  //create Ceu Pingu
  Pingu* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_PINGU, &self);

  //ceu_pingu should be already set now from Ceu Pingu
}

Pingu::~Pingu() {
  Pingu* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_PINGU, &self);
}

void Pingu::replace_action(PinguAction* a) {
  PinguAction* backup_action = ceu_action;
  ceu_action = a;
  delete backup_action;
}

PinguAction* Pingu::get_ceu_action() {
  return ceu_action;
}

unsigned int
Pingu::get_id ()
{
  return id;
}

bool
Pingu::change_allowed(ActionName::Enum new_action)
{
  assert(ceu_action);
  assert(get_ceu_action());
  return get_ceu_action()->change_allowed (new_action);
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

void
Pingu::set_velocity (const Vector3f& velocity_)
{
  velocity = velocity_;

  // crude terminal velocity
  velocity.x = Math::clamp(-terminal_velocity, velocity.x, terminal_velocity);
  velocity.y = Math::clamp(-terminal_velocity, velocity.y, terminal_velocity);
}

// Set the action of the pingu (bridger, blocker, bomber, etc.)
// This function is used by external stuff, like the ButtonPanel, etc
// When you select a function on the button panel and click on a
// pingu, this action will be called with the action name
bool Pingu::request_set_action(ActionName::Enum action_name) {
  if(status == PS_DEAD) {
    log_debug("Setting action to a dead pingu");
    return false;
  }

  switch(PinguAction::get_activation_mode(action_name)) {
    case INSTANT:
      if(action_name == get_ceu_action()->get_type()) {
        log_debug("Pingu: Already have action");
        return false;
      } else if(get_ceu_action()->change_allowed(action_name)) {
        log_debug("setting instant action");
        set_action(action_name);
        return true;
      } else {
        log_debug("change from action %1% not allowed", get_ceu_action()->get_name());
        return false;
      }
    break;

    case WALL_TRIGGERED:
      if(wall_action_set && wall_action == action_name) {
        log_debug("Not using wall action, we have already");
        return false;
      } else {
        log_debug("Setting wall action");
        wall_action = action_name;
        wall_action_set = true;
        return true;
      }
    break;

    case FALL_TRIGGERED:
      if(fall_action_set && fall_action == action_name) {
        log_debug("Not using fall action, we have already");
        return false;
      } else {
        log_debug("Setting fall action");
        fall_action = action_name;
        fall_action_set = true;
        return true;
      }
    break;

    default:
      log_debug("unknown action activation_mode");
      assert(0);
      return false;
    break;
  }

  return false;
}

void
Pingu::set_action (ActionName::Enum action_name)
{
  set_action(create_action(action_name).get());
}

// Sets an action without any checking
void
Pingu::set_action(PinguAction* act)
{
  assert(act);
  printf("C++ set_action\n");
  PinguAction* p = act;
  ceu_out_go(&CEUapp, CEU_IN_PINGU_SET_ACTION, &p);
/*
  PinguAction* backup = get_ceu_action();
  set_ceu_action(act);

  previous_action = backup->get_type();
  delete backup;

  //notify Ceu that it need new action to be created
  PinguAction* p = get_ceu_action();
  ceu_out_go(&CEUapp, CEU_IN_PINGU_SET_ACTION, &p);  */
}

Pingu::PinguStatus
Pingu::get_status (void) const
{
  return status;
}

Pingu::PinguStatus
Pingu::set_status (PinguStatus s)
{
  return (status = s);
}

// Returns true if the given koordinates are above the pingu
bool
Pingu::is_over (int x, int y)
{
  Vector3f center = get_center_pos ();

  return (center.x + 16 > x && center.x - 16 < x &&
          center.y + 16 > y && center.y - 16 < y);
}

bool
Pingu::is_inside (int x1, int y1, int x2, int y2)
{
  assert (x1 < x2);
  assert (y1 < y2);

  return (pos_x > x1 && pos_x < x2
          &&
          pos_y > y1 && pos_y < y2);
}

// Returns the distance between the Pingu and a given coordinate
float
Pingu::dist(int x, int y)
{
  Vector3f p = get_center_pos ();

  return Math::sqrt(((p.x - static_cast<float>(x)) * (p.x - static_cast<float>(x)) +
                     (p.y - static_cast<float>(y)) * (p.y - static_cast<float>(y))));
}

int
Pingu::rel_getpixel(int x, int y)
{
  return WorldObj::get_world()->get_colmap()->getpixel(static_cast<int>(pos_x + static_cast<float>(x * direction)),
                                                       static_cast<int>(pos_y - static_cast<float>(y)));
}

void
Pingu::catch_pingu (Pingu* pingu)
{
  get_ceu_action()->catch_pingu(pingu);
}

bool
Pingu::need_catch ()
{
  if (status == PS_DEAD || status == PS_EXITED)
    return false;

  return get_ceu_action()->need_catch();
}

void
Pingu::set_direction (Direction d)
{
  direction = d;
}

bool
Pingu::is_alive (void)
{
  return (status != PS_DEAD && status != PS_EXITED);
}

std::string
Pingu::get_name()
{
  return get_ceu_action()->get_name();
}

ActionName::Enum
Pingu::get_action ()
{
  return get_ceu_action()->get_type();
}

void
Pingu::apply_force (Vector3f arg_v)
{
  velocity += arg_v;
  // Moving the pingu on pixel up, so that the force can take effect
  // FIXME: this should be handled by a state-machine
  --pos_y;
}

Vector3f
Pingu::get_pos () const
{
  return Vector3f(pos_x, pos_y, 0);
}

Vector3f
Pingu::get_center_pos ()
{
  return get_ceu_action()->get_center_pos();
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

bool
Pingu::catchable ()
{
  return get_ceu_action()->catchable ();
}

std::shared_ptr<PinguAction>
Pingu::create_action(ActionName::Enum action_)
{
  switch(action_)
  {
    case ActionName::BASHER:    return std::make_shared<Basher>(this);
    case ActionName::BRIDGER:   return std::make_shared<Bridger>(this);
    case ActionName::CLIMBER:   return std::make_shared<Climber>(this);
    case ActionName::FALLER:    return std::make_shared<Faller>(this);
    case ActionName::FLOATER:   return std::make_shared<Floater>(this);

    case ActionName::ANGEL:
    case ActionName::BLOCKER:
    case ActionName::BOARDER:
    case ActionName::BOMBER:
    case ActionName::DIGGER:
    case ActionName::DROWN:
    case ActionName::EXITER:
    case ActionName::JUMPER:
    case ActionName::LASERKILL:
    case ActionName::MINER:
    case ActionName::SLIDER:
    case ActionName::SPLASHED:
    case ActionName::SUPERMAN:
    case ActionName::WAITER:
    case ActionName::WALKER:    return std::make_shared<PinguAction>(this, action_);

    default: assert(!"Invalid action name provied");
  }
}

PinguAction* Pingu::create_action2(ActionName::Enum action_) {
  switch(action_) {
    case ActionName::BASHER:    return new Basher(this);
    case ActionName::BRIDGER:   return new Bridger(this);
    case ActionName::CLIMBER:   return new Climber(this);
    case ActionName::FALLER:    return new Faller(this);
    case ActionName::FLOATER:   return new Floater(this);

    case ActionName::ANGEL:
    case ActionName::BLOCKER:
    case ActionName::BOARDER:
    case ActionName::BOMBER:
    case ActionName::DIGGER:
    case ActionName::DROWN:
    case ActionName::EXITER:
    case ActionName::JUMPER:
    case ActionName::LASERKILL:
    case ActionName::MINER:
    case ActionName::SLIDER:
    case ActionName::SPLASHED:
    case ActionName::SUPERMAN:
    case ActionName::WAITER:
    case ActionName::WALKER:    return new PinguAction(this, action_);

    default: assert(!"Invalid action name provied");
  }
}

/* EOF */
