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

#ifndef HEADER_PINGUS_PINGUS_SERVER_HPP
#define HEADER_PINGUS_PINGUS_SERVER_HPP

#include "pingus/action_holder.hpp"
#include "pingus/pingus_level.hpp"
#include "pingus/server_event.hpp"
#include <memory>

std::unique_ptr<std::ostream> get_demostream(const PingusLevel& plf);

/** A abstract server-like class */
class Server
{
protected:
  PingusLevel plf;

  /** Manager class for the number of available actions */
  ActionHolder action_holder;
  
  std::unique_ptr<std::ostream> demostream;

public:
  Server(const PingusLevel& arg_plf);
  ~Server() {};

  void update();

  ActionHolder* get_action_holder();  

private:
  Server (const Server&);
  Server& operator= (const Server&);
};

#endif

/* EOF */
