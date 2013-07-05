//
// wInteraction.h
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

#ifndef _WINTERACTION_H
#define _WINTERACTION_H


class wInteraction {

	public:
		/**
		 * Constructor
		 */
		wInteraction(){}
		
		/**
		 * Initialize
		 * Calculate the width and height of interaction area.
		 */
		void init(int _x, int _y, int _width, int _height) {
			x      = _x;
			y      = _y;
			width  = _x+_width;
			height = _y+_height;
		}
	
		/**
		 * Check if the mouse is over a rectangle.
		 */
		bool overRect(int _mx, int _my, int _x, int _y, int _width, int _height) {
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
		bool overRect(int _mx, int _my) {
			if(_mx > x     && _my > y &&
			   _mx < width && _my < height) {
				return true;
			} else {
				return false;
			}
		}
	
	
	private:
		/**
		 * Variables
		 */
		int x;
		int y;
		int width;
		int height;
	
};
#endif // End _WINTERACTION_H
