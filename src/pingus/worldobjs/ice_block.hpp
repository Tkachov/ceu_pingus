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

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_ICE_BLOCK_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_ICE_BLOCK_HPP

#include "math/vector3f.hpp"
#include "pingus/collision_mask.hpp"
#include "pingus/worldobj.hpp"

namespace WorldObjsData {
class IceBlockData;
}

namespace WorldObjs {

class IceBlock : public WorldObj
{
private:
  /** The number of iceblocks, only complete blocks are supported */
  int width;
  
  Sprite block_sur;
  CollisionMask block_sur_cmap;

public:
  IceBlock(const FileReader& reader);
  ~IceBlock();

  void on_startup ();

private:
  IceBlock (const IceBlock&);
  IceBlock& operator= (const IceBlock&);
};

} // namespace WorldObjs

#endif

/* EOF */
