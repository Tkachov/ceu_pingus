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

  NodeId default_node;
  NodeId final_node;

  Pingus* pingus;

  GraphicContextState gc_state;

  /** The graph that represents the path on the map */
  std::unique_ptr<PathGraph> path_graph;

  /** A collection of drawable things, allocation and deallocation
      takes place elsewhere these are only references to other
      objects */
  DrawableLst drawables;

  /** A collection of drawables loaded from the xml file, this list
      gets deleted at the end */
  ObjectLst objects;

  int mouse_x;
  int mouse_y;

public:
  /** Load the given*/
  Worldmap(const Pathname& filename);
  ~Worldmap();

  Pingus* get_pingus() { return pingus; }

  void add_drawable(Drawable* drawable);

private:
  /** Sets the starting level on the worldmap.  Either take it from the StatManager
      or use the "default-node" option from the XML file */
  void set_starting_node();

  static Worldmap* current_; 

  Worldmap(const Worldmap&);
  Worldmap & operator=(const Worldmap&);
  
public:
  static Worldmap* current() { return current_; }
};

} // namespace WorldmapNS

struct unlock_nodes
{
  WorldmapNS::PathGraph* path_graph;

  unlock_nodes(WorldmapNS::PathGraph* g);
  void operator()(WorldmapNS::Node<WorldmapNS::Dot*>& node);
};

#endif

/* EOF */
