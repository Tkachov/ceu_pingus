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

#include "pingus/actions/bridger.hpp"

#include "engine/display/scene_context.hpp"
#include "engine/sound/sound.hpp"
#include "pingus/gettext.h"
#include "pingus/pingu.hpp"
#include "pingus/world.hpp"
#include "pingus/worldobj.hpp"
#include "util/string_util.hpp"

namespace Actions {

Bridger::Bridger(Pingu* p):
  PinguAction(p, ActionName::BRIDGER),
  walk_sprite(),
  build_sprite(),
  brick_l("other/brick_left"),
  brick_r("other/brick_right"),
  bricks(MAX_BRICKS),
  block_build(false),
  name(_("Bridger") + std::string(" (" + StringUtil::to_string(bricks) + ")"))
{}

// way_is_free() needs to stop BRIDGERS from getting stuck between a brick
// and the ceiling.  The routine also stops cases of Bridgers building up but
// then not being able to walk all the way down the bridge the it has built.
// Even though the routine may be the same as brick_placement_allowed(), it is
// best to keep them apart as they may need to be independent of each other if
// there needs to be a patch.
bool
Bridger::way_is_free()
{
  bool way_free = true;

  for (int x_inc = 1; x_inc <= 4; x_inc++)
  {
    if (rel_getpixel(x_inc, 2) != Groundtype::GP_NOTHING
        || head_collision_on_walk(x_inc, 2))
    {
      way_free = false;
      break;
    }
  }

  return way_free;
}

// brick_placement_allowed() is mainly for stopping WALKERS from getting stuck
// between a brick and the ceiling.  Even though the routine may be the same,
// as way_is_free() it is best to keep them apart as they may need to be
// independent of each other if there needs to be a patch.
bool
Bridger::brick_placement_allowed(void)
{
  return !head_collision_on_walk(0, 2);
}

void
Bridger::place_a_brick()
{
  bricks--;
  name = _("Bridger") + std::string(" (") + StringUtil::to_string(bricks) + ")";

  if (bricks < 4)
    Sound::PingusSound::play_sound("ting");

  if (pingu->direction.is_right())
  {
    WorldObj::get_world()->put(brick_r,
                               static_cast<int>(pingu->get_pos().x + 10.0f - static_cast<float>(brick_r.get_width())),
                               static_cast<int>(pingu->get_pos().y),
                               Groundtype::GP_BRIDGE);
  }
  else
  {
    WorldObj::get_world()->put(brick_l,
                               static_cast<int>(pingu->get_pos().x - 10.0f),
                               static_cast<int>(pingu->get_pos().y),
                               Groundtype::GP_BRIDGE);
  }
}

void
Bridger::walk_one_step_up()
{
  pingu->set_pos(pingu->get_pos().x + (4.0f * static_cast<float>(pingu->direction)),
                 pingu->get_pos().y - 2);
}

std::string
Bridger::get_name () const
{
  return name;
}

} // namespace Actions

/* EOF */
