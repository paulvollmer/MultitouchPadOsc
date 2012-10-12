//
// main.cpp
// MultitouchPadOsc is released under the MIT License.
//
// Copyright (c) 2011 - 2012, Paul Vollmer http://www.wrong-entertainment.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef _TEXTCONSOLE_H
#define _TEXTCONSOLE_H

#include "ofMain.h"
#define NUM_STRINGS 20


class TextConsole {
	
	public:
		/**
		 * Constructor
		 */
		TextConsole() {}
	
		/**
		 * Initialize
		 */
		void init(ofTrueTypeFont &_f) {
			font = _f;
			// set the currentConsoleStrings to 0
			currentConsoleStrings = 0;
		}
	
		/**
		 * display counsole text
		 */
		void display(int _x, int _y) {
			for(int i=0; i<NUM_STRINGS; i++) {
				font.drawString(consoleStrings[i], _x, _y+(i*15));
			}
		}
	
		/**
		 * add a string to console text
		 */
		void addString(string msg) {
			consoleStrings[currentConsoleStrings] = msg;
		
			if(currentConsoleStrings < NUM_STRINGS) {
				currentConsoleStrings++;
			}
			if(currentConsoleStrings == NUM_STRINGS) {
				currentConsoleStrings = 0;
			}
		}
	
		/**
		 * Variables
		 */
		int    currentConsoleStrings;
		string consoleStrings[NUM_STRINGS];
	
	
	private:
		ofTrueTypeFont font;
	
};
#endif // End _TEXTCONSOLE_H
