//  $Id: Console.cc,v 1.16 2001/04/04 10:21:16 grumbel Exp $
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

#include <algorithm>
#include <cstdio>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "PingusResource.hh"
#include "Console.hh"

using namespace std;

// Globale console
Console console;
Console::Endl Console::endl;

Console::Console()
{
  is_init = false;
  is_visible = false;
  current_pos = 0;
  number_of_lines = 10;
}

Console::~Console()
{
}

// We are not initialising the console in the constructor, 'cause
// that doesn't work (ClanLib hasn't init the display at that point) void
void
Console::init()
{
  // std::cout << "Console: Init..." << std::endl;
  font = PingusResource::load_font("Fonts/xterm","fonts");

  (*this) << "Pingus Output Console (hide/show it with F1)\n"
	  << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

  is_init = true;
}

void
Console::draw()
{
  assert(is_init);

  int i,j;
  int start_index;
  bool draw_current_line = !current_line.empty();
  int start_y_pos = 
    CL_Display::get_height() - (font->get_height() * (number_of_lines + 3));

  if (draw_current_line)
    start_index =  max(0, current_pos - number_of_lines);
  else
    start_index =  max(0, current_pos - number_of_lines-1);

  CL_Display::fill_rect(0, start_y_pos,
			CL_Display::get_width(),
			CL_Display::get_height(),
			0.0, 0.0, 0.0, 0.5);

  for(i = start_index, j=1; 
      i < (int)output_buffer.size(); 
      ++i, ++j)
    {
      font->print_left(10, 
		       start_y_pos + j * font->get_height(), 
		       output_buffer[i].c_str());
    }
  if (draw_current_line)
    font->print_left(10, start_y_pos + j * font->get_height(),
		     current_line.c_str());
}

void
Console::increase_lines()
{
  ++number_of_lines;
}

void
Console::decrease_lines()
{
  if (number_of_lines > 0)
    --number_of_lines;
}

void 
Console::scroll_up()
{
  if (current_pos - number_of_lines > 0)
    --current_pos;
}

void
Console::scroll_down()
{
  if (current_pos - number_of_lines < (int)output_buffer.size())
    ++current_pos;
}

void
Console::set_lines(int a)
{
  number_of_lines = a;
}

int
Console::get_lines()
{
  return number_of_lines;
}

void 
Console::add_line(string str)
{
  string::size_type pos;
  string tmp_string;

  // std::cout << "STR: " << str << std::endl;

  while ((pos = str.find("\n")) != string::npos) 
    {
      tmp_string = str.substr(0, pos);
      // std::cout << "TMP:" << tmp_string << std::endl;
      output_buffer.push_back(current_line + tmp_string);
      current_pos++;
      current_line = "";
      str = str.substr(pos+1);
    }

  current_line += str;

  // FIXME: This could be optimized if xterm would be a fixed font...
  while(font->get_text_width(current_line.c_str()) > (CL_Display::get_width() - 20))
    {
      int pos = current_line.size();

      while (font->get_text_width(current_line.substr(0, pos).c_str())
	     > (CL_Display::get_width() - 20))
	{
	  pos--;
	}

      tmp_string = current_line.substr(0, pos);

      output_buffer.push_back(tmp_string);
      current_pos++;
      current_line = current_line.substr(pos);
    }
}

// Simple wrapper around sprintf, warrning it will only be able to
// handle up to 1023 characters
void
Console::printf(char* format, ...) 
{
  char str_buffer[1024];
  va_list argp;

  va_start(argp, format);
#ifndef WIN32
  vsnprintf(str_buffer, 1024, format, argp);
#else
  vsprintf(str_buffer, format, argp);
#endif
  va_end(argp);

 add_line(str_buffer);
}

void
Console::puts(string str)
{
  add_line(str);
  newline();
}

void
Console::newline()
{
  add_line("\n");
}

Console& 
Console::operator<<(const Console::Endl& endl)
{
  newline();
  return *this;
}

Console& 
Console::operator<<(string str)
{
  add_line(str);
  return *this;
}

Console&
Console::operator<<(int a)
{
  this->printf("%d", a);
  return *this;
}

void
Console::on_event()
{
  draw();
}

/* EOF */
