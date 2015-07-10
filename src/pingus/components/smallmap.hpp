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

#ifndef HEADER_PINGUS_PINGUS_COMPONENTS_SMALLMAP_HPP
#define HEADER_PINGUS_PINGUS_COMPONENTS_SMALLMAP_HPP

#include "engine/display/sprite.hpp"
#include "engine/gui/rect_component.hpp"

class Playfield;
class Server;
class Vector3f;

/** This is the map that appears in the corner of the screen */
class SmallMap : public GUI::RectComponent
{
private:
  Server*    server;
  Playfield* playfield;

  /** Graphic surface of the exit */
  Sprite exit_sur;

  /** Graphic surface of the entrance */
  Sprite entrance_sur;

  /** Indicates whether the playfield should can be scrolled around depending
      on the position of the cursor in the small map */
  bool scroll_mode;

  bool has_focus;

  /** Pointer to the current GC, only valid inside draw() */
  DrawingContext* gc_ptr;

public:
  SmallMap(Server*, Playfield*, const Rect& rect);
  virtual ~SmallMap();

  /*{ @name Stuff called from the GUIManager */  
  void on_primary_button_release(int x, int y);  

  // Events
  void on_pointer_enter ();
  void on_pointer_leave ();

  bool is_at (int x, int y);
  bool mouse_over();
  /*}*/

private:
  SmallMap (const SmallMap&);
  SmallMap& operator= (const SmallMap&);
};

#endif

/* EOF */
