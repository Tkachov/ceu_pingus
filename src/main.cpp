//  Pingus - A free Lemmings clone
//  Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmx.de>
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

#include <SDL.h>

#include "pingus/pingus_main.hpp"
#include "engine/gui/component.hpp"

#include "util/log.hpp"
#include "ceuvars.h"
#include "_ceu_app.c"


//#include "pingus/screens/pingus_menu.hpp"

#include "engine/display/display.hpp"
#include "engine/display/framebuffer.hpp"

tceu_app CEUapp; //exported in "ceuvars.h", which is used everywhere to send Ceu events

int main(int argc, char** argv)
{
  PingusMain app;
    
  static char CEU_DATA[sizeof(CEU_Main)];
  CEUapp.data = (tceu_org*) &CEU_DATA;
  CEUapp.init = &ceu_app_init;
  CEUapp.init(&CEUapp);    /* calls CEU_THREADS_MUTEX_LOCK() */ //so what?

  return app.run(argc, argv);
}

/* EOF */
