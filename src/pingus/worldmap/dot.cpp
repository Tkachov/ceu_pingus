//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include "pingus/worldmap/dot.hpp"

#include "ceuvars.h"

namespace WorldmapNS {

Dot::Dot(const FileReader& reader) :
  Drawable(),
  pos()
{
  reader.read_vector("position", pos);
  reader.read_string("name",     name);

  assert(!name.empty());
}

void Dot::draw_hover(DrawingContext& gc) {
  DrawableDrawPackage package(this, gc);
  DrawableDrawPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_DOT_DRAW_HOVER, &pp);
}

void Dot::on_click() {
  Dot* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DOT_ON_CLICK, &self);
}

} // namespace WorldmapNS

/* EOF */
