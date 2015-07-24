//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_PINGUS_WORLDMAP_PATH_GRAPH_HPP
#define HEADER_PINGUS_PINGUS_WORLDMAP_PATH_GRAPH_HPP

#include <map>
#include <vector>

#include "math/vector3f.hpp"
#include "pingus/worldmap/graph.hpp"
#include "pingus/worldmap/path.hpp"
#include "pingus/worldmap/pathfinder.hpp"
#include "util/file_reader.hpp"

namespace WorldmapNS {

/** This class represents the walkable path on the Worldmap */
class PathGraph
{
public:
  // FIXME: Memory leak? Where do we free stuff data inside the graph?
  // FIXME: shouldn't be public
  Graph<void*, Path*> graph;

  std::vector<void*> dots;
  typedef std::vector<Pathfinder<void*, Path*>* > PFinderCache;
  PFinderCache pathfinder_cache;
private:

  // FIXME: This could/should probally be moved inside the graph (or not?!)
  /** Map to look up node names and get the coresponding id's */
  std::map<std::string, NodeId> node_lookup;

  /** Map to look up edge names and get the corresponding id's */
  std::map<std::string, EdgeId> edge_lookup;

public:
  /** @param worldmap is a pointer to the worldmap that holds this
      PathGraph, it is used so that the PathGraph can insert its
      drawables into the world */
  PathGraph();
  ~PathGraph();

  /** @return a list of positions to walk to reach node \a end, by
      starting from \a start */
  PathfinderResult get_path(NodeId start, NodeId end);

  EdgeId lookup_edge(const std::string& name);
  NodeId lookup_node(const std::string& name);

  std::string lookup_node(EdgeId id);
  std::string lookup_edge(NodeId id);

private:
  PathGraph (const PathGraph&);
  PathGraph& operator= (const PathGraph&);
};

} // namespace WorldmapNS

#endif

/* EOF */
