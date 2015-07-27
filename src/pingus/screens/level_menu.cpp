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

#include "pingus/screens/level_menu.hpp"

#include "pingus/gettext.h"
#include "pingus/globals.hpp"
#include "util/log.hpp"
#include "util/system.hpp"

#include "ceuvars.h"

struct LevelsetPrioritySorter
{
  bool operator()(Levelset* lhs, Levelset* rhs) const
  {
    return lhs->get_priority() > rhs->get_priority();
  }
};
      
void fill_levelsets(std::vector<Levelset*>& levelsets) {
  auto directory = Pathname("levelsets", Pathname::DATA_PATH).opendir("*.levelset");
  for(auto i = directory.begin(); i != directory.end(); ++i)
  {
    try 
    {
      std::unique_ptr<Levelset> levelset = Levelset::from_file(*i);
      if (!levelset->get_developer_only() || globals::developer_mode)
      {
        levelsets.push_back(levelset.release());
      }
    }
    catch(const std::exception& err)
    {
      log_error("%1%", err.what());
    }
  }

  if (globals::developer_mode)
  {
    levelsets.push_back(Levelset::from_directory(_("Under Construction"),
                                                 _("Untested, unpolished and broken levels"),
                                                 "levelsets/underconstruction",
                                                 Pathname("levels", Pathname::DATA_PATH)).release());
  }

  std::sort(levelsets.begin(), levelsets.end(), LevelsetPrioritySorter());
}

LevelMenu::LevelMenu() {
  LevelMenu* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_LEVEL_MENU, &self);  

  resize(Display::get_size());
}

LevelMenu::~LevelMenu() {
  LevelMenu* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_LEVEL_MENU, &self);
}

/* EOF */
