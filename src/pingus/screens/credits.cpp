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

#include "pingus/screens/credits.hpp"

#include "util/pathname.hpp"

#include "ceuvars.h"

void read_file(std::ifstream& fin, std::vector<std::string>& credits) {
  std::string line;
  while(std::getline(fin, line))
      credits.push_back(line);
}

void couldnt_open(const Pathname& filename, std::vector<std::string>& credits) {
  std::ostringstream fout;
  fout << "couldn't open " << filename;
  credits.push_back(fout.str());
}

Credits::Credits(const Pathname& fn): filename(fn) {
  Credits* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_CREDITS, &self);
}

Credits::~Credits() {
  Credits* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_CREDITS, &self);
}

void Credits::update(float delta) {
  ScreenUpdatePackage package(this, delta);
  ScreenUpdatePackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_CREDITS_UPDATE, &pp);
}

/* EOF */
