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

#include "pingus/worldobjs/switch_door_switch.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/collision_map.hpp"

#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"
#include "pingus/worldobjs/switch_door_door.hpp"
#include "util/log.hpp"

#include "ceuvars.h"

namespace WorldObjs {

SwitchDoorSwitch::SwitchDoorSwitch(const FileReader& reader) :
  switch_pos(),
  switch_sur("worldobjs/switchdoor_switch"),
  m_target(),
  is_triggered(false),
  m_door()
{
  reader.read_string("target-id", m_target);
  reader.read_vector("position", switch_pos);

  SwitchDoorSwitch* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_SWITCH_DOOR_SWITCH, &self);
}

SwitchDoorSwitch::~SwitchDoorSwitch() {
  SwitchDoorSwitch* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_SWITCH_DOOR_SWITCH, &self);
}

void
SwitchDoorSwitch::on_startup ()
{
  if (m_target.empty())
  {
    log_error("target-id is empty");
  }
  else
  {
    m_door = dynamic_cast<SwitchDoorDoor*>(world->get_worldobj(m_target));
    if (!m_door)
      log_error("given target-id is not a SwitchDoorDoor");
  }
}

} // namespace WorldObjs

/* EOF */
