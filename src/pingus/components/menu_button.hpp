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

#ifndef HEADER_PINGUS_PINGUS_COMPONENTS_MENU_BUTTON_HPP
#define HEADER_PINGUS_PINGUS_COMPONENTS_MENU_BUTTON_HPP


#include <string>

#include "engine/display/font.hpp"
#include "engine/display/sprite.hpp"
#include "engine/gui/component.hpp"

class PingusMenu;
class Vector2i;

/** Framework for menu buttons */
class MenuButton: public GUI::Component
{
public: //protected and public here is public for Ceu
  PingusMenu* menu;

  int x_pos;
  int y_pos;

  MenuButton(PingusMenu* menu, const Vector2i& pos, const std::string& text, const std::string& desc) {}
  virtual ~MenuButton() {}

  void set_pos(int x, int y) {
    x_pos = x;
    y_pos = y;
  }

private:
  MenuButton(const MenuButton&);
  MenuButton& operator=(const MenuButton&);
};

#endif

/* EOF */
