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

#include "pingus/worldobjs/teleporter_target.hpp"

#include <iostream>
#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"
#include "pingus/resource.hpp"

namespace WorldObjs {

TeleporterTarget::TeleporterTarget(const FileReader& reader) :
  WorldObj(reader),
  pos(),
  sprite("worldobjs/teleportertarget")
{
  reader.read_vector("position", pos);
}

float
TeleporterTarget::get_z_pos () const
{
  return pos.z;
}

void
TeleporterTarget::draw (SceneContext& gc)
{
  gc.color().draw(sprite, pos);
}

void
TeleporterTarget::update ()
{
  sprite.update();
}

void
TeleporterTarget::teleporter_used()
{
  sprite.restart();
}

} // namespace WorldObjs

/* EOF */