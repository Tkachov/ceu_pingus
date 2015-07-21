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

#include "pingus/worldmap/worldmap_screen.hpp"

#include "ceuvars.h"

namespace WorldmapNS {

WorldmapScreen::WorldmapScreen() {
  WorldmapScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_WORLDMAP_SCREEN, &self);
}

WorldmapScreen::~WorldmapScreen() {
  WorldmapScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_WORLDMAP_SCREEN, &self);
}

void WorldmapScreen::load(const Pathname& filename) {
  WorldmapScreenLoadPackage package(this, filename);
  WorldmapScreenLoadPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_LOAD_WORLDMAP_SCREEN, &pp);
}

void WorldmapScreen::update(float delta) {
  GUIScreen::update(delta);

  ScreenUpdatePackage package(this, delta);
  ScreenUpdatePackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_WORLDMAP_SCREEN_UPDATE, &pp);
}

} // namespace WorldmapNS

/* EOF */
