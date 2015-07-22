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

#include "pingus/worldmap/worldmap.hpp"

#include <iostream>

#include "engine/sound/sound.hpp"
#include "pingus/gettext.h"
#include "pingus/globals.hpp"
#include "pingus/stat_manager.hpp"
#include "pingus/worldmap/pingus.hpp"
#include "util/log.hpp"
#include "util/sexpr_file_writer.hpp"
#include "util/pathname.hpp"

#include "ceuvars.h"

namespace WorldmapNS {

Worldmap* Worldmap::current_ = 0; 

Worldmap::Worldmap(const Pathname& filename) :
  worldmap(),
  default_node(),
  final_node(),
  pingus(),
  gc_state(),
  path_graph(),
  drawables(),
  objects(),
  mouse_x(0),
  mouse_y(0)
{
  current_ = this;

  worldmap = PingusWorldmap(filename);
}

Worldmap::~Worldmap() {
  Worldmap* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_WORLDMAP, &self);
}

void
Worldmap::add_drawable(Drawable* drawable)
{
  drawables.push_back(drawable);
}

} // namespace WorldmapNS

/* EOF */
