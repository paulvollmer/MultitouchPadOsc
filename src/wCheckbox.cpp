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



#include "wCheckbox.h"





/*
 * Constructor
 */
wCheckbox::wCheckbox() {
	status = false;
	size = 10;
}



/**
 * Initialize
 */
void wCheckbox::init(string _message, int _x, int _y) {
	message = _message;
	x       = _x;
	y       = _y;
	
	// Initialize interaction
	interaction.init(x, y, size, size);
}



/**
 * Display the button
 */
void wCheckbox::display() {
	if (status == true) {
		ofSetColor(0 ,255, 0);
	} else {
		ofSetColor(255, 0, 0);
	}
	ofFill();
	ofRect(x, y, size, size);
	
	// message
	ofSetColor(0, 255, 255);
	ofFill();
	ofDrawBitmapString(message, x+size+10, y+size);
}



/**
 * Mouse pressed
 */
void wCheckbox::pressed(int _mx, int _my) {
	if(interaction.overRect(_mx, _my)) {
		status = !status;
	}
}