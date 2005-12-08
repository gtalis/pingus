//  $Id: editor_viewport.cxx,v 1.00 2005/11/09 23:41:12 Jave27 Exp $
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

#include <ClanLib/display.h>
#include <vector>
#include <string>
#include <iostream>
#include "../vector.hxx"
#include "../display/drawing_context.hxx"
#include "../graphic_context_state.hxx"
#include "editor_viewport.hxx"
#include "editor_screen.hxx"
#include "xml_level.hxx"
#include "level_objs.hxx"

namespace Pingus {
namespace Editor {

// Constructor
EditorViewport::EditorViewport(EditorScreen* e) :
	scene_context(new SceneContext()),
	editor(e),
	bg_surface(0),
	state(CL_Display::get_width(), CL_Display::get_height()),
	autoscroll(true)
{
	// FIXME: Hardcoded values should be determined by level size
	state.set_limit(CL_Rect(-30, -50, 1600, 1300));
	state.set_pos(CL_Pointf(0, 0));
}

// Destructor
EditorViewport::~EditorViewport ()
{
	if (bg_surface) delete bg_surface;
}

// When someone right-clicks inside the viewport
void
EditorViewport::on_secondary_button_click(int x, int y)
{
	// FIXME: Hardcoded 15 & 25 should probably be dynamic
	std::cout << "Right-click at " << x - 15 - (state.get_width()/2 - state.get_pos().x) << ", " 
		<< y - 25 - (state.get_height()/2 - state.get_pos().y) << std::endl;
}

// Draws all of the objects in the viewport and the background (if any)
void
EditorViewport::draw(DrawingContext &gc)
{
	scene_context->clear();
	state.push(*scene_context);
	
	// Now, draw all of the objects

	// FIXME: Should draw the background(s) over the whole viewport (stretched or tiled)
	if (bg_surface)
		scene_context->color().draw(*bg_surface, Vector());

	// FIXME: This is obviously not correct, but it's just a proof of concept now.
	// Draw the level objects
	std::vector<LevelObj*> objs = editor->get_level()->get_objects();
	for (unsigned i = 0; i < objs.size(); i++)
		objs[i]->draw(scene_context->color());

	state.pop(*scene_context);
	gc.draw(new SceneContextDrawingRequest(scene_context, CL_Vector(0, 0, -5000)));
}

// Returns true if the viewport is at the x,y coordinate
bool
EditorViewport::is_at(int x, int y)
{
	// FIXME: Should return true everywhere except for on the panel
	return true;
}

// 
void
EditorViewport::on_pointer_move(int x, int y)
{
	mouse_at = Vector(float(x), float(y));
}

void
EditorViewport::update(float delta)
{
	// Autoscroll if necessary
	if (autoscroll)
	{
		const int autoscroll_border = 10;
		if (autoscroll)
		{
			if (mouse_at.x < autoscroll_border)
				state.set_pos(state.get_pos() - CL_Pointf(5, 0));
			else if ((float)CL_Display::get_width() - mouse_at.x < autoscroll_border)
				state.set_pos(state.get_pos() + CL_Pointf(5, 0));
			else if (mouse_at.y < autoscroll_border)
				state.set_pos(state.get_pos() - CL_Pointf(0, 5));
			else if ((float)CL_Display::get_height() - mouse_at.y < autoscroll_border)
				state.set_pos(state.get_pos() + CL_Pointf(0, 5));
		}
	}
}
} // Editor namespace
} // Pingus namespace

/* EOF */