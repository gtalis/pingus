//  $Id: exit_data.hxx,v 1.6 2002/09/27 11:26:43 torangan Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_EXIT_DATA_HXX
#define HEADER_PINGUS_EXIT_DATA_HXX

#include <ClanLib/Core/Math/cl_vector.h>
#include "res_descriptor.hxx"
#include "worldobj_data.hxx"

#include "libxmlfwd.hxx"

///
class ExitData : public WorldObjData
{
public:
  CL_Vector pos;
  ResDescriptor desc;
  int owner_id;
  
  /** Causes the entrance handling to fall back to the old position
      treatment, that means the position is treaten as the upper/left
      corner of the exit surface. The new handling treats the position
      of the bottom/center position of the surface, which is much more
      convenience. */
  bool use_old_pos_handling;

public:
  ExitData() { clean (); }
  ExitData (xmlDocPtr doc, xmlNodePtr cur);
  
  ExitData (const ExitData& old);
  ExitData& operator= (const ExitData& old);

  /// Reset the values to default
  void clean(void) 
  { 
    owner_id = 0; 
    use_old_pos_handling = true;
  }

  void write_xml(std::ostream&);
  
  WorldObj* create_WorldObj();
  EditorObjLst create_EditorObj();
};

#endif

/* EOF */




