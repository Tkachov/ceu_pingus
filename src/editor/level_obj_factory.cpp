//  Pingus - A free Lemmings clone
//  Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmx.de>
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

#include "editor/level_obj_factory.hpp"

#include "editor/generic_level_obj.hpp"
#include "editor/group_level_obj.hpp"
#include "util/file_reader.hpp"

namespace Editor {

LevelObjPtr
LevelObjFactory::create(const FileReader& reader)
{    
  if (reader.get_name() == "group")
  {
    std::shared_ptr<GroupLevelObj> group = std::make_shared<GroupLevelObj>();

    FileReader objects = reader.read_section("objects");
    std::vector<FileReader> sections = objects.get_sections();
    for(auto it = sections.begin(); it != sections.end(); ++it)
    {
      LevelObjPtr obj = create(*it);
      if (obj)
      {
        group->add_child(obj);
      }
    }
    return group;
  }
  if (reader.get_name() == "prefab")
  {  
    std::string name;
    reader.read_string("name", name);

    Vector3f p;
    reader.read_vector("position", p);

    std::shared_ptr<GroupLevelObj> group = GroupLevelObj::from_prefab(name);
    if (!group)
    {
      return LevelObjPtr();
    }
    else
    {
      FileReader overrides;
      if (reader.read_section("overrides", overrides))
        group->set_overrides(overrides);

      group->set_orig_pos(p);
      group->set_pos(p);
      return group;
    }
  }
  else
  {
    // Temporary objects
    unsigned attribs;
    Vector3f p;
    Color    tmp_color;
    ResDescriptor desc;
    std::string   tmp_str;
    int   tmp_int;
    float tmp_float;
    bool  tmp_bool;

    // Create new object
    LevelObjPtr obj = std::make_shared<GenericLevelObj>(reader.get_name());
    attribs = obj->get_attribs();

    // All objects have a position - get that.
    if (!reader.read_vector("position", p))
    { // Workaround for lack of position for background
      if (reader.get_name() == "surface-background")
        p = Vector3f(0.f, 0.f, -150.f);
    }

    obj->set_orig_pos(p);
    obj->set_pos(p);

    // Get optional attributes based on the attribs value
    if (attribs & HAS_SPRITE)
    {
      reader.read_desc("surface", desc);
      obj->set_res_desc(desc);
    }
    if (attribs & HAS_TYPE)
    {   
      reader.read_string("type", tmp_str);
      obj->set_type(tmp_str);
    }
    if (attribs & HAS_GPTYPE)
    {   
      reader.read_string("type", tmp_str);
      obj->set_ground_type(tmp_str);
    }
    if (attribs & HAS_SPEED)
    {
      reader.read_int("speed", tmp_int);
      obj->set_speed(tmp_int);
    }
    if (attribs & HAS_REPEAT)
    {
      if (!reader.read_int("repeat", tmp_int))
        reader.read_int("width", tmp_int);
      obj->set_repeat(tmp_int);
    }
    if (attribs & HAS_PARALLAX)
    {
      reader.read_float("parallax", tmp_float);
      obj->set_parallax(tmp_float);
    }
    if (attribs & HAS_OWNER)
    {
      reader.read_int("owner-id", tmp_int);
      obj->set_owner(tmp_int);
    }
    if (attribs & HAS_DIRECTION)
    {
      reader.read_string("direction", tmp_str);
      obj->set_direction(tmp_str);
    }
    if (attribs & HAS_COLOR)
    {
      if (!reader.read_colori("colori", tmp_color))
        reader.read_colorf("color", tmp_color);
      obj->set_color(tmp_color);
    }
    if (attribs & HAS_SCROLL)
    {
      reader.read_float("scroll-x", tmp_float);
      obj->set_scroll_x(tmp_float);
      reader.read_float("scroll-y", tmp_float);
      obj->set_scroll_y(tmp_float);
    }
    if (attribs & HAS_STRETCH)
    {
      reader.read_bool("stretch-x", tmp_bool);
      obj->set_stretch_x(tmp_bool);
      reader.read_bool("stretch-y", tmp_bool);
      obj->set_stretch_y(tmp_bool);
      reader.read_bool("keep-aspect", tmp_bool);
      obj->set_keep_aspect(tmp_bool);
    }
    if (attribs & HAS_PARA)
    {
      reader.read_float("para-x", tmp_float);
      obj->set_para_x(tmp_float);
      reader.read_float("para-y", tmp_float);
      obj->set_para_y(tmp_float);
    }
    if (attribs & HAS_RELEASE_RATE)
    {
      reader.read_int("release-rate", tmp_int);
      obj->set_release_rate(tmp_int);
    }
    if (attribs & HAS_ID)
    {
      reader.read_string("id", tmp_str);
      obj->set_id(tmp_str);
    }
    if (attribs & HAS_TARGET_ID)
    {
      reader.read_string("target-id", tmp_str);
      obj->set_target_id(tmp_str);
    }

    if (attribs & HAS_STARFIELD)
    {
      reader.read_int("small-stars", tmp_int);
      obj->set_small_stars(tmp_int);

      reader.read_int("middle-stars", tmp_int);
      obj->set_middle_stars(tmp_int);

      reader.read_int("large-stars", tmp_int);
      obj->set_large_stars(tmp_int);
    }
    if (attribs & HAS_HEIGHT)
    {
      reader.read_int("height", tmp_int);
      obj->set_height(tmp_int);
    }

    return obj;
  }
}

} // namespace Editor

/* EOF */
