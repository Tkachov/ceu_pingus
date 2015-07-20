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

#ifndef HEADER_PINGUS_PINGUS_SCREENS_START_SCREEN_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_START_SCREEN_HPP

#include "engine/screen/gui_screen.hpp"
#include "pingus/pingus_level.hpp"

class StartScreen: public GUIScreen
{
private:
  PingusLevel plf;

public:
  StartScreen(const PingusLevel& plf);
  ~StartScreen();

private:
  StartScreen (const StartScreen&);
  StartScreen& operator= (const StartScreen&);
};

#endif

/* EOF */
