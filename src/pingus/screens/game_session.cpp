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

#include "pingus/screens/game_session.hpp"
#include "ceuvars.h"

GameSession::GameSession(const PingusLevel& arg_plf, bool arg_show_result_screen) :
  plf(arg_plf),
  show_result_screen(arg_show_result_screen)  
{  
  log_debug("GameSession");

  GameSession* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_GAME_SESSION, &self);
}

GameSession::~GameSession()
{
  GameSession* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_GAME_SESSION, &self);
}

/* EOF */
