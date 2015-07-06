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

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJ_FACTORY_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJ_FACTORY_HPP

#include <map>
#include <vector>

#include "math/vector3f.hpp"
#include "util/file_reader.hpp"

class WorldObjAbstractFactory;

/** WorldObjFactory which can be used to create all kinds of
    WorldObj's by given its id */
class WorldObjFactory
{
private:
  std::map<std::string, WorldObjAbstractFactory*> factories;

  static WorldObjFactory* instance_;

  WorldObjFactory ();
  void free_factories();

public:
  /** Return the singleton instance */
  static WorldObjFactory* instance ();
  static void deinit();
  /** Register a factory for object creation */
  void register_factory(const std::string& id,
                        WorldObjAbstractFactory* factory);

  /** Create a WorldObj type from a given piece of xml, use the
      'type' property for determinating the object type. */
  std::vector<void*> create(const FileReader& reader);

private:
  WorldObjFactory (const WorldObjFactory&);
  WorldObjFactory& operator= (const WorldObjFactory&);
};

struct WorldObjCeuPackage {
  FileReader* reader;
  void* result;
  WorldObjCeuPackage(const FileReader& r): reader(const_cast<FileReader*>(&r)), result(0) {};
};

struct PrefabPackage {  
  void* object;
  Vector3f pos;
  PrefabPackage(void* o, Vector3f p): object(o), pos(p) {};
};

#endif

/* EOF */
