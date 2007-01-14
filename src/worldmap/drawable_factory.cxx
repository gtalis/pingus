//  $Id: drawable_factory.cxx,v 1.2 2003/10/21 11:01:52 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <iostream>
#include "surface_drawable.hxx"
#include "sprite_drawable.hxx"
#include "drawable_factory.hxx"

namespace WorldMapNS {

Drawable*
DrawableFactory::create(FileReader reader)
{
  if (reader.get_name() == "surface")
    {
      return new SurfaceDrawable(reader);
    }
  else
    {
      std::cout << "DrawableFactory::create(): Can't create " << reader.get_name() << std::endl;
      return 0;
    }
}

} // namespace WorldMapNS

/* EOF */
