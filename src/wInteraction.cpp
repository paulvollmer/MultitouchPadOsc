/**
 * MagicTrackpadOsc is developed by Paul Vollmer (wrong-entertainment.com)
 * 
 * 
 * Copyright (c) 2011 Paul Vollmer
 *
 * MagicTrackpadOsc is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * MagicTrackpadOsc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with MagicTrackpadOsc; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * @author      Paul Vollmer
 * @modified    2011.12.09
 * @version     0.1.1
 */



#include "wInteraction.h"





/*
 * Constructor
 */
wInteraction::wInteraction() {
}



/**
 * Initialize
 * Calculate the width and height of interaction area.
 */
void wInteraction::init(int _x, int _y, int _width, int _height) {
	x      = _x;
	y      = _y;
	width  = _x+_width;
	height = _y+_height;
}



/**
 * Check if the mouse is over a rectangle.
 */
bool wInteraction::overRect(int _mx, int _my, int _x, int _y, int _width, int _height) {
	if(_mx > _x        && _my > _y &&
	   _mx < _x+_width && _my < _y+_height) {
		return true;
	} else {
		return false;
	}
}



/**
 * Check if the mouse is over a rectangle.
 * Use this method if you have init wInteraction before.
 */
bool wInteraction::overRect(int _mx, int _my) {
	if(_mx > x     && _my > y &&
	   _mx < width && _my < height) {
		return true;
	} else {
		return false;
	}
}
