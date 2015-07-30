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

#include "engine/screen/gui_screen.hpp"

#include "engine/display/display.hpp"
#include "engine/gui/gui_manager.hpp"
#include "pingus/globals.hpp"
#include "util/log.hpp"

#include "ceuvars.h"

GUIScreen::GUIScreen() :
  Screen(Display::get_size()),
  gui_manager(new GUI::GUIManager())
{
}

GUIScreen::~GUIScreen ()
{
}

/** Draw this screen */
void
GUIScreen::draw(DrawingContext& gc)
{
  draw_background(gc);
  gui_manager->draw(gc);
  draw_foreground(gc);
}

void
GUIScreen::update(float delta)
{
  gui_manager->update(delta);

  ScreenUpdatePackage package(this, delta);
  ScreenUpdatePackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_SCREEN_UPDATE, &pp);
}

void
GUIScreen::update (const Input::Event& event)
{
  // Dispatch the recieved input events
  gui_manager->update(event);

  switch (event.type)
  {
    case Input::POINTER_EVENT_TYPE:
    {
      // ignored cause this is handled in the gui_manager
    }
    break;

    case Input::BUTTON_EVENT_TYPE:
    {
      process_button_event (event.button);
    }
    break;

    case Input::AXIS_EVENT_TYPE:
    {
      if (event.axis.name == Input::ACTION_AXIS)
      {
        on_action_axis_move(event.axis.dir);
      }
    }
    break;

    case Input::SCROLLER_EVENT_TYPE:
    {

    }
    break;
                
    case Input::KEYBOARD_EVENT_TYPE:
    {
                
    }
    break;

    case Input::TEXT_INPUT_EVENT_TYPE:
    {
                
    }
    break;

    default:
      log_error("unhandled event type: %1%", event.type);
      break;
  }

  ScreenUpdateEventPackage package(this, event);
  ScreenUpdateEventPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_SCREEN_UPDATE_EVENT, &pp);
}

void
GUIScreen::process_button_event (const Input::ButtonEvent& event)
{
  if (event.state == Input::BUTTON_PRESSED)
  {
    switch (event.name)
    {
      case Input::PRIMARY_BUTTON:
        // ignoring, handled in the gui_manager
        break;
      case Input::SECONDARY_BUTTON:
        // ignoring, handled in the gui_manager
        break;
      case Input::PAUSE_BUTTON:
        on_pause_press ();
        break;
      case Input::SINGLE_STEP_BUTTON:
        on_single_step_press();
        break;
      case Input::FAST_FORWARD_BUTTON:
        on_fast_forward_press ();
        break;
      case Input::ARMAGEDDON_BUTTON:
        on_armageddon_press ();
        break;
      case Input::ESCAPE_BUTTON:
        on_escape_press ();
        break;
      case Input::ACTION_UP_BUTTON:
        on_action_up_press();
        break;
      case Input::ACTION_DOWN_BUTTON:
        on_action_down_press();
        break;
      default:
        log_debug("unhandled event: %1%", event.name);
        break;
    }
  }
  else if (event.state == Input::BUTTON_RELEASED)
  {
    switch (event.name)
    {
      case Input::PRIMARY_BUTTON:
        // ignoring, handled in the gui_manager
        break;
      case Input::SECONDARY_BUTTON:
        // ignoring, handled in the gui_manager
        break;
      case Input::PAUSE_BUTTON:
        on_pause_release ();
        break;
      case Input::SINGLE_STEP_BUTTON:
        on_single_step_release();
        break;
      case Input::FAST_FORWARD_BUTTON:
        on_fast_forward_release ();
        break;
      case Input::ARMAGEDDON_BUTTON:
        on_armageddon_release ();
        break;
      case Input::ESCAPE_BUTTON:
        on_escape_release ();
        break;
      case Input::ACTION_UP_BUTTON:
        on_action_up_release();
        break;
      case Input::ACTION_DOWN_BUTTON:
        on_action_down_release();
        break;
      default:
        log_debug("unhandled event: %1%", event.name);
        break;
    }
  }
  else
  {
    log_error("got unknown event.state: %1%", event.state);
  }
}

void GUIScreen::draw_background(DrawingContext& gc) {
  ScreenDrawPackage package(this, gc);
  ScreenDrawPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_SCREEN_DRAW_BACKGROUND, &pp);
}

void GUIScreen::resize(const Size& size_) {
  Screen::resize(size_);
  gui_manager->set_rect(Rect(Vector2i(0, 0), size));

  ScreenResizePackage package(this, size_);
  ScreenResizePackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_SCREEN_RESIZE, &pp);
}

void GUIScreen::on_startup() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_STARTUP, &self);
}

void GUIScreen::on_armageddon_press() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_ARMAGEDDON_PRESS, &self);
}

void GUIScreen::on_escape_press() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_ESCAPE_PRESS, &self);
}

void GUIScreen::on_pause_press() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_PAUSE_PRESS, &self);
}

void GUIScreen::on_single_step_press() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_SINGLE_STEP_PRESS, &self);
}

void GUIScreen::on_fast_forward_press() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_FAST_FORWARD_PRESS, &self);
}

void GUIScreen::on_action_up_press() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_ACTION_UP_PRESS, &self);
}

void GUIScreen::on_action_down_press() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_ACTION_DOWN_PRESS, &self);
}

void GUIScreen::on_pause_release() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_PAUSE_RELEASE, &self);
}
void GUIScreen::on_single_step_release() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_SINGLE_STEP_RELEASE, &self);
}

void GUIScreen::on_armageddon_release() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_ARMAGEDDON_RELEASE, &self);
}

void GUIScreen::on_escape_release() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_ESCAPE_RELEASE, &self);
}

void GUIScreen::on_fast_forward_release() {
  GUIScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_ON_FAST_FORWARD_RELEASE, &self);
}

void GUIScreen::on_action_axis_move(float move) {
  ScreenAxisMovePackage package(this, move);
  ScreenAxisMovePackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_ON_ACTION_AXIS_MOVE, &pp);
}

/* EOF */
