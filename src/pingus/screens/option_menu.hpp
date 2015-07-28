//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_PINGUS_SCREENS_OPTION_MENU_HPP
#define HEADER_PINGUS_PINGUS_SCREENS_OPTION_MENU_HPP

#include <map>
#include "engine/gui/rect_component.hpp"
#include "engine/screen/gui_screen.hpp"
#include "tinygettext/language.hpp"

struct Option {
  GUI::RectComponent* label;
  GUI::RectComponent* control;

  Option(GUI::RectComponent* label_, GUI::RectComponent* control_):
    label(label_), control(control_)
  {}
};

struct LanguageSorter
{
  bool operator()(const tinygettext::Language& lhs,
                  const tinygettext::Language& rhs)
  {
    return lhs.get_name() < rhs.get_name();
  }
};

class OptionMenu: public GUIScreen
{
private:
  tinygettext::Language m_language;
  std::map<std::string, tinygettext::Language> m_language_map;

  Size old_size;

public:
  OptionMenu() {};
  void resize(const Size&);

private:
  OptionMenu (const OptionMenu&);
  OptionMenu& operator= (const OptionMenu&);
};

#endif

/* EOF */
