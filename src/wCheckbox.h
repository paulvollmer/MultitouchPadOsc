/**
 *  wCheckbox.h
 *  This file is part of MultitouchPadOsc
 *
 *  
 *  The MIT License
 *  Copyright (c) 2012 Paul Vollmer, http://www.wrong-entertainment.com
 *  All rights reserved.
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and  associated documentation files  (the "Software"),  to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  
 *  @plattform        MacOs 10.6+
 *                    Win XXX
 *                    Linux XXX
 *  @openFrameworks   0071
 *  @dependencies     
 *  @modified         2012.07.16
 *  @version          0.1.2
 */

#ifndef _WCHECKBOX
#define _WCHECKBOX

#include "ofMain.h"
#include "wInteraction.h"



class wCheckbox {
	
	public:
		/*
		 * Constructor
		 */
		wCheckbox() {
			size = 10;
		}
	
	
	
		/**
		 * Initialize
		 *
		 * _message Checkbox message
		 * _x Checkbox X-position
		 * _y Checkbox Y-position
		 * _status Checkbox status
		 */
		void init(ofTrueTypeFont &_f, string _message, int _x, int _y, int _status) {
			font    = _f;
			message = _message;
			x       = _x;
			y       = _y;
			status  = _status;
		
			// Initialize interaction
			interaction.init(x, y, size, size);
		}
	
		void init(ofTrueTypeFont &_f, string _message, int _x, int _y) {
			init(_f, _message, _x, _y, 1);
		}
	
	
		/**
		 * Display the button
		 */
		void display() {
			switch (status) {
				case 0:
					ofSetColor(0 ,255, 0);
					break;
				case 1:
					ofSetColor(255, 0, 0);
					break;
			}
		
			/*if (status == true) {
				ofSetColor(0 ,255, 0);
			} else {
				ofSetColor(255, 0, 0);
			}*/
			ofFill();
			ofRect(x, y, size, size);
		
			// message
			ofSetColor(0, 255, 255);
			ofFill();
			font.drawString(message, x+size+10, y+size);
		}
	
	
		/**
		 * Mouse pressed
		 */
		void pressed(int _mx, int _my) {
			if(interaction.overRect(_mx, _my)) {
				//status = !status;
				switch (status) {
					case 0:
						status = 1;
						break;
					case 1:
						status = 0;
						break;
				}
			}
		}
	
	
	
		/* Variables */
		int status;
	
	
	private:
		ofTrueTypeFont font;
		
		wInteraction interaction;

		/* Variables */
		int    x;
		int    y;
		int    size;
		string message;
	
};

#endif
