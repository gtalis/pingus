//  $Id: Display.cc,v 1.1 2000/02/12 20:53:42 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include <ClanLib/core.h>

#include "Display.hh"

void
Display::draw_rect(int x1, int y1, int x2, int y2, float r, float g, float b, float a)
{
  CL_Display::draw_line(x1, y1, x2, y1, r, g, b, a);
  CL_Display::draw_line(x1, y2, x2, y2, r, g, b, a);
  CL_Display::draw_line(x1, y1, x1, y2, r, g, b, a);
  CL_Display::draw_line(x2, y1, x2, y2, r, g, b, a);
}

/* EOF */
