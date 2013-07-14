//
// ConsoleMVC.cpp
// MultitouchPadOsc is released under the MIT License.
//
// Copyright (c) 2011-2013, Paul Vollmer http://www.wrong-entertainment.com
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

#include "ConsoleMVC.h"

ConsoleMVC::ConsoleMVC(){}


void ConsoleMVC::init() {
	/* Set the currentConsoleStrings to 0
	 */
	currentConsoleStrings = 0;
}


void ConsoleMVC::draw(ofTrueTypeFont font) {
	/* Ground
	 */
	ofEnableAlphaBlending();
	ofSetColor(0, 150);
	ofFill();
	ofRect(10, 30, ofGetWidth()-20, ofGetHeight()-40);
	ofDisableAlphaBlending();
	
	/* console text
	 */
	for(int i=0; i<NUM_STRINGS; i++) {
		if (i == (currentConsoleStrings-1)) {
			ofSetColor(ofColor::white);
		} else {
			ofSetColor(COLOR_LIGHT_GREY);
		}
		font.drawString(consoleStrings[i], FONT_POSITION_X, 50+(i*15));
	}
}


void ConsoleMVC::addString(string msg, bool log) {
	consoleStrings[currentConsoleStrings] = msg;
	
	if (log == true) {
		ofLog() << msg;
	}
	
	if (currentConsoleStrings < NUM_STRINGS) {
		currentConsoleStrings++;
	}
	if (currentConsoleStrings == NUM_STRINGS) {
		currentConsoleStrings = 0;
	}
}
