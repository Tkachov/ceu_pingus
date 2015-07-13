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

#include "pingus/components/playfield.hpp"

#include "ceuvars.h"

Playfield::Playfield(const Rect& rect_) :
  RectComponent(rect_),
  scene_context(new SceneContext(rect_)),
  state(rect_.get_width(), rect_.get_height())
{}

Playfield::~Playfield() {}

void Playfield::draw_world() {
  SceneContext* sc = scene_context.get();
  ceu_out_go(&CEUapp, CEU_IN_PLAYFIELD_DRAW, &sc);
}

/* EOF */
