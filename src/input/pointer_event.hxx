//  $Id: pointer_event.hxx,v 1.4 2002/09/27 11:26:47 torangan Exp $
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

#ifndef HEADER_PINGUS_INPUT_POINTER_EVENT_HXX
#define HEADER_PINGUS_INPUT_POINTER_EVENT_HXX

#include "event.hxx"

namespace Input {

  enum Type { standard };

  class PointerEvent : public Event {
  
    public:
      Type  type;
      float x, y;
           
    public:
      PointerEvent (Type type_, float x_, float y_) : type(type_), x(x_), y(y_) { }
      
      EventType get_type () { return PointerEventType; }
      
    private:
      PointerEvent (const PointerEvent&);
      PointerEvent& operator= (const PointerEvent&);
  };

}

#endif

/* EOF */
