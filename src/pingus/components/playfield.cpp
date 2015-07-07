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

#include "pingus/components/playfield.hpp"

#include "engine/display/display.hpp"
#include "pingus/globals.hpp"
#include "pingus/pingu_holder.hpp"
#include "pingus/screens/game_session.hpp"
#include "pingus/server.hpp"
#include "pingus/world.hpp"

#include "ceuvars.h"

Playfield::Playfield(Server* server_, GameSession* session_, const Rect& rect_) :
  RectComponent(rect_),
  server(server_),
  session(session_),
  mouse_scrolling(),
  scroll_speed(),
  scroll_center(),
  scene_context(new SceneContext(rect_)),
  state(rect_.get_width(), rect_.get_height()),
  clipping_rectangles(),
  mouse_pos(),
  old_state_pos()
{
  mouse_scrolling    = false;

  state.set_limit(Rect(Vector2i(0, 0),
                       Size(server->get_world()->get_width(),
                            server->get_world()->get_height())));

  // FIXME: Temporary workaround till start-pos is integrated a bit more properly
  state.set_pos(server->get_world()->get_start_pos(0));

  Playfield* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_PLAYFIELD, &self);
}

Playfield::~Playfield() {
  Playfield* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_PLAYFIELD, &self);
}

void
Playfield::draw(DrawingContext& gc)
{
  scene_context->clear();

  state.push(*scene_context);

  ceu_out_go(&CEUapp, CEU_IN_PLAYFIELD_DRAW, &scene_context);

  state.pop(*scene_context);

  gc.draw(new SceneContextDrawingRequest(scene_context.get(), Vector2i(0,0), -10000));

  gc.push_modelview();
  gc.translate(rect.left, rect.top);
  // Draw the scrolling band
  if (mouse_scrolling && !globals::drag_drop_scrolling)
  {
    gc.draw_line(mouse_pos, scroll_center - Vector2i(0, 15),
                 Color(0, 255, 0));

    gc.draw_line(mouse_pos, scroll_center + Vector2i(0, 15),
                 Color(0, 0, 255));

    gc.draw_line(mouse_pos, scroll_center + Vector2i(15, 0),
                 Color(0, 255, 255));

    gc.draw_line(mouse_pos, scroll_center - Vector2i(15, 0),
                 Color(255, 255, 0));

    gc.draw_line(mouse_pos, scroll_center,
                 Color(255, 0, 0));
  }
  gc.pop_modelview();
}

void
Playfield::update(float delta)
{
  // FIXME: This should be delta dependant
  if (!mouse_scrolling)
  {
    Playfield* self = this;
    ceu_out_go(&CEUapp, CEU_IN_PLAYFIELD_UPDATE, &self);
  }
  else
  {
    if (globals::drag_drop_scrolling)
    {
      state.set_pos(old_state_pos + (scroll_center - mouse_pos));
    }
    else
    {
      state.set_pos(Vector2i(state.get_pos().x - static_cast<int>(static_cast<float>(scroll_center.x - mouse_pos.x) * 0.2f),
                             state.get_pos().y - static_cast<int>(static_cast<float>(scroll_center.y - mouse_pos.y) * 0.2f)));
    }
  }

  if (globals::auto_scrolling && (Display::is_fullscreen() || Display::has_grab()))
  {
    scroll_speed = static_cast<int>(800 * delta);

    if (mouse_pos.x < 10)
    {
      state.set_pos(state.get_pos() - Vector2i(scroll_speed, 0));
    }
    else if (mouse_pos.x > Display::get_width() - 10)
    {
      state.set_pos(state.get_pos() + Vector2i(scroll_speed, 0));
    }

    if (mouse_pos.y < 10)
    {
      state.set_pos(state.get_pos() - Vector2i(0, scroll_speed));
    }
    else if (mouse_pos.y > Display::get_height() - 10)
    {
      state.set_pos(state.get_pos() + Vector2i(0, scroll_speed));
    }
  }
}

void Playfield::on_primary_button_press(int x, int y) {
  x -= rect.left;
  y -= rect.top;

  if(session) {
    Vector2i p = state.screen2world(Vector2i(x,y));
    Vector2i* pp = &p;
    ceu_out_go(&CEUapp, CEU_IN_PLAYFIELD_CLICK, &pp);
  }
}

void
Playfield::on_secondary_button_press(int x, int y)
{
  x -= rect.left;
  y -= rect.top;

  mouse_scrolling = true;
  scroll_center.x = x;
  scroll_center.y = y;

  old_state_pos = state.get_pos();
}

void
Playfield::on_secondary_button_release (int x, int y)
{
  x -= rect.left;
  y -= rect.top;

  mouse_scrolling = false;
}

Vector2i
Playfield::get_pos() const
{
  return Vector2i(static_cast<int>(state.get_pos().x),
                  static_cast<int>(state.get_pos().y));
}

void
Playfield::set_viewpoint(int x, int y)
{
  state.set_pos(Vector2i(x, y));
}

void
Playfield::scroll (int x, int y)
{
  state.set_pos(state.get_pos() + Vector2i(x, y));
}

void
Playfield::update_layout()
{
  state.set_size(rect.get_width(), rect.get_height());
  scene_context->set_rect(rect);
}

/* EOF */
