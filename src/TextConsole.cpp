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
 * @modified    2011.12.14
 * @version     0.1.1
 */



#include "TextConsole.h"





/**
 * Constructor
 */
TextConsole::TextConsole() {
}



/**
 * Initialize
 */
void TextConsole::init() {
	// set the currentConsoleStrings to 0
	currentConsoleStrings = 0;
}



void TextConsole::display(int _x, int _y) {
	for(int i=0; i<NUM_STRINGS; i++) {
		ofDrawBitmapString(consoleStrings[i], _x, _y+(i*15));
	}
}



void TextConsole::addString(string msg) {
	consoleStrings[currentConsoleStrings] = msg;
	
	if(currentConsoleStrings < NUM_STRINGS) {
		currentConsoleStrings++;
	}
	if(currentConsoleStrings == NUM_STRINGS) {
		currentConsoleStrings = 0;
	}
}
