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

#include "pingus/pingu.hpp"
#include "pingus/pingus_level.hpp"

#include "ceuvars.h"

PinguHolder::PinguHolder(const PingusLevel& plf) :
  number_of_allowed(plf.get_number_of_pingus()),
  number_of_exited(0),
  all_pingus_size(0),
  pingus()
{
  PinguHolder* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_PINGU_HOLDER, &self);
}

PinguHolder::~PinguHolder()
{
  PinguHolder* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_PINGU_HOLDER, &self);
}

Pingu*
PinguHolder::create_pingu (const Vector3f& pos, int owner_id)
{
  if (number_of_allowed > get_number_of_released())
  {
    PinguPackage package(this, pos, owner_id);
    PinguPackage* pp = &package;
    ceu_out_go(&CEUapp, CEU_IN_NEW_PINGU, &pp);

    // This list holds the active pingus
    pingus.push_back(package.result);

    return package.result;
  }
  else
  {
    return 0;
  }
}

void
PinguHolder::draw (SceneContext& gc)
{
  SceneContext* g = &gc;
  ceu_out_go(&CEUapp, CEU_IN_PINGU_DRAW_WALKER, &g);
  ceu_out_go(&CEUapp, CEU_IN_PINGU_DRAW_OTHERS, &g);
}

void PinguHolder::update() {
  ceu_out_go(&CEUapp, CEU_IN_PINGU_UPDATE_ALL, 0);

  PinguIter pingu = pingus.begin();
  while(pingu != pingus.end()) {
    switch((*pingu)->get_status()) {
      case Pingu::PS_EXITED:
        number_of_exited += 1;
      //no break;

      case Pingu::PS_DEAD:
        // Removing the pingu and setting the iterator back to
        // the correct position, no memory hole since pingus will
        // keep track of the allocated Pingus
        pingu = pingus.erase(pingu);
      break;

      default:
        // move to the next Pingu
        ++pingu;
    }
  }
}

Pingu* PinguHolder::get_pingu(unsigned int id_) {
  GetPinguPackage package(this, id_);
  GetPinguPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_GET_PINGU, &pp);
  return pp->result;
}

float
PinguHolder::get_z_pos() const
{
  return 50;
}

int
PinguHolder::get_number_of_exited()
{
  return number_of_exited;
}

int
PinguHolder::get_number_of_killed()
{
  return all_pingus_size - static_cast<int>(pingus.size()) - get_number_of_exited();
}

int
PinguHolder::get_number_of_alive()
{
  return static_cast<int>(pingus.size());
}

int
PinguHolder::get_number_of_released()
{
  return all_pingus_size;
}

int
PinguHolder::get_number_of_allowed()
{
  return number_of_allowed;
}

unsigned int
PinguHolder::get_end_id()
{
  return all_pingus_size;
}

/* EOF */
