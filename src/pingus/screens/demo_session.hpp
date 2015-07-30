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

#ifndef HEADER_PINGUS_PINGUS_SCREENS_DEMO_SESSION_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_DEMO_SESSION_HPP

#include <memory>
#include <vector>

#include "engine/screen/gui_screen.hpp"
#include "pingus/pingus_level.hpp"
#include "pingus/server_event.hpp"
#include "util/pathname.hpp"
#include "engine/gui/component.hpp"
#include "engine/gui/rect_component.hpp"
#include "engine/gui/surface_button.hpp"

namespace Input {
struct Event;
struct ScrollEvent;
} // namespace Input

class Server;
class XMLPDF;
class DemoPlayer;
class PingusDemo;

static bool false_func() { return false; }

class BButton: public GUI::SurfaceButton
{
private:
  Sprite highlight;
  std::function<void(void)> callback;
  std::function<bool(void)> highlight_func;
  
public:
  BButton(int x, int y, const std::string& name,  std::function<void (void)> callback_, std::function<bool(void)> highlight_func_ = &false_func);
  virtual void draw(DrawingContext& gc);
  void on_click();
};

/** A DemoSession is analog to a GameSession, but instead of loading a
    level and letting the player play a game, a demo file will be
    loaded and the level will be played automatically. */
class DemoSession : public GUIScreen
{
private:
  Pathname pathname;

  PingusLevel plf;
  Server*     server;
  std::unique_ptr<PingusDemo> demo;
  std::vector<ServerEvent>  events;  

  BButton* fastforward_button;
  BButton* pause_button;
  BButton* restart_button;

  bool pause;
  bool fast_forward;

public:
  /** @param filename the complete filename of the demo file */
  DemoSession(const Pathname& pathname);
  ~DemoSession();

  /** Pass a delta to the screen */
  void update(float delta);

  void on_pause_press ();
  void on_fast_forward_press ();  

  void restart();
  
  void on_scroller_move(float x, float y);

  bool is_pause() { return pause; }
  bool is_fast_forward() { return fast_forward; }

private:
  DemoSession (const DemoSession&);
  DemoSession& operator= (const DemoSession&);
};

#endif

/* EOF */
