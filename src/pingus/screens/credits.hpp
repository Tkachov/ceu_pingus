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

#ifndef HEADER_PINGUS_PINGUS_SCREENS_CREDITS_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_CREDITS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "engine/screen/gui_screen.hpp"

class Pathname;

void read_file(std::ifstream& fin, std::vector<std::string>& credits);
void couldnt_open(const Pathname& filename, std::vector<std::string>& credits);

class Credits: public GUIScreen {
private:
  const Pathname& filename;

public:
  Credits(const Pathname& filename);
  virtual ~Credits();

  void update(float);

private:
  Credits(const Credits&);
  Credits& operator=(const Credits&);

};

#endif

/* EOF */
