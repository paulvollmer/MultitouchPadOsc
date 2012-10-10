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
 *  @modified         2012.08.01
 *  @version          0.1.2b  
 */

#pragma once

#define PROJECTNAME "MultitouchPadOsc"
#define PROJECTVERSION "0.1.2"

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxMultiTouchPad.h"
#include "ofxXmlDefaultSettings.h"
#include "ofxUI.h"

#include "TextConsole.h"
#include "wCheckbox.h"
#include "wImageButton.h"

// Used to print debugging infos to console
#define MULTITOUCHPADOSC_DEBUG





class MultitouchPadOscApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		// Multitouch events
		void padUpdates(int & t);
		void newTouch(int & n);
		void removedTouch(int & r);
		// osc events
		void intMessage(string s, int val);
		void floatMessage(string s, float val);
		// Gui events
		void guiEvent(ofxUIEventArgs &e);
		
		
	private:
		// XML Settings
		ofxXmlDefaultSettings XML;
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
		// Touchpoint color variables
		ofColor defXmlTouchpointColor;
		ofColor defXmlTouchpointLines;
		ofColor defXmlTouchpointCross;
	
	
		// Font
		ofTrueTypeFont vera;
		
		// OSC
		//OscSender   oscSender;
		// openFrameworks osc addon
		ofxOscSender   oscSender;
	
		// Multitouch Trackpad
		ofxMultiTouchPad   pad;
	
		// Console
		TextConsole console;
	
		// GUI
		ofxUICanvas *gui;
		wImageButton btnOscActive;   // button to trigger osc activity on/off
		ofImage      oscSendImage;
		wImageButton btnTouchpoints; // button to show/hide touchpoints
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
