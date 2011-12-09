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
#include "ofxMultiTouchPad.h"


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
		
		void padUpdates(int & t);
		void newTouch(int & n);
		void removedTouch(int & r);
		
		
	private:
		// XML settings
		ofxXmlSettings  xmlSettings;
		int             appFramerate;
		int             appCount;
		string          oscoutHost;
		int             oscoutPort;
		int             oscout;
		string          oscDevicename;
		int             oscFrame;
		int             oscTimestamp;
		int             oscPosition;
		int             oscVelocity;
		int             oscSize;
		int             oscMaxis;
		int             oscAngle;
	
		
		ofxMultiTouchPad pad;
		
		// Images
		ofImage backgroundImage;
	
};
