// $Id: miner.cpp 3216 2007-09-22 01:47:03Z grumbel $
////  Pingus - A free Lemmings clone
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

#include "pingus/actions/miner.hpp"

#include "engine/display/scene_context.hpp"
#include "engine/sound/sound.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_enums.hpp"
#include "pingus/world.hpp"
#include "pingus/worldobj.hpp"
#include "util/log.hpp"

namespace Actions {

Miner::Miner (Pingu* p) :
  PinguAction(p),
  miner_radius("pingus/common/miner_radius_gfx", "pingus/common/miner_radius"),
  miner_radius_left("pingus/common/miner_radius_left_gfx", "pingus/common/miner_radius_left"),
  miner_radius_right("pingus/common/miner_radius_right_gfx", "pingus/common/miner_radius_right"),
  sprite()
{
  sprite.load(Direction::LEFT,  Sprite("pingus/player" +
                                       pingu->get_owner_str() + "/miner/left"));
  sprite.load(Direction::RIGHT, Sprite("pingus/player" +
                                       pingu->get_owner_str() + "/miner/right"));
}

void
Miner::mine(bool final)
{
  if (!final)
  {
    // regular mine action
    WorldObj::get_world()->remove(miner_radius,
                                  pingu->get_xi() - (miner_radius.get_width() / 2) + pingu->direction,
                                  pingu->get_yi() - miner_radius.get_height() + 2);
  }
  else
  {
    // the last mine action before switching to another action
    CollisionMask& radius = (pingu->direction == Direction::LEFT) ? miner_radius_left : miner_radius_right;
    WorldObj::get_world()->remove(radius,
                                  pingu->get_xi() - (radius.get_width() / 2) + pingu->direction,
                                  pingu->get_yi() - radius.get_height() + 2);
  }
}

void
Miner::draw (SceneContext& gc)
{
  gc.color().draw(sprite[pingu->direction], pingu->get_pos());
}

} // namespace Actions

/* EOF */
