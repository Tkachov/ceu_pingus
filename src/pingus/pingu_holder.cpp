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

#include "pingus/pingu_holder.hpp"


#include "pingus/pingus_level.hpp"

#include "ceuvars.h"

PinguHolder::PinguHolder(const PingusLevel& plf) :
  number_of_allowed(plf.get_number_of_pingus()),
  dead(0), exited(0), released(0) {}

PinguHolder::~PinguHolder() {}

void
PinguHolder::draw (SceneContext& gc)
{
  SceneContext* g = &gc;
  ceu_out_go(&CEUapp, CEU_IN_PINGU_DRAW_WALKER, &g);
  ceu_out_go(&CEUapp, CEU_IN_PINGU_DRAW_OTHERS, &g);
}

void PinguHolder::update() {  
  ceu_out_go(&CEUapp, CEU_IN_PINGU_UPDATE_ALL, 0);
}

float
PinguHolder::get_z_pos() const
{
  return 50;
}

int PinguHolder::get_number_of_exited() { return exited; }

int PinguHolder::get_number_of_killed() { return dead; }

int PinguHolder::get_number_of_alive() { return released - dead - exited; }

int PinguHolder::get_number_of_released() { return released; }

int PinguHolder::get_number_of_allowed() { return number_of_allowed; }

unsigned int PinguHolder::get_end_id() { return released; }

/* EOF */
