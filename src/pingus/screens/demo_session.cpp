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
#include "engine/gui/surface_button.hpp"
#include "engine/screen/screen_manager.hpp"
#include "pingus/components/playfield.hpp"
#include "pingus/components/button_panel.hpp"
#include "pingus/pingus_demo.hpp"
#include "pingus/server.hpp"
#include "pingus/world.hpp"
#include "util/log.hpp"

#include "ceuvars.h"

static bool false_func() { return false; }

class BButton : public GUI::SurfaceButton
{
private:
  Sprite highlight;
  std::function<void(void)> callback;
  std::function<bool(void)> highlight_func;
  
public:
  BButton(int x, int y, const std::string& name, 
          std::function<void (void)> callback_,
          std::function<bool(void)> highlight_func_ = &false_func) :
    SurfaceButton(x, y, name, name + "-pressed", name + "-hover"),
    highlight("core/demo/highlight"),
    callback(callback_),
    highlight_func(highlight_func_)
  {}

  virtual void draw (DrawingContext& gc) 
  {

    if (highlight_func())
    {
      gc.draw(button_pressed_surface, Vector2i(x_pos, y_pos));
      gc.draw(highlight, Vector2i(x_pos, y_pos));
    }
    else
    {
      SurfaceButton::draw(gc);
    }
  }

  void on_click() {
    callback();
  }
};

DemoSession::DemoSession(const Pathname& pathname_) :
  pathname(pathname_),
  server(),
  demo(),
  events(),
  pcounter(),
  playfield(),
  small_map(),
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

  init_WORLD(server->plf);

  gui_manager->add(pcounter);
  gui_manager->add(new ButtonPanel(server, Vector2i(0, (size.height - 100)/2)));

  gui_manager->add(playfield);
  
  gui_manager->add(small_map);

  gui_manager->add(fastforward_button= new BButton(32+50, 32, "core/demo/fastforward",
                                                   std::bind(&DemoSession::on_fast_forward_press, this),
                                                   std::bind(&DemoSession::is_fast_forward, this)));
  gui_manager->add(pause_button =new BButton(32,  32, "core/demo/pause",
                                             std::bind(&DemoSession::on_pause_press, this),
                                             std::bind(&DemoSession::is_pause, this)));
  gui_manager->add(restart_button = new BButton(size.width - 32 - 48, 32, "core/demo/reload",
                                                std::bind(&DemoSession::restart, this)));
}

DemoSession::~DemoSession()
{
  DemoSession* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_DEMO_SESSION, &self);
}

void
DemoSession::draw_background(DrawingContext& gc)
{
  Rect rect = playfield->get_rect();
  
  if (rect != Rect(Vector2i(0,0), Size(gc.get_width(), gc.get_height())))
  { // Draw a black border around the playfield when the playfield is smaller then the screen
    Color border_color(0, 0, 0);
    // top
    gc.draw_fillrect(Rect(0, 0, gc.get_width(), rect.top),
                     border_color);
    // bottom
    gc.draw_fillrect(Rect(0, rect.bottom, gc.get_width(), gc.get_height()),
                     border_color);
    // left
    gc.draw_fillrect(Rect(0, rect.top, rect.left, rect.bottom),
                     border_color);
    // right
    gc.draw_fillrect(Rect(rect.right, rect.top, gc.get_width(), rect.bottom),
                     border_color);
  }  
}

/** Pass a delta to the screen */
void
DemoSession::update(float delta)
{
  GUIScreen::update(delta);

  ComponentUpdatePackage package((GUI::Component*)this, delta);
  ComponentUpdatePackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_DEMO_SESSION_UPDATE_SERVER, &pp);
}

void DemoSession::on_pause_press() {
  pause = !pause;
}

void DemoSession::on_fast_forward_press() {
  fast_forward = !fast_forward;
}

void
DemoSession::on_escape_press()
{
  log_info("Escape Pressed");
  server->send_finish_event();
  ScreenManager::instance()->pop_screen();
}

void DemoSession::on_scroller_move(float x, float y) {
  Vector2i package(x, y);
  Vector2i* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_DEMO_SESSION_ON_SCROLLER_MOVE, &pp);
}

void
DemoSession::restart()
{
  ScreenManager::instance()->replace_screen(std::make_shared<DemoSession>(pathname));
}

void
DemoSession::resize(const Size& size_)
{
  GUIScreen::resize(size_);

  WorldGetSizePackage package;
  WorldGetSizePackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_WORLD_GET_SIZE, &pp);

  playfield->set_rect(Rect(Vector2i(Math::max((size.width  - package.width)/2,  0),
                                    Math::max((size.height - package.height)/2, 0)), 
                           Size(Math::min(size.width,  package.width),
                                Math::min(size.height, package.height))));

  fastforward_button->set_pos(32+50, 32);
  pause_button->set_pos(32,  32);
  restart_button->set_pos(size.width - 32 - 48, 32);

  small_map->set_rect(Rect(Vector2i(5, size.height - 105), Size(175, 100)));
}

/* EOF */
