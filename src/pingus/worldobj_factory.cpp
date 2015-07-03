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

#include "pingus/worldobj_factory.hpp"

#include <stdexcept>

#include "pingus/prefab_file.hpp"
#include "util/log.hpp"
#include "util/overrride_file_reader.hpp"

#include "ceuvars.h"

WorldObjFactory* WorldObjFactory::instance_ = 0;

/** WorldObjAbstractFactory, interface for creating factories */
class WorldObjAbstractFactory
{
public:
  WorldObjAbstractFactory (const std::string& id) {
    WorldObjFactory::instance ()->register_factory (id, this);
  }

  virtual ~WorldObjAbstractFactory() {}

  virtual std::vector<WorldObj*> create(const FileReader& reader) =0;

private:
  WorldObjAbstractFactory (const WorldObjAbstractFactory&);
  WorldObjAbstractFactory& operator= (const WorldObjAbstractFactory&);
};

/** Template to create factories, usage:
    new WorldObjFactoryImpl<"liquid", Liquid>; */
template<class T>
class WorldObjFactoryImpl : public WorldObjAbstractFactory
{
public:
  WorldObjFactoryImpl (const std::string& id)
    : WorldObjAbstractFactory (id) {}

  std::vector<WorldObj*> create(const FileReader& reader) {
    std::vector<WorldObj*> lst;
    lst.push_back(new T(reader));
    return lst;
  }

private:
  WorldObjFactoryImpl (const WorldObjFactoryImpl&);
  WorldObjFactoryImpl& operator= (const WorldObjFactoryImpl&);
};

/** not a template to create Ceu factories, usage:
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_CLASS_NAME, "id"); */

class WorldObjCeuFactoryImpl: public WorldObjAbstractFactory {
  int EVENT;
public:
  WorldObjCeuFactoryImpl(int ev, const std::string& id): WorldObjAbstractFactory(id), EVENT(ev) {}

  std::vector<WorldObj*> create(const FileReader& reader) {
    std::vector<WorldObj*> lst;

    WorldObjCeuPackage package(reader);
    WorldObjCeuPackage* pp = &package;
    ceu_out_go(&CEUapp, EVENT, &pp);

    if(package.result)
      lst.push_back(package.result);
    else
      log_error("Ceu factory failed to create new WorldObj");

    return lst;
  }

private:
  WorldObjCeuFactoryImpl(const WorldObjCeuFactoryImpl&);
  WorldObjCeuFactoryImpl& operator=(const WorldObjCeuFactoryImpl&);
};

class WorldObjGroupFactory : public WorldObjAbstractFactory
{
public:
  WorldObjGroupFactory (const std::string& id) :
    WorldObjAbstractFactory(id)
  {}

  virtual ~WorldObjGroupFactory() {}

  virtual std::vector<WorldObj*> create(const FileReader& reader) {
    std::vector<WorldObj*> group;

    FileReader objects = reader.read_section("objects");
    std::vector<FileReader> sections = objects.get_sections();
    for(auto it = sections.begin(); it != sections.end(); ++it)
    {
      std::vector<WorldObj*> objs = WorldObjFactory::instance()->create(*it);
      for(auto obj = objs.begin(); obj != objs.end(); ++obj)
      {
        if (*obj)
        {
          group.push_back(*obj);
        }
      }
    }
    return group;
  }

private:
  WorldObjGroupFactory (const WorldObjGroupFactory&);
  WorldObjGroupFactory& operator= (const WorldObjGroupFactory&);
};

class WorldObjPrefabFactory : public WorldObjAbstractFactory
{
public:
  WorldObjPrefabFactory (const std::string& id) :
    WorldObjAbstractFactory(id)
  {}

  virtual ~WorldObjPrefabFactory() {}

  virtual std::vector<WorldObj*> create(const FileReader& reader) {
    std::string name;
    reader.read_string("name", name);

    Vector3f pos;
    reader.read_vector("position", pos);

    PrefabFile prefab = PrefabFile::from_resource(name);
    FileReader overrides;
    reader.read_section("overrides", overrides);

    std::vector<WorldObj*> group;
    const std::vector<FileReader>& objects = prefab.get_objects();
    for(auto it = objects.begin(); it != objects.end(); ++it)
    {
      OverrideFileReader override_reader(*it, overrides);

      std::vector<WorldObj*> objs = WorldObjFactory::instance()->create(override_reader);
      for(auto obj = objs.begin(); obj != objs.end(); ++obj)
      {
        if (*obj)
        {
          (*obj)->set_pos((*obj)->get_pos() + pos);
          group.push_back(*obj);
        }
      }
    }
    return group;
  }

private:
  WorldObjPrefabFactory (const WorldObjPrefabFactory&);
  WorldObjPrefabFactory& operator= (const WorldObjPrefabFactory&);
};

WorldObjFactory::WorldObjFactory() :
  factories()
{
  // Register all WorldObj's
}

WorldObjFactory*
WorldObjFactory::instance()
{
  if ( ! instance_)
  {
    instance_ = new WorldObjFactory ();

    // Registring Factories
    new WorldObjGroupFactory("group");
    new WorldObjPrefabFactory("prefab");

    new WorldObjCeuFactoryImpl(CEU_IN_NEW_LIQUID, "liquid");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_HOTSPOT, "hotspot");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_ENTRANCE, "entrance");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_EXIT, "exit");

    // traps
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_FAKE_EXIT, "fake_exit");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_GUILLOTINE, "guillotine");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_HAMMER, "hammer");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_LASER_EXIT, "laser_exit");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_SMASHER, "smasher");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_SPIKE, "spike");

    // Special Objects
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_SWITCH_DOOR_SWITCH, "switchdoor-switch");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_SWITCH_DOOR_DOOR, "switchdoor-door");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_ICE_BLOCK, "iceblock");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_CONVEYOR_BELT, "conveyorbelt");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_TELEPORTER, "teleporter");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_TELEPORTER_TARGET, "teleporter-target");

    // Backgrounds
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_SURFACE_BACKGROUND, "surface-background");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_STARFIELD_BACKGROUND, "starfield-background");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_SOLID_COLOR_BACKGROUND, "solidcolor-background");

    // Weather
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_SNOW_GENERATOR, "snow-generator");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_RAIN_GENERATOR, "rain-generator");
    // Weather-Backward compability
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_SNOW_GENERATOR, "snow");
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_RAIN_GENERATOR, "rain");

    // Groundpieces
    new WorldObjCeuFactoryImpl(CEU_IN_NEW_GROUNDPIECE, "groundpiece");
  }

  return instance_;
}

void WorldObjFactory::deinit()
{
  if (instance_)
  {
    instance_->free_factories();
    delete instance_;
    instance_ = 0;
  }
}

std::vector<WorldObj*>
WorldObjFactory::create(const FileReader& reader)
{
  std::map<std::string, WorldObjAbstractFactory*>::iterator it = factories.find(reader.get_name());

  if (it == factories.end())
  {
    log_error("invalid id: '%1%'", reader.get_name());
    return std::vector<WorldObj*>();
  }
  else
  {
    return it->second->create(reader);
  }
}

void
WorldObjFactory::register_factory (const std::string& id,
                                   WorldObjAbstractFactory* factory)
{
  factories[id] = factory;
}

void
WorldObjFactory::free_factories()
{
  for (std::map<std::string, WorldObjAbstractFactory*>::iterator i = factories.begin(); i != factories.end(); ++i)
  {
    delete i->second;
  }
}

/* EOF */
