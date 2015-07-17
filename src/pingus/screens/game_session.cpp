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

#include "engine/display/display.hpp"
#include "engine/gui/gui_manager.hpp"
#include "engine/screen/screen_manager.hpp"
#include "pingus/server.hpp"

#include "engine/sound/sound.hpp"
#include "pingus/components/button_panel.hpp"
#include "pingus/components/time_display.hpp"
#include "pingus/globals.hpp"
#include "pingus/savegame_manager.hpp"
#include "pingus/screens/result_screen.hpp"
#include "pingus/world.hpp"
#include "util/log.hpp"

#include "ceuvars.h"

GameSession::GameSession(const PingusLevel& arg_plf, bool arg_show_result_screen) :
  plf(arg_plf),
  show_result_screen(arg_show_result_screen),
  server(),  
  button_panel (0),
  pcounter     (0),
  playfield    (0),
  time_display (0),
  small_map    (0),
  armageddon_button(),
  forward_button(),
  pause_button(),
  pause(false),
  fast_forward(false),
  single_step(false)
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

void
GameSession::draw_background (DrawingContext& gc)
{
  Rect rect = playfield->get_rect();

  if (rect != Rect(Vector2i(0,0), Size(Display::get_width(), Display::get_height())))
  { // Draw a black border around the playfield when the playfield is smaller then the screen
    Color border_color(0, 0, 0);
    // top
    gc.draw_fillrect(Rect(0, 0, Display::get_width(), rect.top),
                     border_color);
    // bottom
    gc.draw_fillrect(Rect(0, rect.bottom, Display::get_width(), Display::get_height()),
                     border_color);
    // left
    gc.draw_fillrect(Rect(0, rect.top, rect.left, rect.bottom),
                     border_color);
    // right
    gc.draw_fillrect(Rect(rect.right, rect.top, Display::get_width(), rect.bottom),
                     border_color);
  }
}

void GameSession::update(float delta) {
  ScreenUpdatePackage package(this, delta);
  ScreenUpdatePackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_GAME_SESSION_UPDATE, &pp);
}

void
GameSession::update(const Input::Event& event)
{
  GUIScreen::update(event);

  //log_info("Events: " << event.get_type ());

  switch (event.type)
  {
    case Input::BUTTON_EVENT_TYPE:
    {
      const Input::ButtonEvent& ev = event.button;

      if (ev.state == Input::BUTTON_PRESSED)
      {
        if (ev.name >= Input::ACTION_1_BUTTON && ev.name <= Input::ACTION_10_BUTTON)
        {
          button_panel->set_button(ev.name - Input::ACTION_1_BUTTON);
        }
        else if (ev.name == Input::ACTION_DOWN_BUTTON)
        {
          button_panel->next_action();
        }
        else if (ev.name == Input::ACTION_UP_BUTTON)
        {
          button_panel->previous_action();
        }
      }
    }
    break;

    case Input::POINTER_EVENT_TYPE:
      // Ignore, is handled in GUIScreen
      break;

    case Input::AXIS_EVENT_TYPE:
      // ???
      //process_axis_event (event.axis);
    break;

    case Input::SCROLLER_EVENT_TYPE:
    {
      const Input::ScrollEvent* e = &event.scroll;
      ceu_out_go(&CEUapp, CEU_IN_GAME_SESSION_SCROLLER_EVENT_TYPE, &e);
    }
    break;

    case Input::KEYBOARD_EVENT_TYPE:
      break;

    case Input::TEXT_INPUT_EVENT_TYPE:
      break;

    default:
      // unhandled event
      log_info("unhandled event: %1%", event.type);
      break;
  }
}

void
GameSession:: on_pause_press ()
{
  set_pause(!get_pause());
}

void
GameSession::on_single_step_press ()
{
  set_pause(true);
  single_step = true;
}

void
GameSession::on_fast_forward_press ()
{
  if (get_pause())
  {
    set_pause(false);
  }
  else
  {
    set_fast_forward(true);
  }
}

void
GameSession::on_fast_forward_release ()
{
  set_fast_forward(false);
}

void
GameSession::on_action_axis_move (float move)
{
  if (move > 0)
    button_panel->next_action ();
  else if (move < 0)
    button_panel->previous_action ();
}

void
GameSession::on_startup ()
{
  if (globals::developer_mode)
    log_info("Starting Music: %1%", server->get_plf().get_music());

  if (server->get_plf().get_music() == "none" ||
      server->get_plf().get_music().empty())
  {
    Sound::PingusSound::stop_music();
  }
  else
  {
    Sound::PingusSound::play_music(server->get_plf().get_music());
  }
}

ActionName::Enum
GameSession::get_action_name() const
{
  return button_panel->get_action_name();
}

void
GameSession::set_fast_forward(bool value)
{
  fast_forward = value;
  if (fast_forward)
  {
    pause = false;
  }
}

bool
GameSession::get_fast_forward() const
{
  return fast_forward;
}

void
GameSession::set_pause(bool value)
{
  pause = value;
  if (pause)
  {
    fast_forward = false;
  }
}

bool
GameSession::get_pause() const
{
  return pause;
}

/* EOF */
