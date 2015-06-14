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

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_BOARDER_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_BOARDER_HPP

#include "pingus/pingu_action.hpp"

namespace Actions {

/** The Boarder action causes a pingu to use a skateboard to move
    forward. */
class Boarder: public PinguAction {
public:
  Boarder(Pingu* p): PinguAction(p) {};
  ActionName::Enum get_type() const { return ActionName::BOARDER; }

private:
  Boarder(const Boarder&);
  Boarder& operator=(const Boarder&);
};

} // namespace Actions

#endif

/* EOF */
