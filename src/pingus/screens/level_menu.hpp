//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_PINGUS_SCREENS_LEVEL_MENU_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_LEVEL_MENU_HPP

#include <vector>
#include "engine/screen/gui_screen.hpp"
#include "pingus/levelset.hpp"

void fill_levelsets(std::vector<Levelset*>& levelsets);

class LevelMenu: public GUIScreen {
public:
  LevelMenu();
  ~LevelMenu();

private:
  LevelMenu (const LevelMenu&);
  LevelMenu& operator= (const LevelMenu&);
};

#endif

/* EOF */
