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
	
	
	// Initialize settings file, load and set variables.
	settings.init("settings.xml");
	
	// XML settings
	// Set the filepath of xmlSettings XML.
	xmlSettingsFilepath = "settings.xml";
	// We load our settings file.
	// If it doesn't exist we can still make...
	if( xmlSettings.loadFile(xmlSettingsFilepath) ) {
		cout << "  " << xmlSettingsFilepath << " loaded!" << endl;
	} else {
		cout << "  unable to load " << xmlSettingsFilepath << " check data/ folder" << endl;
	}
	
	// Read the settings file.
	// Application settings
	appFramerate = xmlSettings.getValue("app:framerate", 60);
	appWindowx   = xmlSettings.getValue("app:windowx", 50);
	appWindowy   = xmlSettings.getValue("app:windowy", 50);
	appCount     = xmlSettings.getValue("app:count", 1);
	cout << "  app:framerate  = " << appFramerate << endl;
	cout << "  app:windowx    = " << appWindowx << endl;
	cout << "  app:windowy    = " << appWindowy << endl;
	cout << "  app:count      = " << appCount << endl;
	
	// osc settings
	// If 0 = true, 1 = false
	oscHost = xmlSettings.getValue("osc:outhost", "127.0.0.1");
	oscPort = xmlSettings.getValue("osc:outport", 1234);
	oscOut  = xmlSettings.getValue("osc:out", 1);
	cout << "  osc:outhost    = " << oscHost << endl;
	cout << "  osc:outport    = " << oscPort << endl;
	cout << "  osc:out        = " << oscOut << endl;
	
	padDevicename = xmlSettings.getValue("osc:devicename", "mtosc");
	padFrame      = xmlSettings.getValue("osc:frame", 1);
	padTimestamp  = xmlSettings.getValue("osc:timestamp", 1);
	padPosition   = xmlSettings.getValue("osc:position", 1);
	padVelocity   = xmlSettings.getValue("osc:velocity", 1);
	padSize       = xmlSettings.getValue("osc:size", 1);
	padMaxis      = xmlSettings.getValue("osc:maxis", 1);
	padAngle      = xmlSettings.getValue("osc:angle", 1);
	cout << "  osc:devicename = " << padDevicename << endl;
	cout << "  osc:frame      = " << padFrame << endl;
	cout << "  osc:timestamp  = " << padTimestamp << endl;
	cout << "  osc:position   = " << padPosition << endl;
	cout << "  osc:velocity   = " << padVelocity << endl;
	cout << "  osc:size       = " << padSize << endl;
	cout << "  osc:maxis      = " << padMaxis << endl;
	cout << "  osc:angle      = " << padAngle << endl;
	
	
	// Application
	// All application settings below.
	// Set the framerate, window title, add +1 to app:count
	ofSetFrameRate(appFramerate);
	ofSetWindowTitle(string(PROJECTNAME)+string(" - ")+PROJECTVERSION);
	ofSetWindowPosition(appWindowx, appWindowy);
	appCount++;
	
	
	// OSC
	// open an outgoing connection to oscHost:oscPort
	oscSender.setup(oscHost, oscPort);
	
	
	// Images
	backgroundImage.loadImage("MagicTrackpad.png");
	
	
	// GUI
	// set the status to osc:out settings value
	btnOscActive.init("oscactive_on.png", "oscactive_off.png", 54, 50);
	if(oscOut == 0) btnOscActive.status = true;
	else btnOscActive.status = false;
	
	btnSettings.init("settings_on.png", "settings_off.png", 90, 50);
	btnConsole.init("console_on.png", "console_off.png", 171, 50);
	
	cbFrame.init("frame active", 60, 155);
	cbTimestamp.init("timestamp active", 60, 170);
	cbPosition.init("x-, y-position active", 60, 185);
	
	cbVelocity.init("x, y-velocity active", 60, 200);
	cbMaxis.init("maxis active", 60, 215);
	cbSize.init("size active", 60, 230);
	cbAngle.init("angle active", 60, 245);
	
	
	
	// Multitouch Trackpad
	// Add the listeners
    ofAddListener(pad.update, this, &testApp::padUpdates);
    ofAddListener(pad.touchAdded, this, &testApp::newTouch);
    ofAddListener(pad.touchRemoved, this, &testApp::removedTouch);
	cout << "  number of trackpad devices: " << pad.getNumDevices() << endl;
	
	
	cout << "Setup ready" << endl;
}



/**
 * Update
 */
void testApp::update() {
	//cout << "Touchcount: " << pad.getTouchCount() << endl;
}



/**
 * Draw
 *
 * Draw the backgroundImage
 * Display the GUI
 */
void testApp::draw() {
	// background image
	ofFill();
	ofSetColor(255);
	backgroundImage.draw(0, 0);
	
	
	// GUI
	btnOscActive.display();
	btnSettings.display();
	btnConsole.display();
	
	
	// settings button
	if(btnSettings.status == true) {
		// ground
		ofEnableAlphaBlending();
		ofSetColor(0, 150);
		ofFill();
		ofRect(55, 125, ofGetWidth()-110, 420);
		ofDisableAlphaBlending();
		// text
		ofSetColor(0, 255, 0);
		string test = string("test")+" hello";
		cout << test << endl;
		string s = string("OSC SETTINGS \n")+
		           "master name              (change name at config file)\n";
		           /*string("osc active               (shortcut 1)\n")+
		           string("frame active             (shortcut 2)\n")+
		           string("timestamp active         (shortcut 3)\n")+
		           string("x, y position active     (shortcut 4)\n")+
		           string("x, y velocity active     (shortcut 5)\n")+
		           string("minor/major axis active  (shortcut 6)\n")+
		           string("size active              (shortcut 7)\n")+
				          "angle active             (shortcut 8)";*/
		ofDrawBitmapString(s, 60, 150);
		
		cbFrame.display();
		cbTimestamp.display();
		cbPosition.display();
		cbVelocity.display();
		cbMaxis.display();
		cbSize.display();
		cbAngle.display();
	}
	
	// console button
	if(btnConsole.status == true) {
		// ground
		ofEnableAlphaBlending();
		ofSetColor(0, 150);
		ofFill();
		ofRect(55, 125, ofGetWidth()-110, 420);
		ofDisableAlphaBlending();
	}
	
	
	// Local-IP, Host: xxx.xxx.xxx.xxx Port: xxxx
    ofSetColor(0);
	ofDrawBitmapString("Local-IP: ",
					   50, 95);
	ofDrawBitmapString("Host: "+ofToString(oscHost)+" Port: "+ofToString(oscPort),
					   50, 110);
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
			//ofSetHexColor(0xffffff);
			//ofDrawBitmapString((string)_s, 0,0);
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



/**
 * Trackpad update
 */
void testApp::padUpdates(int & t) {
    printf("pad updates & has %i touches\n",t);
}



/**
 * Trackpad new touch
 */
void testApp::newTouch(int & n) {
    printf("+ a new touch\n",n);
	
}



/**
 * Trackpad remove touch
 */
void testApp::removedTouch(int & r) {
    printf("- a removed touch\n",r);
}



/**
 * Key pressed
 */
void testApp::keyPressed(int key) {
	switch(key) {
		// OSC out
		case '1':
			if (oscOut == 0) {
				oscOut = 1;
				btnOscActive.status = !btnOscActive.status;
			} else {
				oscOut = 0;
				btnOscActive.status = !btnOscActive.status;
			}
			cout << "Shortcut oscOut: " << oscOut << endl;
			break;
		
		// OSC frame
		case '2':
			if (padFrame == 0) {
				padFrame = 1;
			} else {
				padFrame = 0;
			}
			cout << "Shortcut padFrame: " << padFrame << endl;
			break;
		
		// OSC timestamp
		case '3':
			if (padTimestamp == 0) {
				padTimestamp = 1;
			} else {
				padTimestamp = 0;
			}
			cout << "Shortcut padTimestamp: " << padTimestamp << endl;
			break;
		
		// OSC position
		case '4':
			if (padPosition == 0) {
				padPosition = 1;
			} else {
				padPosition = 0;
			}
			cout << "Shortcut padPosition: " << padPosition << endl;
			break;

		// OSC velocity
		case '5':
			if (padVelocity == 0) {
				padVelocity = 1;
			} else {
				padVelocity = 0;
			}
			cout << "Shortcut padVelocity: " << padVelocity << endl;
			break;

		// OSC size
		case '6':
			if (padSize == 0) {
				padSize = 1;
			} else {
				padSize = 0;
			}
			cout << "Shortcut padSize: " << padSize << endl;
			break;

		// OSC maxis
		case '7':
			if (padMaxis == 0) {
				padMaxis = 1;
			} else {
				padMaxis = 0;
			}
			cout << "Shortcut padMaxis: " << padMaxis << endl;
			break;

		// OSC angle
		case '8':
			if (padAngle == 0) {
				padAngle = 1;
			} else {
				padAngle = 0;
			}
			cout << "Shortcut padAngle: " << padAngle << endl;
			break;

		default:
			break;
	}
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
	// GUI
	btnOscActive.pressed(x, y);
	if(btnOscActive.status == true) oscOut = 0;
	else oscOut = 1;
	
	btnSettings.pressed(x, y);
	if(btnSettings.status == true) btnConsole.status = false;
	
	btnConsole.pressed(x, y);
	if(btnConsole.status == true) btnSettings.status = false;
	
	if(btnSettings.status == true) {
		cbFrame.pressed(x, y);
	}
}



/**
 * Mouse released
 */
void testApp::mouseReleased(int x, int y, int button) {
	if (oscOut == true) {
		ofxOscMessage m;
		m.setAddress( "/test" );
		m.addIntArg( 1 );
		m.addFloatArg( 3.5f );
		m.addStringArg( "hello" );
		m.addFloatArg( ofGetElapsedTimef() );
		oscSender.sendMessage( m );
	}
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


/**
 * Exit
 *
 * Update XML settings variables.
 * Save the current app count, window position and framerate.
 * Save OSC variables like Host, Port etc.
 */
void testApp::exit() {
	cout << "Exit start" << endl;
	
	
	// Application variable update
	// Save the current app count to XML file.
	xmlSettings.setValue("app:count", appCount);
	cout << "  appCount      = " << appCount << endl;
	
	// Get the current window x, y position and save to XML file.
	appWindowx = ofGetWindowPositionX();
	appWindowy = ofGetWindowPositionY();
	xmlSettings.setValue("app:windowx", appWindowx);
	xmlSettings.setValue("app:windowy", appWindowy);
	cout << "  appWindowx    = " << appWindowx << endl;
	cout << "  appWindowy    = " << appWindowy << endl;
	
	
	// OSC variable update
	// Save the current OSC variables to XML file.
	xmlSettings.setValue("osc:outhost", oscHost);
	xmlSettings.setValue("osc:outport", oscPort);
	xmlSettings.setValue("osc:out", oscOut);
	
	xmlSettings.setValue("osc:devicename", padDevicename);
	xmlSettings.setValue("osc:frame", padFrame);
	xmlSettings.setValue("osc:timestamp", padTimestamp);
	xmlSettings.setValue("osc:position", padPosition);
	xmlSettings.setValue("osc:velocity", padVelocity);
	xmlSettings.setValue("osc:size", padSize);
	xmlSettings.setValue("osc:maxis", padMaxis);
	xmlSettings.setValue("osc:angle", padAngle);
	cout << "  oscHost       = " << oscHost << endl;
	cout << "  oscPort       = " << oscPort << endl;
	cout << "  oscOut        = " << oscOut << endl;
	cout << "  oscDevicename = " << padDevicename << endl;
	cout << "  padFrame      = " << padFrame << endl;
	cout << "  padTimestamp  = " << padTimestamp << endl;
	cout << "  padPosition   = " << padPosition << endl;
	cout << "  padVelocity   = " << padVelocity << endl;
	cout << "  padSize       = " << padSize << endl;
	cout << "  padMaxis      = " << padMaxis << endl;
	cout << "  padAngle      = " << padAngle << endl;
	
	
	// save the settings file.
	xmlSettings.saveFile(xmlSettingsFilepath);
	cout << "  settings saved to " << xmlSettingsFilepath << " xml!" << endl;
	
	
	cout << "Exit ready" << endl;
}
