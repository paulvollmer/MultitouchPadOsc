//
// MultitouchPadOscApp.ch
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
#include "wCheckbox.h"
#include "wImageButton.h"

#include "ToolbarMVC.h"
#include "TouchpointsMVC.h"
#include "SettingsMVC.h"
#include "ConsoleMVC.h"


class MultitouchPadOscApp : public ofBaseApp {
public:
	/**
	 * Setup
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
	 * - Draw the backgroundImage
	 * - Display the GUI
	 */
	void draw();
	
	/**
	 * Exit
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
	
	/**
	 * Multitouch Trackpad update
	 */
	void padUpdates(int & t);
	
	/**
	 * Multitouch Trackpad new touch
	 */
	void newTouch(int & n);
	
	/**
	 * Multitouch Trackpad remove touch
	 */
	void removedTouch(int & r);
	
	/**
	 * Gui event
	 */
	void guiEvent(ofxUIEventArgs &e);
	
	
private:
	/**
	 * Set the Application Window Title
	 */
	void setWindowTitle();
	
	/**
	 * Send an osc message (integer value)
	 */
	void oscIntMessage(string s, int val);
	
	/**
	 * Send an osc message (float value)
	 */
	void oscFloatMessage(string s, float val);
	
	/* Font
	 */
	ofTrueTypeFont vera;
	
	/* Multitouch Trackpad
	 */
	ofxMultiTouchPad pad;
	
	/* XML Settings
	 */
	ofxXmlDefaultSettings XML;
	
	/* openFrameworks osc addon
	 */
	ofxOscSender oscSender;
	bool oscIsSending;
	
	/* Viewer
	 */
	ToolbarMVC toolbarMVC;
	TouchpointsMVC touchpointsMVC;
	SettingsMVC settingsMVC;
	ConsoleMVC consoleMVC;
	
	/* GUI
	 */
	ofxUICanvas *gui;
	
};
