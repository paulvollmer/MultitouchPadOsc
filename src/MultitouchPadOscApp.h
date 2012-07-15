/**
 *  MultitouchPadOscApp.h
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
 *  @modified         2012.07.15
 *  @version          0.1.1a
 */

#pragma once

#include "ofMain.h"
#include "ofxXmlDefaultSettings.h"

#include "TextConsole.h"
#include "OscSender.h"
#include "ofxMultiTouchPad.h"
#include "wCheckbox.h"
#include "wImageButton.h"

#define PROJECTNAME "MultitouchPadOsc"
#define PROJECTVERSION "0.1.1"





class MultitouchPadOscApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();
		
		void padUpdates(int & t);
		void newTouch(int & n);
		void removedTouch(int & r);
		
		
	private:
		// XML Settings
		ofxXmlDefaultSettings defXml;
		////////////////////////int    defXmlAppCount;         // Application counter
		// OSC variables
		int    defXmlOscOut;           // Send out OSC message, 0 = true, 1 = false
		string defXmlOscHost;          // OSC host variable
		int    defXmlOscPort;          // OSC port variable
		// Trackpad variables
		string defXmlPadDevicename;    // Trackpad devicename
		int    defXmlPadFrame;         // Trackpad frame
		int    defXmlPadTimestamp;     // Trackpad timestamp
		int    defXmlPadPosition;      // Trackpad finger x-, y-position
		int    defXmlPadVelocity;      // Trackpad finger x-, y-velocity
		int    defXmlPadSize;          // Trackpad finger size
		int    defXmlPadMaxis;         // Trackpad finger minor-, major-axis
		int    defXmlPadAngle;         // Trackpad finger angle
	
		// Font
		ofTrueTypeFont vera;
		
		// OSC
		OscSender   oscSender;
	
		// Multitouch Trackpad
		ofxMultiTouchPad   pad;
	
	
	
	
		// Console
		TextConsole console;
	
		// Images
		ofImage backgroundImage;
		ofImage oscSendImage;
	
		// GUI
		wImageButton btnOscActive;   // button to trigger osc activity on/off
		wImageButton btnSettings;    // button to show/hide settings
		wImageButton btnConsole;     // button to show/hide console
		wCheckbox    cbFrame;        // checkbox to trigger pad frame on/off
		//wCheckbox    cbTimestamp;    // checkbox to trigger pad timestamp on/off
		wCheckbox    cbPosition;     // checkbox to trigger finger x-, y-position on/off
		//wCheckbox    cbVelocity;     // checkbox to trigger finger x-, y-velocity on/off
		//wCheckbox    cbMaxis;        // checkbox to trigger finger minor-, major-axis on/off
		wCheckbox    cbSize;         // checkbox to trigger finger size on/off
		wCheckbox    cbAngle;        // checkbox to trigger finger angle on/off
	
};
