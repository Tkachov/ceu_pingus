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

#include <stdexcept>

#include "pingus/globals.hpp"
#include "pingus/worldmap/path_drawable.hpp"
#include "pingus/worldmap/worldmap.hpp"
#include "util/log.hpp"
#include "util/raise_exception.hpp"

namespace WorldmapNS {

PathGraph::PathGraph(Worldmap* arg_worldmap):
  worldmap(arg_worldmap),
  graph(),
  dots(),
  pathfinder_cache(),
  node_lookup(),
  edge_lookup()
{}

void delete_Path(Edge<Path*> x)
{
  ///delete x.data;
}

PathGraph::~PathGraph()
{
  graph.for_each_edge(delete_Path);
  for(PFinderCache::iterator i = pathfinder_cache.begin();
      i != pathfinder_cache.end(); ++i)
    delete *i;
}

PathfinderResult
PathGraph::get_path(NodeId start_id, NodeId end_id)
{
  Pathfinder<Drawable*,Path*>*& pfinder = pathfinder_cache[start_id];

  if (!pfinder)
  {
    pfinder = new Pathfinder<Drawable*, Path*>(graph, start_id);
    pathfinder_cache[start_id] = pfinder;
  }

  return pfinder->get_result(end_id);
}

EdgeId
PathGraph::lookup_edge(const std::string& name)
{
  std::map<std::string, EdgeId>::iterator i = edge_lookup.find(name);
  if (i == edge_lookup.end())
  {
    log_info("Couldn't find EdgeId for: %1%", name);
    return NoEdge;
  }
  else
  {
    return i->second;
  }
}

NodeId
PathGraph::lookup_node(const std::string& name)
{
  std::map<std::string, NodeId>::iterator i = node_lookup.find(name);
  if (i == node_lookup.end())
  {
    log_info("Couldn't find NodeId for: %1%", name);
    return NoNode;
  }
  else
  {
    return i->second;
  }
}

std::string
PathGraph::lookup_node(EdgeId id)
{
  for (std::map<std::string, NodeId>::iterator i = node_lookup.begin();
       i != node_lookup.end(); ++i)
  {
    if (i->second == id)
    {
      return i->first;
    }
  }
  log_info("PathGraph: Couldn't find id: %1%", id);
  return "error_node";
}

std::string
PathGraph::lookup_edge(NodeId id)
{
  for (std::map<std::string, EdgeId>::iterator i = node_lookup.begin();
       i != node_lookup.end(); ++i)
  {
    if (i->second == id)
    {
      return i->first;
    }
  }
  log_info("PathGraph: Couldn't find id: %1%", id);
  return "error_node";
}

} // namespace WorldmapNS

/* EOF */
