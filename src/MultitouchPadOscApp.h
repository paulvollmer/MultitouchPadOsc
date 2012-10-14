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


class MultitouchPadOscApp : public ofBaseApp {
public:
	/**
	 * Setup
	 * 
	 * - Load the default settings xml.
	 * - Load Font
	 * - Initialize osc sender
	 * - Initialize ofxMultiTouchPad
	 * - Load background image.
	 * - Initialize GUI
	 */
	void setup();
	/**
	 * Update
	 */
	void update();
	/**
	 * Draw
	 *
	 * - Draw the backgroundImage
	 * - Display the GUI
	 */
	void draw();
	/**
	 * Exit
	 *
	 * - Update XML settings variables.
	 * - Save the current app count, window position and framerate.
	 * - Save OSC variables like Host, Port etc.
	 */
	void exit();
	/**
	 * Key pressed
	 */
	void keyPressed(int key);
	/**
	 * Key released
	 */
	void keyReleased(int key);
	/**
	 * Mouse moved
	 */
	void mouseMoved(int x, int y);
	/**
	 * Mouse dragged
	 */
	void mouseDragged(int x, int y, int button);
	/**
	 * Mouse pressed
	 */
	void mousePressed(int x, int y, int button);
	/**
	 * Mouse released
	 */
	void mouseReleased(int x, int y, int button);
	/**
	 * Window resized
	 */
	void windowResized(int w, int h);
	/**
	 * Got message
	 */
	void gotMessage(ofMessage msg);
	/**
	 * Drag event
	 */
	void dragEvent(ofDragInfo dragInfo);
	
	// Multitouch events
	/**
	 * Trackpad update
	 */
	void padUpdates(int & t);
	/**
	 * Trackpad new touch
	 */
	void newTouch(int & n);
	/**
	 * Trackpad remove touch
	 */
	void removedTouch(int & r);
	
	// osc events
	/**
	 * Send an osc message (integer value)
	 */
	void intMessage(string s, int val);
	/**
	 * Send an osc message (float value)
	 */
	void floatMessage(string s, float val);
	
	/**
	 * Gui event
	 */
	void guiEvent(ofxUIEventArgs &e);
	
	
	
private:
	/**
	 * Set the Application Window Title
	 */
	void setWindowTitle();
	
		// XML Settings
		ofxXmlDefaultSettings XML;
		// OSC variables
		int    xmlOscOut;           // Send out OSC message, 0 = true, 1 = false
		string xmlOscHost;          // OSC host variable
		int    xmlOscPort;          // OSC port variable
		// Trackpad variables
		string xmlPadDevicename;    // Trackpad devicename
		int    xmlPadFrame;         // Trackpad frame
		int    xmlPadTimestamp;     // Trackpad timestamp
		int    xmlPadPosition;      // Trackpad finger x-, y-position
		int    xmlPadVelocity;      // Trackpad finger x-, y-velocity
		int    xmlPadSize;          // Trackpad finger size
		int    xmlPadMaxis;         // Trackpad finger minor-, major-axis
		int    xmlPadAngle;         // Trackpad finger angle
		// Touchpoint color variables
		ofColor xmlTouchpointColor;
		ofColor xmlTouchpointLines;
		ofColor xmlTouchpointCross;
	
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
		//wImageButton btnSafetyMode;  // This mode can be used to run in safety mode.
	                                 // No dock or other system stuff can be selected.
		wImageButton btnWindowMode;
		bool xmlWindowMode;          // The current window mode. Normal or mini
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
