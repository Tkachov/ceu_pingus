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

#ifndef HEADER_PINGUS_PINGUS_COMPONENTS_PLAYFIELD_HPP
#define HEADER_PINGUS_PINGUS_COMPONENTS_PLAYFIELD_HPP

#include <memory>

#include "engine/display/graphic_context_state.hpp"
#include "engine/gui/rect_component.hpp"

class ButtonPanel;
class Controller;
class View;

/** This class encapsulates all the different Views */
class Playfield : public GUI::RectComponent
{
private:
  std::unique_ptr<SceneContext> scene_context;
  GraphicContextState state;

public:
  Playfield(const Rect& rect);
  virtual ~Playfield();

private:
  Playfield (const Playfield&);
  Playfield& operator= (const Playfield&);
};

#endif

/* EOF */
