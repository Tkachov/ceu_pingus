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

#include "pingus/screens/story_screen.hpp"
#include "ceuvars.h"

StoryScreen::StoryScreen(const FileReader& reader, bool credits):
  story(new WorldmapNS::WorldmapStory(reader)),
  m_credits(credits)
{
  StoryScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_NEW_STORY_SCREEN, &self);
}

StoryScreen::~StoryScreen() {
  StoryScreen* self = this;
  ceu_out_go(&CEUapp, CEU_IN_DELETE_STORY_SCREEN, &self);
}

/* EOF */
