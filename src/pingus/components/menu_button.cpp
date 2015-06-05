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

#include "pingus/components/menu_button.hpp"

#include "engine/display/drawing_context.hpp"
#include "engine/sound/sound.hpp"
#include "math/vector2i.hpp"
#include "pingus/screens/pingus_menu.hpp"

#include "ceuvars.h"

MenuButton::MenuButton(PingusMenu* menu_, const Vector2i& pos_,
                       const std::string& text_, const std::string& desc_):
  menu(menu_),
  surface_p(Sprite("core/menu/menuitem")),
  highlight(Sprite("core/menu/menuitem_highlight")),
  font(Fonts::pingus_small),
  font_large(Fonts::chalk_large),
  x_pos(pos_.x),
  y_pos(pos_.y),
  desc(desc_),
  text(text_),
  mouse_over(false),
  pressed(false) {
    void* self = this;
    ceu_out_go(&CEUapp, CEU_IN_NEW_MENUBUTTON, &self);
  }

MenuButton::~MenuButton() {
  void* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_MENUBUTTON, &self);
}

void MenuButton::on_click () {
  menu->on_click(this);
}

void MenuButton::draw(DrawingContext& gc) {
  if(mouse_over) {
    gc.draw(surface_p,Vector2i(x_pos, y_pos));
    gc.draw(highlight, Vector2i(x_pos, y_pos));
    gc.print_center(font_large, Vector2i(x_pos, y_pos - 28), text);
  } else {
    gc.draw(surface_p, Vector2i(x_pos, y_pos));
    gc.print_center(font_large, Vector2i(x_pos, y_pos - 28), text);
  }
}

void MenuButton::update(float delta) {}

void MenuButton::on_pointer_enter() {}

void MenuButton::on_pointer_leave() {}

void MenuButton::on_pointer_press() {
  pressed = true;
}

void MenuButton::on_pointer_release() {
  pressed = false;
}

bool MenuButton::is_at(int x, int y) {
  return (x > x_pos - int(surface_p.get_width()) / 2
          && x < x_pos + int(surface_p.get_width()) / 2
          && y > y_pos - int(surface_p.get_height()) / 2
          && y < y_pos + int(surface_p.get_height()) / 2);
}

void MenuButton::set_pos(int x, int y) {
  x_pos = x;
  y_pos = y;
}

/* EOF */
