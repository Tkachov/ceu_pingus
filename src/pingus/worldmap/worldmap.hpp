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

#ifndef HEADER_PINGUS_PINGUS_WORLDMAP_WORLDMAP_HPP
#define HEADER_PINGUS_PINGUS_WORLDMAP_WORLDMAP_HPP

#include <memory>
#include <vector>

#include "engine/display/graphic_context_state.hpp"
#include "pingus/worldmap/pingus_worldmap.hpp"
#include "pingus/worldmap/graph.hpp"

class Font;
class DrawingContext;

namespace WorldmapNS {

typedef int EdgeId;
typedef int NodeId;

class WorldmapStory;
class PathGraph;
class Drawable;
class Pingus;

/** A class for loading, displaying and managing the worldmap. The
    worldmap is basically a multi-layered image and a path
    (bidirectional graph) where a pingu can walk on. Parts of the
    worldmap are hidable and will only get displayed at specific
    events (successfull level completions, etc.). */
class Worldmap
{
private:
  PingusWorldmap worldmap;

  typedef std::vector<Drawable*>   ObjectLst;
  typedef std::vector<Drawable*> DrawableLst;

  GraphicContextState gc_state;

  /** A collection of drawable things, allocation and deallocation
      takes place elsewhere these are only references to other
      objects */
  DrawableLst drawables;

  /** A collection of drawables loaded from the xml file, this list
      gets deleted at the end */
  ObjectLst objects;

public:
  /** Load the given*/
  Worldmap(const Pathname& filename);

  void add_drawable(Drawable* drawable);

private:
  Worldmap(const Worldmap&);
  Worldmap & operator=(const Worldmap&);
};

} // namespace WorldmapNS

#endif

/* EOF */
