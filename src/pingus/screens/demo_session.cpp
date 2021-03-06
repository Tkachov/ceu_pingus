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

#include "pingus/screens/demo_session.hpp"

#include <algorithm>
#include <iostream>

#include "engine/gui/gui_manager.hpp"
#include "engine/screen/screen_manager.hpp"
#include "pingus/pingus_demo.hpp"
#include "pingus/server.hpp"
#include "util/log.hpp"

#include "ceuvars.h"

BButton::BButton(int x, int y, const std::string& name,  std::function<void (void)> callback_, std::function<bool(void)> highlight_func_):
    SurfaceButton(x, y, name, name + "-pressed", name + "-hover"),
    highlight("core/demo/highlight"),
    callback(callback_),
    highlight_func(highlight_func_)
  {}

void BButton::draw(DrawingContext& gc) {
  if(highlight_func()) {
    gc.draw(button_pressed_surface, Vector2i(x_pos, y_pos));
    gc.draw(highlight, Vector2i(x_pos, y_pos));
  } else {
    SurfaceButton::draw(gc);
  }
}

void BButton::on_click() { callback(); }

DemoSession::DemoSession(const Pathname& pathname_) :
  pathname(pathname_),
  server(),
  demo(),
  events(),    
  fastforward_button(),
  pause_button(),
  restart_button(),
  pause(false),
  fast_forward(false)
{
  // Load Demo file
  demo = std::unique_ptr<PingusDemo>(new PingusDemo(pathname));

  events = demo->get_events();
  // Reverse the vector so that we can use pop_back()  
  std::reverse(events.begin(), events.end());

  // Create server
  plf = PingusLevel(Pathname("levels/" + demo->get_levelname()  + ".pingus", Pathname::DATA_PATH));

  if (plf.get_checksum() != demo->get_checksum())
  {
    log_warn("checksum missmatch between demo (%1%) and level (%2%)",
             demo->get_checksum(), plf.get_checksum());
  }  

  // Create GUI
  DemoSession* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_DEMO_SESSION, &self);
}

DemoSession::~DemoSession()
{
  DemoSession* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_DEMO_SESSION, &self);
}

void DemoSession::on_pause_press() {
  pause = !pause;
}

void DemoSession::on_fast_forward_press() {
  fast_forward = !fast_forward;
}

void DemoSession::on_scroller_move(float x, float y) {
  Vector2i package(x, y);
  Vector2i* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_DEMO_SESSION_ON_SCROLLER_MOVE, &pp);
}

void
DemoSession::restart()
{
  DemoSession* self = this;
  ceu_out_go(&CEUapp, CEU_IN_RESTART_DEMO_SESSION, &self);  
}

/* EOF */
