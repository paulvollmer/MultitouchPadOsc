//
// ImageButton.cpp
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

#include "ImageButton.h"

ImageButton::ImageButton() {
	status = false;
}

void ImageButton::init(string _on, string _off, int _x, int _y) {
	on.loadImage(_on);
	off.loadImage(_off);
	x = _x;
	y = _y;

	// Initialize interaction
	interaction.init(x, y, on.width, on.height);
}

void ImageButton::display() {
	if (status == true) {
		on.draw(x, y);
	} else {
		off.draw(x, y);
	}
}

void ImageButton::pressed(int _mx, int _my) {
	if(interaction.overRect(_mx, _my)) {
		status = !status;
	}
}

void ImageButton::setPosition(int _x, int _y){
	x = _x;
	y = _y;
	interaction.init(x, y, on.width, on.height);
}
