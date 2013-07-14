//
// Checkbox.h
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

#ifndef _CHECKBOX_H
#define _CHECKBOX_H

#include "ofMain.h"
#include "Interaction.h"
#include "Variables.h"


class Checkbox {
	
	public:
		/*
		 * Constructor
		 */
        Checkbox();
		
		/**
		 * Initialize
		 *
		 * _message Checkbox message
		 * _x Checkbox X-position
		 * _y Checkbox Y-position
		 * _status Checkbox status
		 */
        void init(ofTrueTypeFont &_f, string _message, int _x, int _y, bool _status);
	
        void init(ofTrueTypeFont &_f, string _message, int _x, int _y);
	
		/**
		 * Display the button
		 */
        void display();
	
		/**
		 * Mouse pressed
		 */
        void pressed(int _mx, int _my);
	
		/**
		 * Variables
		 */
		bool status;
	
	
	private:
		ofTrueTypeFont font;
		
		Interaction interaction;

		/* Variables */
		int    x;
		int    y;
		int    size;
		string message;
	
};
#endif // End _CHECKBOX_H
