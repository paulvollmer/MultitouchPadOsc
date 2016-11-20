//
// Checkbox.cpp
// MultitouchPadOsc is released under the MIT License.
//
// Copyright (c) 2011-2016, Paul Vollmer
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

#include "Checkbox.h"


Checkbox::Checkbox() {
	size = 10;
}

void Checkbox::init(ofTrueTypeFont &_f, string _message, int _x, int _y, bool _status) {
    font    = _f;
	message = _message;
	x       = _x;
	y       = _y;
	status  = _status;
	
	// Initialize interaction
	interaction.init(x, y, size, size);
}

void Checkbox::init(ofTrueTypeFont &_f, string _message, int _x, int _y) {
	init(_f, _message, _x, _y, true);
}
	
void Checkbox::display() {
	if(status) {
        ofSetColor(CHECKBOX_COLOR_ON_R, CHECKBOX_COLOR_ON_G, CHECKBOX_COLOR_ON_B);
    } else {
        ofSetColor(COLOR_DARK_GREY);
	}

	ofFill();
	ofRect(x, y, size, size);

	// message
	ofSetColor(COLOR_LIGHT_GREY);
	ofFill();
	font.drawString(message, x+size+10, y+size);
}
	
void Checkbox::pressed(int _mx, int _my) {
	if(interaction.overRect(_mx, _my)) {
		status = !status;
	}
}
