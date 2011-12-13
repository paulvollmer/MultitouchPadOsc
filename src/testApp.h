/**
 * MagicTrackpadOsc is developed by Paul Vollmer (wrong-entertainment.com)
 * 
 * 
 * Copyright (c) 2011 Paul Vollmer
 *
 * MagicTrackpadOsc is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * MagicTrackpadOsc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with MagicTrackpadOsc; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * @author      Paul Vollmer
 * @modified    2011.12.09
 * @version     0.1.1
 */



#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"

#include "ofxMultiTouchPad.h"

#include "wCheckbox.h"
#include "wImageButton.h"

#define PROJECTNAME "MagicTrackpadOsc"
#define PROJECTVERSION "0.1.1"





class testApp : public ofBaseApp {

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
		// XML settings
		ofxXmlSettings   xmlSettings;           // xml of addon
		string           xmlSettingsFilepath;   // xml filepath
	
		// Application
		int appFramerate;
		int appWindowx;
		int appWindowy;
		int appCount;
	
		// OSC
		ofxOscSender   oscSender;   // osc of addon
		int            oscOut;      // osc active variable, if 0 = true, 1 = false
		string         oscHost;     // osc host variable
		int            oscPort;     // osc port variable
		
		// Multitouch Trackpad
		ofxMultiTouchPad   pad;
		string             padDevicename;
		int                padFrame;
		int                padTimestamp;
		int                padPosition;
		int                padVelocity;
		int                padSize;
		int                padMaxis;
		int                padAngle;
		
		// Images
		ofImage backgroundImage;
	
		// GUI
		wImageButton btnOscActive;   // button to trigger osc activity on/off
		wImageButton btnSettings;    // button to show/hide settings
		wImageButton btnConsole;     // button to show/hide console
		wCheckbox    cbFrame;        // checkbox to trigger pad frame on/off
	
};
