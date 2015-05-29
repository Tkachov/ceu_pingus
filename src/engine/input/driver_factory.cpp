//  Pingus - A free Lemmings clone
//  Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmx.de>
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

#include "driver_factory.hpp"

#include "engine/input/core_driver.hpp"
#include "engine/input/sdl_driver.hpp"

#ifdef HAVE_CWIID
#  include "engine/input/wiimote/wiimote_driver.hpp"
#endif 

#ifdef HAVE_XINPUT
#  include "engine/input/xinput/xinput_driver.hpp"
#endif

#ifdef HAVE_LINUXUSBMOUSE
#  include "engine/input/usbmouse/usbmouse_driver.hpp"
#endif

#ifdef HAVE_LINUXEVDEV
#  include "engine/input/evdev/evdev_driver.hpp"
#endif

namespace Input {

Driver*
DriverFactory::create(const std::string& name, Manager* manager)
{
  if (name == "sdl") 
  {
    return new SDLDriver;
  }
  else if (name == "core") 
  {
    return new CoreDriver(manager);
  }
#ifdef HAVE_LINUXUSBMOUSE
  else if (name == "usbmouse") 
  {
    return new USBMouseDriver();
  } 
#endif
#ifdef HAVE_LINUXEVDEV
  else if (name == "evdev") 
  {
    return new EvdevDriver();
  }
#endif
#ifdef HAVE_XINPUT
  else if (name == "xinput") 
  {
    return new XInputDriver();
  } 
#endif
#ifdef HAVE_CWIID
  else if (name == "wiimote") 
  {
    return new WiimoteDriver();
  } 
#endif
  else 
  {
    return 0;
  }
}

} // namespace Input

/* EOF */
