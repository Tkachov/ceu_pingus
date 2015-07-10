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

#include "pingus/components/smallmap.hpp"

#include "pingus/components/playfield.hpp"
#include "pingus/server.hpp"
#include "pingus/smallmap_image.hpp"
#include "pingus/world.hpp"

#include "ceuvars.h"

SmallMap::SmallMap(Server* server_, Playfield* playfield_, const Rect& rect_) :
  RectComponent(rect_), 
  server(server_),
  playfield(playfield_),
  exit_sur(),
  entrance_sur(), 
  scroll_mode(false),
  has_focus(),
  gc_ptr(0)
{
  SmallMap* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_SMALLMAP, &self);
}

SmallMap::~SmallMap() {
  SmallMap* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_SMALLMAP, &self);
}

bool
SmallMap::is_at (int x, int y)
{
  return (x > rect.left && x < rect.left + static_cast<int>(rect.get_width())
          && y > rect.top && y < rect.top + static_cast<int>(rect.get_height()));
}

void
SmallMap::on_primary_button_release(int x, int y)
{
  scroll_mode = false;
}

void
SmallMap::on_pointer_enter ()
{
  has_focus = true;
}

void
SmallMap::on_pointer_leave ()
{
  has_focus = false;
}

/* EOF */
