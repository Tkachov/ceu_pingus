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

#include "pingus/components/action_button.hpp"

#include "engine/display/drawing_context.hpp"
#include "pingus/screens/game_session.hpp"
#include "pingus/server.hpp"
#include "pingus/world.hpp"

#include "stdio.h"

#include "ceuvars.h"

ArmageddonButton::ArmageddonButton(Server* s, int x, int y) :
  RectComponent(Rect(Vector2i(x, y), Size(38, 60))),
  server(s),
  sprite(),
  background  ("core/buttons/hbuttonbgb"),
  backgroundhl("core/buttons/hbuttonbg")
{
  sprite = Sprite("core/buttons/armageddon_anim");

  void* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_ARMAGEDDONBUTTON, &self);
}

ArmageddonButton::~ArmageddonButton() {
  void* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_ARMAGEDDONBUTTON, &self);
}

void
ArmageddonButton::draw (DrawingContext& gc)
{
  Vector2i pos(rect.left, rect.top);

  if (server->get_world()->check_armageddon ())
  {
    gc.draw(backgroundhl, pos);
    gc.draw(sprite, pos);
  }
  else
  {
    gc.draw(background, pos);

    sprite.set_frame(7);
    gc.draw(sprite, pos);
  }
}

void
ArmageddonButton::update (float delta)
{
  sprite.update(delta);
}

ForwardButton::ForwardButton(GameSession* s, int x, int y) :
  RectComponent(Rect(Vector2i(x, y), Size(38, 60))),
  session(s),
  surface(),
  background ("core/buttons/hbuttonbgb"),
  backgroundhl("core/buttons/hbuttonbg")
{
  surface = Sprite("core/buttons/fast_forward");

  void* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_FORWARDBUTTON, &self);
}

ForwardButton::~ForwardButton() {
  void* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_FORWARDBUTTON, &self);
}

void
ForwardButton::draw (DrawingContext& gc)
{
  Vector2i pos(rect.left, rect.top);

  if (session->get_fast_forward())
  {
    gc.draw(backgroundhl, pos);
  }
  else
  {
    gc.draw(background, pos);
  }

  gc.draw(surface, pos);
}

PauseButton::PauseButton(GameSession* s, int x, int y) :
  RectComponent(Rect(Vector2i(x, y), Size(38, 60))),
  session(s),
  surface(),
  background ("core/buttons/hbuttonbgb"),
  backgroundhl("core/buttons/hbuttonbg")
{
  surface = Sprite("core/buttons/pause");

  void* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_PAUSEBUTTON, &self);
}

PauseButton::~PauseButton() {
  void* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_PAUSEBUTTON, &self);
}

void
PauseButton::draw (DrawingContext& gc)
{
  Vector2i pos(rect.left, rect.top);

  if (session->get_pause())
  {
    gc.draw(backgroundhl, pos);
  }
  else
  {
    gc.draw(background, pos);
  }

  gc.draw(surface, pos);
}

/* EOF */
