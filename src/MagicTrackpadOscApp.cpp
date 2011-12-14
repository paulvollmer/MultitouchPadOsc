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



#include "MagicTrackpadOscApp.h"





/**
 * Setup
 * 
 * Load the settings xml file.
 * Load background image.
 */
void MagicTrackpadOscApp::setup() {
	cout << "Setup start" << endl;
	
	
	// Initialize settings file.
	settings.init("settings.xml");
	
	
	// Application
	// All application settings below.
	// Set the framerate, window title, add +1 to app:count
	ofSetFrameRate(settings.appFramerate);
	ofSetWindowTitle(string(PROJECTNAME)+string(" - ")+PROJECTVERSION);
	ofSetWindowPosition(settings.appWindowx, settings.appWindowy);
	
	
	// OSC
	// open an outgoing connection to oscHost:oscPort
	oscSender.setup(settings.oscHost, settings.oscPort);
	
	
	// Images
	backgroundImage.loadImage("MagicTrackpad.png");
	
	
	// GUI
	// set the status to osc:out settings value
	btnOscActive.init("oscactive_on.png", "oscactive_off.png", 54, 50);
	if(settings.oscOut == 0) btnOscActive.status = true;
	else btnOscActive.status = false;
	
	btnSettings.init("settings_on.png", "settings_off.png", 90, 50);
	btnConsole.init("console_on.png", "console_off.png", 171, 50);
	
	cbFrame.init("frame active                 (shortcut 2)", 60, 155, settings.padFrame);
	cbTimestamp.init("timestamp active             (shortcut 3)", 60, 170, settings.padTimestamp);
	cbPosition.init("x-, y-position active        (shortcut 4)", 60, 185, settings.padPosition);
	cbVelocity.init("x-, y-velocity active        (shortcut 5)", 60, 200, settings.padVelocity);
	cbMaxis.init("minor-, major-axis active    (shortcut 6)", 60, 215, settings.padMaxis);
	cbSize.init("size active                  (shortcut 7)", 60, 230, settings.padSize);
	cbAngle.init("angle active                 (shortcut 8)", 60, 245, settings.padAngle);
	
	
	
	// Multitouch Trackpad
	// Add the listeners
    ofAddListener(pad.update, this, &MagicTrackpadOscApp::padUpdates);
    ofAddListener(pad.touchAdded, this, &MagicTrackpadOscApp::newTouch);
    ofAddListener(pad.touchRemoved, this, &MagicTrackpadOscApp::removedTouch);
	cout << "  number of trackpad devices: " << pad.getNumDevices() << endl;
	
	
	cout << "Setup ready" << endl;
}



/**
 * Update
 */
void MagicTrackpadOscApp::update() {
	//cout << "Touchcount: " << pad.getTouchCount() << endl;
}



/**
 * Draw
 *
 * Draw the backgroundImage
 * Display the GUI
 */
void MagicTrackpadOscApp::draw() {
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
		ofSetColor(0, 255, 255);
		ofDrawBitmapString("OSC SETTINGS", 60, 150);
		ofDrawBitmapString("device name (change name at config file)", 60, 295);
		
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
	ofDrawBitmapString("Host: "+ofToString(settings.oscHost)+" Port: "+ofToString(settings.oscPort),
					   50, 110);
    ofDrawBitmapString("TouchCount: "+ofToString(pad.getTouchCount(), 0),
                       20, 20);
    
	
    // connect all touches with a line
    std::vector<ofPoint>touches;
    pad.getTouchesAsOfPoints(&touches);
    for(int i=0; (i<touches.size()-1 && touches.size()>1); i++) {
        ofSetColor(0 ,255, 255);
        int x1 = ofMap(touches.at(i).x,   0.0, 1.0, 40,  ofGetWidth()-40);
		int y1 = ofMap(touches.at(i).y,   0.0, 1.0, 125, ofGetHeight()-40);
		int x2 = ofMap(touches.at(i+1).x, 0.0, 1.0, 40,  ofGetWidth()-40);
		int y2 = ofMap(touches.at(i+1).y, 0.0, 1.0, 125, ofGetHeight()-40);
		ofLine(x1, y1, x2, y2);
    }
    
	for(int i=0; i<pad.getTouchCount(); i++) {
		// get a single touch as MTouch struct....
		MTouch touch;
		if(!pad.getTouchAt(i,&touch)) continue; // guard..
		
		// using MTouch struct
		int x = ofMap(touch.x, 0.0, 1.0, 40,  ofGetWidth()-40);
		int y = ofMap(touch.y, 0.0, 1.0, 125, ofGetHeight()-40);
		ofSetColor(0, 155, 255);
		ofFill();
		ofEllipse(x, y, 20, 20);
		
		ofSetColor(0);
		ofNoFill();
		ofLine(x-5, y, x+5, y);
		ofLine(x, y-5, x, y+5);
		
		// draw info
		/*char _s [128];
		sprintf(_s, "ID %05i, frame: %05i, x: %6.3f, y: %6.3f, angle: %8.3f,"
				"size: %6.3f nFingers: %d\n",
				touch.ID,touch.frame,touch.x,touch.y,touch.angle,
				touch.size,pad.getTouchCount());
		ofSetHexColor(0xffffff);
		ofDrawBitmapString((string)_s, 0,0);*/
    }
	
}



/**
 * Trackpad update
 */
void MagicTrackpadOscApp::padUpdates(int & t) {
	if (settings.oscOut == true) {
		
		printf("pad updates & has %i touches\n",t);
		
		/*ofxOscMessage m;
		m.setAddress("/" + settings.padDevicename + "/" + ofToString(t));
		//m.addIntArg( 1 );
		m.addFloatArg(1);
		//m.addStringArg( "hello" );
		//m.addFloatArg( ofGetElapsedTimef() );
		oscSender.sendMessage( m );*/
	}
}



/**
 * Trackpad new touch
 */
void MagicTrackpadOscApp::newTouch(int & n) {
    printf("+ a new touch\n",n);
	
}



/**
 * Trackpad remove touch
 */
void MagicTrackpadOscApp::removedTouch(int & r) {
    printf("- a removed touch\n",r);
}



/**
 * Key pressed
 */
void MagicTrackpadOscApp::keyPressed(int key) {
	switch(key) {
		// OSC out
		case '1':
			if (settings.oscOut == 0) {
				settings.oscOut = 1;
				btnOscActive.status = !btnOscActive.status;
			} else {
				settings.oscOut = 0;
				btnOscActive.status = !btnOscActive.status;
			}
			cout << "Shortcut oscOut: " << settings.oscOut << endl;
			break;
		
		// OSC frame
		case '2':
			if (settings.padFrame == 0) {
				settings.padFrame = 1;
			} else {
				settings.padFrame = 0;
			}
			cbFrame.status = settings.padFrame;
			
			cout << "Shortcut padFrame: " << settings.padFrame << endl;
			break;
		
		// OSC timestamp
		case '3':
			if (settings.padTimestamp == 0) {
				settings.padTimestamp = 1;
			} else {
				settings.padTimestamp = 0;
			}
			cbTimestamp.status = settings.padTimestamp;
			
			cout << "Shortcut padTimestamp: " << settings.padTimestamp << endl;
			break;
		
		// OSC position
		case '4':
			if (settings.padPosition == 0) {
				settings.padPosition = 1;
			} else {
				settings.padPosition = 0;
			}
			cbPosition.status = settings.padPosition;
			
			cout << "Shortcut padPosition: " << settings.padPosition << endl;
			break;

		// OSC velocity
		case '5':
			if (settings.padVelocity == 0) {
				settings.padVelocity = 1;
			} else {
				settings.padVelocity = 0;
			}
			cbVelocity.status = settings.padVelocity;
			
			cout << "Shortcut padVelocity: " << settings.padVelocity << endl;
			break;

		// OSC size
		case '6':
			if (settings.padMaxis == 0) {
				settings.padMaxis = 1;
			} else {
				settings.padMaxis = 0;
			}
			cbMaxis.status = settings.padMaxis;
			
			cout << "Shortcut padMaxis: " << settings.padMaxis << endl;
			break;

		// OSC maxis
		case '7':
			if (settings.padSize == 0) {
				settings.padSize = 1;
			} else {
				settings.padSize = 0;
			}
			cbSize.status = settings.padSize;
			
			cout << "Shortcut padSize: " << settings.padSize << endl;
			break;

		// OSC angle
		case '8':
			if (settings.padAngle == 0) {
				settings.padAngle = 1;
			} else {
				settings.padAngle = 0;
			}
			cbAngle.status = settings.padAngle;
			
			cout << "Shortcut padAngle: " << settings.padAngle << endl;
			break;

		default:
			break;
	}
}



/**
 * Key released
 */
void MagicTrackpadOscApp::keyReleased(int key) {
	
}



/**
 * Mouse moved
 */
void MagicTrackpadOscApp::mouseMoved(int x, int y) {
	
}



/**
 * Mouse dragged
 */
void MagicTrackpadOscApp::mouseDragged(int x, int y, int button) {

}



/**
 * Mouse pressed
 */
void MagicTrackpadOscApp::mousePressed(int x, int y, int button) {
	// GUI
	btnOscActive.pressed(x, y);
	if(btnOscActive.status == true) settings.oscOut = 0;
	else settings.oscOut = 1;
	
	btnSettings.pressed(x, y);
	if(btnSettings.status == true) btnConsole.status = false;
	
	btnConsole.pressed(x, y);
	if(btnConsole.status == true) btnSettings.status = false;
	
	if(btnSettings.status == true) {
		cbFrame.pressed(x, y);
		settings.padFrame = cbFrame.status;

		cbTimestamp.pressed(x, y);
		settings.padTimestamp = cbTimestamp.status;

		cbPosition.pressed(x, y);
		settings.padPosition = cbPosition.status;
		
		cbVelocity.pressed(x, y);
		settings.padVelocity = cbVelocity.status;
		
		cbMaxis.pressed(x, y);
		settings.padMaxis = cbMaxis.status;
		
		cbSize.pressed(x, y);
		settings.padSize = cbSize.status;
		
		cbAngle.pressed(x, y);
		settings.padAngle = cbAngle.status;
	}
	
}



/**
 * Mouse released
 */
void MagicTrackpadOscApp::mouseReleased(int x, int y, int button) {
	
}


/**
 * Window resized
 */
void MagicTrackpadOscApp::windowResized(int w, int h) {
	
}


/**
 * Got message
 */
void MagicTrackpadOscApp::gotMessage(ofMessage msg) {
	
}


/**
 * Drag event
 */
void MagicTrackpadOscApp::dragEvent(ofDragInfo dragInfo) {
	

}


/**
 * Exit
 *
 * Update XML settings variables.
 * Save the current app count, window position and framerate.
 * Save OSC variables like Host, Port etc.
 */
void MagicTrackpadOscApp::exit() {
	cout << "Exit start" << endl;
	
	// Update settings file.
	settings.save();
	
	cout << "Exit ready" << endl;
}
