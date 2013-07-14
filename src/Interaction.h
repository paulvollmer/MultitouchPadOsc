//
// Interaction.h
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

#ifndef _INTERACTION_H
#define _INTERACTION_H


class Interaction {

	public:
		/**
		 * Constructor
		 */
        Interaction();
		
		/**
		 * Initialize
		 * Calculate the width and height of interaction area.
		 */
        void init(int _x, int _y, int _width, int _height);
	
		/**
		 * Check if the mouse is over a rectangle.
		 */
        bool overRect(int _mx, int _my, int _x, int _y, int _width, int _height);
	
		/**
		 * Check if the mouse is over a rectangle.
		 * Use this method if you have init wInteraction before.
		 */
        bool overRect(int _mx, int _my);
	
	
	private:
		/**
		 * Variables
		 */
		int x;
		int y;
		int width;
		int height;
	
};
#endif // End _INTERACTION_H
