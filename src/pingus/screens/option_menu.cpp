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

#include "pingus/screens/option_menu.hpp"

#include <sstream>

#include "engine/display/display.hpp"
#include "engine/gui/gui_manager.hpp"
#include "engine/screen/screen_manager.hpp"
#include "engine/sound/sound.hpp"
#include "pingus/config_manager.hpp"
#include "pingus/fonts.hpp"
#include "pingus/gettext.h"
#include "tinygettext/dictionary_manager.hpp"
#include "util/log.hpp"
#include "util/system.hpp"

#include "ceuvars.h"

extern tinygettext::DictionaryManager dictionary_manager;

void OptionMenu::resize(const Size& size_) {
  old_size = size;
  GUIScreen::resize(size_);

  ScreenResizePackage package(this, size_);
  ScreenResizePackage* pp = &package;
  ceu_out_go(&CEUapp, CEU_IN_SCREEN_RESIZE, &pp);
}

/* EOF */
