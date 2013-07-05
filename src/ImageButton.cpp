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



#include "wImageButton.h"





/**
 * Constructor
 */
wImageButton::wImageButton() {
	status = false;
}



/**
 * Initialize
 */
void wImageButton::init(string _on, string _off, int _x, int _y) {
	on.loadImage(_on);
	off.loadImage(_off);
	x = _x;
	y = _y;
	
	// Initialize interaction
	interaction.init(x, y, on.width, on.height);
}



/**
 * Display the button
 */
void wImageButton::display() {
	if (status == true) {
		on.draw(x, y);
	} else {
		off.draw(x, y);
	}
}



/**
 * Mouse pressed
 */
void wImageButton::pressed(int _mx, int _my) {
	if(interaction.overRect(_mx, _my)) {
		status = !status;
	}
}


void wImageButton::setPosition(int _x, int _y){
	x = _x;
	y = _y;
	interaction.init(x, y, on.width, on.height);
}
