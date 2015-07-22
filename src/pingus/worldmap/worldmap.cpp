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

#include "pingus/worldmap/worldmap.hpp"

#include <iostream>

#include "engine/sound/sound.hpp"
#include "pingus/gettext.h"
#include "pingus/globals.hpp"
#include "pingus/stat_manager.hpp"
#include "pingus/worldmap/level_dot.hpp"
#include "pingus/worldmap/pingus.hpp"
#include "util/log.hpp"
#include "util/sexpr_file_writer.hpp"
#include "util/pathname.hpp"

#include "ceuvars.h"

unlock_nodes::unlock_nodes(WorldmapNS::PathGraph* g): path_graph(g) {}

void unlock_nodes::operator()(WorldmapNS::Node<WorldmapNS::Dot*>& node)
{
  if (node.data->finished())
  {
    //log_info("Unlocking neightbours of: " << node.data);
    for (std::vector<WorldmapNS::EdgeId>::iterator i = node.next.begin(); i != node.next.end(); ++i)
    {
      WorldmapNS::Edge<WorldmapNS::Path*>& edge = path_graph->graph.resolve_edge(*i);

      // FIXME: This should be identical to node.data->unlock(), but not sure
      path_graph->graph.resolve_node(edge.source).data->unlock();
      path_graph->graph.resolve_node(edge.destination).data->unlock();
    }
  }
}

namespace WorldmapNS {

Worldmap* Worldmap::current_ = 0; 

Worldmap::Worldmap(const Pathname& filename) :
  worldmap(),
  default_node(),
  final_node(),
  pingus(),
  gc_state(),
  path_graph(),
  drawables(),
  objects(),
  mouse_x(0),
  mouse_y(0)
{
  current_ = this;

  worldmap = PingusWorldmap(filename);
}

Worldmap::~Worldmap()
{
  for (auto i = drawables.begin (); i != drawables.end (); ++i)
  {
    delete (*i);
  }

  Worldmap* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_WORLDMAP, &self);
}

void
Worldmap::add_drawable(Drawable* drawable)
{
  drawables.push_back(drawable);
}

// Determine starting node
void
Worldmap::set_starting_node()
{
  // See if the user has played this map before.  If not, use the <default-node>
  // tag from the XML file.
  NodeId id;
  std::string node_name;

  if (StatManager::instance()->get_string(worldmap.get_short_name() + "-current-node", node_name))
  {
    // Just in case that level doesn't exist, look it up.
    id = path_graph->lookup_node(node_name);
    if (id == NoNode)
      id = default_node;
  }
  else
    id = default_node;
                
  pingus->set_position(id);

  LevelDot* leveldot = dynamic_cast<LevelDot*>(path_graph->get_dot(id));
  if (leveldot)
  {
    leveldot->unlock();
  }
}

} // namespace WorldmapNS

/* EOF */
