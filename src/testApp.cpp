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



#include "testApp.h"


/**
 * Setup
 * 
 * Load the settings xml file.
 * Load background image.
 */
void testApp::setup() {
	cout << "Setup start" << endl;
	
	// XML settings
	string filepath = "MagicTrackpadOscSettings.xml";
	// We load our settings file.
	// If it doesn't exist we can still make...
	if( xmlSettings.loadFile(filepath) ) {
		cout << filepath << " loaded!" << endl;
	} else {
		cout << "unable to load " << filepath << " check data/ folder" << endl;
	}
	
	// Read the settings file.
	// Application settings
	appFramerate = xmlSettings.getValue("app:framerate", 60);
	appCount     = xmlSettings.getValue("app:count", 1);
	/*cout << "app:framerate = " << appFramerate << endl;
	cout << "app:count     = " << appCount << endl;*/
	
	// OSC settings
	oscoutHost    = xmlSettings.getValue("osc:outhost", "127.0.0.1");
	oscoutPort    = xmlSettings.getValue("osc:outport", 1234);
	oscout        = xmlSettings.getValue("osc:out", 1);                  // if 0 it send messages
	oscDevicename = xmlSettings.getValue("osc:devicename", "mtosc");
	oscFrame      = xmlSettings.getValue("osc:frame", 1);
	oscTimestamp  = xmlSettings.getValue("osc:timestamp", 1);
	oscPosition   = xmlSettings.getValue("osc:position", 1);
	oscVelocity   = xmlSettings.getValue("osc:velocity", 1);
	oscSize       = xmlSettings.getValue("osc:size", 1);
	oscMaxis      = xmlSettings.getValue("osc:maxis", 1);
	oscAngle      = xmlSettings.getValue("osc:angle", 1);
	/*cout << "osc:outhost    = " << oscoutHost << endl;
	cout << "osc:outport    = " << oscoutPort << endl;
	cout << "osc:out        = " << oscout << endl;
	cout << "osc:devicename = " << oscDevicename << endl;
	cout << "osc:frame      = " << oscFrame << endl;
	cout << "osc:timestamp  = " << oscTimestamp << endl;
	cout << "osc:position   = " << oscPosition << endl;
	cout << "osc:velocity   = " << oscVelocity << endl;
	cout << "osc:size       = " << oscSize << endl;
	cout << "osc:maxis      = " << oscMaxis << endl;
	cout << "osc:angle      = " << oscAngle << endl;*/
	
	// add +1 to app:count and save the settings file.
	appCount++;
	xmlSettings.setValue("app:count", appCount);
	xmlSettings.saveFile(filepath);
	cout << "settings saved to xml!" << endl;
	
	
	// Images
	backgroundImage.loadImage("MagicTrackpad.png");
	
	// add the listeners
    ofAddListener(pad.update, this, &testApp::padUpdates);
    ofAddListener(pad.touchAdded, this, &testApp::newTouch);
    ofAddListener(pad.touchRemoved, this, &testApp::removedTouch);
	cout << "Number of Devices: " << pad.getNumDevices() << endl;
	
	cout << "Setup ready!" << endl;
}



/**
 * Update
 */
void testApp::update() {
	//cout << "Touchcount: " << pad.getTouchCount() << endl;
}



/**
 * Draw
 */
void testApp::draw() {
	// background image
	ofFill();
	ofSetColor(255);
	backgroundImage.draw(0, 0);
	
    ofSetColor(0);
    ofDrawBitmapString("TouchCount: "+ofToString(pad.getTouchCount(), 0),
                       20, 20);
    
    // connect all touches with a line
    std::vector<ofPoint>touches;
    pad.getTouchesAsOfPoints(&touches);
    for(int i=0; (i<touches.size()-1 && touches.size()>1); i++) {
        ofSetColor(255, 128, 22);
        ofLine(touches.at(i).x*ofGetWidth(),
               touches.at(i).y*ofGetHeight(),
               touches.at(i+1).x*ofGetWidth(),
               touches.at(i+1).y*ofGetHeight());
    }
    
    // ---- if we have only 2 touches, draw a line
    if(pad.getTouchCount()==2) {
        MTouch t1,t2;
        if(pad.getTouchAt(0,&t1) && pad.getTouchAt(1,&t2) ){
            ofSetColor(22, 255, 225);
            ofLine(t1.x*ofGetWidth(), t1.y*ofGetHeight(),
                   t2.x*ofGetWidth(), t2.y*ofGetHeight());
            
            ofSetColor(25, 128, 225, 128);
            ofCircle(t1.x*ofGetWidth(), t1.y*ofGetHeight(), t1.size*10);
            ofCircle(t2.x*ofGetWidth(), t2.y*ofGetHeight(), t2.size*10);
        }
    }
    else {
		for(int i=0; i<pad.getTouchCount(); i++) {
			// get a single touch as MTouch struct....
			MTouch _t;
			if(!pad.getTouchAt(i,&_t)) continue; // guard..
			
			// ... or as ofPoint
			ofPoint _p(0,0,0);
			if(!pad.getTouchAsOfPointAt(i,&_p)) continue; // guard..
			
			
			char _s [128];
			sprintf(_s, "ID %05i, frame: %05i, x: %6.3f, y: %6.3f, angle: %8.3f,"
                    "size: %6.3f nFingers: %d\n",
                    _t.ID,_t.frame,_t.x,_t.y,_t.angle,
                    _t.size,pad.getTouchCount());
			
			// using MTouch struct
			glPushMatrix();
			ofSetHexColor(0xff0000);
			ofTranslate(_t.x*ofGetWidth(),
						_t.y*ofGetHeight(),0);
			ofRotateZ(_t.angle);
			int s = _t.size*50;
			ofRect(-s/2,-(s*0.625)/2,s,s*0.625);
			
			// draw info
			//        ofSetColor(0xffffff);
			//        ofDrawBitmapString((string)_s, 0,0);
			glPopMatrix();
			
			// using ofPoint
			glPushMatrix();
			ofSetHexColor(0xffff00);
			ofTranslate(_p.x*ofGetWidth(),
						_p.y*ofGetHeight(),0);
			s = 10;
			ofCircle(0,0,s);
			glPopMatrix();
			
			
		}
    }
}


//--------------------------------------------------------------
void testApp::padUpdates(int & t) {
    printf("pad updates & has %i touches\n",t);
}

void testApp::newTouch(int & n) {
    printf("++++++ a new touch\n",n);
}

void testApp::removedTouch(int & r) {
    printf("------ a removed touch\n",r);
}


/**
 * Key pressed
 */
void testApp::keyPressed(int key) {

}


/**
 * Key released
 */
void testApp::keyReleased(int key) {

}


/**
 * Mouse moved
 */
void testApp::mouseMoved(int x, int y) {

}


/**
 * Mouse dragged
 */
void testApp::mouseDragged(int x, int y, int button) {

}


/**
 * Mouse pressed
 */
void testApp::mousePressed(int x, int y, int button) {

}


/**
 * Mouse released
 */
void testApp::mouseReleased(int x, int y, int button) {

}


/**
 * Window resized
 */
void testApp::windowResized(int w, int h) {

}


/**
 * Got message
 */
void testApp::gotMessage(ofMessage msg) {

}


/**
 * Drag event
 */
void testApp::dragEvent(ofDragInfo dragInfo) { 

}
