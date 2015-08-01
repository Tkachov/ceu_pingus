//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
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

#include "engine/gui/rect_component.hpp"

#include "ceuvars.h"

namespace GUI {

void Component::draw(DrawingContext& gc) {
  ComponentDrawPackage package(this, gc);
  ComponentDrawPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_COMPONENT_DRAW, &pp);
}

void Component::update(float delta) {
  ComponentUpdatePackage package(this, delta);
  ComponentUpdatePackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_COMPONENT_UPDATE, &pp);
}

bool Component::is_at(int x, int y) {  
  ComponentIsAtPackage package(this, Vector2i(x, y));
  ComponentIsAtPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_COMPONENT_IS_AT, &pp);
  return package.result;
}

void Component::on_primary_button_press(int x, int y) {
  //Ceu ON_PRIMARY_BUTTON_PRESS
  PositionPackage package(this, Vector2i(x, y));
  PositionPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_ON_PRIMARY_BUTTON_PRESS, &pp);
}

void Component::on_primary_button_release(int x, int y) {
  //Ceu ON_PRIMARY_BUTTON_RELEASE
  PositionPackage package(this, Vector2i(x, y));
  PositionPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_ON_PRIMARY_BUTTON_RELEASE, &pp);
}

void Component::on_secondary_button_press(int x, int y) {
  //Ceu ON_SECONDARY_BUTTON_PRESS
  PositionPackage package(this, Vector2i(x, y));
  PositionPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_ON_SECONDARY_BUTTON_PRESS, &pp);
}
void Component::on_secondary_button_release(int x, int y) {
  //Ceu ON_SECONDARY_BUTTON_RELEASE
  PositionPackage package(this, Vector2i(x, y));
  PositionPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_ON_SECONDARY_BUTTON_RELEASE, &pp);
}

void Component::on_primary_button_click(int x, int y) {
  //Ceu ON_PRIMARY_BUTTON_CLICK
  PositionPackage package(this, Vector2i(x, y));
  PositionPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_ON_PRIMARY_BUTTON_CLICK, &pp);
}

void Component::on_secondary_button_click(int x, int y) {
  //Ceu ON_SECONDARY_BUTTON_CLICK
  PositionPackage package(this, Vector2i(x, y));
  PositionPackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_ON_SECONDARY_BUTTON_CLICK, &pp);
}

RectComponent*
Component::get_parent() const
{
  return parent; 
}

void
Component::set_parent(RectComponent* p)
{
  assert(parent == 0);
  parent = p; 
}

void
Component::grab()
{
  if (parent) 
    parent->parent_grab(this); 
}

void
Component::ungrab()
{
  if (parent)
    parent->parent_ungrab(this); 
}

} // namespace GUI

/* EOF */
