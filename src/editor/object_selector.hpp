/*  $Id$
**   __      __ __             ___        __   __ __   __
**  /  \    /  \__| ____    __| _/_______/  |_|__|  | |  |   ____
**  \   \/\/   /  |/    \  / __ |/  ___/\   __\  |  | |  | _/ __ \
**   \        /|  |   |  \/ /_/ |\___ \  |  | |  |  |_|  |_\  ___/
**    \__/\  / |__|___|  /\____ /____  > |__| |__|____/____/\___  >
**         \/          \/      \/    \/                         \/
**  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
**  02111-1307, USA.
*/

#ifndef HEADER_OBJECT_SELECTOR_HPP
#define HEADER_OBJECT_SELECTOR_HPP

#include "gui/component.hpp"

namespace Editor {

class EditorScreen;

/** */
class ObjectSelector : public GUI::Component
{
private:
  EditorScreen* editor;
  Vector2i button_pos;
public:
  typedef void (ObjectSelector::*Callback)();
  Callback callback;

  ObjectSelector(EditorScreen* editor);
  ~ObjectSelector();

  void draw (DrawingContext& gc);
  void update (float delta);

  bool is_at (int x, int y);
  
  void add_button(const std::string& image, const std::string& tooltip = "", Callback callback = 0);
private:
  ObjectSelector (const ObjectSelector&);
  ObjectSelector& operator= (const ObjectSelector&);
};

} // namespace Editor

#endif

/* EOF */
