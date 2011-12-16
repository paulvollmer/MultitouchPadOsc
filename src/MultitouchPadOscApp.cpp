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



#include "MultitouchPadOscApp.h"





/**
 * Setup
 * 
 * Load the settings xml file.
 * Load background image.
 */
void MultitouchPadOscApp::setup() {
	
	// Font
	vera.loadFont("Vera.ttf", 10, true, false);
	
	// Console
	console.init(vera);
	
	
	// Initialize settings file.
	settings.init("settings.xml");
	console.addString(ofToString(settings.filepath) + " loaded");
	
	// Application
	// All application settings below.
	// Set the framerate, window title, add +1 to app:count
	ofSetFrameRate(settings.appFramerate);
	ofSetWindowTitle(string(PROJECTNAME)+string(" - ")+PROJECTVERSION);
	ofSetWindowPosition(settings.appWindowx, settings.appWindowy);
	
	
	// OSC
	oscSender.init(settings.oscHost, settings.oscPort);
	console.addString(ofToString("Host: ") +
					  ofToString(settings.oscHost) +
					  ofToString(" Port: ") +
					  ofToString(settings.oscPort) + " connected");
	
	
	// Images
	backgroundImage.loadImage("MagicTrackpad.png");
	
	
	// GUI
	// set the status to osc:out settings value
	btnOscActive.init("oscactive_on.png", "oscactive_off.png", 40, 10);
	if(settings.oscOut == 0) btnOscActive.status = true;
	else btnOscActive.status = false;
	
	btnSettings.init("settings_on.png",  "settings_off.png",  90,  10);
	btnConsole.init("console_on.png",    "console_off.png",   171, 10);
	
	cbFrame.init(vera,      "frame active",               60, 130, settings.padFrame);
	cbTimestamp.init(vera,  "timestamp active",           60, 145, settings.padTimestamp);
	cbPosition.init(vera,   "x-, y-position active",      60, 160, settings.padPosition);
	cbVelocity.init(vera,   "x-, y-velocity active",      60, 175, settings.padVelocity);
	cbMaxis.init(vera,      "minor-, major-axis active",  60, 190, settings.padMaxis);
	cbSize.init(vera,       "size active",                60, 205, settings.padSize);
	cbAngle.init(vera,      "angle active",               60, 220, settings.padAngle);
	console.addString("GUI Initialized");
	
	
	// Multitouch Trackpad
	// Add the listeners
    ofAddListener(pad.update, this, &MultitouchPadOscApp::padUpdates);
    ofAddListener(pad.touchAdded, this, &MultitouchPadOscApp::newTouch);
    ofAddListener(pad.touchRemoved, this, &MultitouchPadOscApp::removedTouch);
	//cout << "  number of trackpad devices: " << pad.getNumDevices() << endl;
	console.addString(ofToString("Number of Devices: ") + ofToString(pad.getNumDevices()));
}



/**
 * Update
 */
void MultitouchPadOscApp::update() {
}



/**
 * Draw
 *
 * Draw the backgroundImage
 * Display the GUI
 */
void MultitouchPadOscApp::draw() {
	// background image
	ofFill();
	ofSetColor(255);
	backgroundImage.draw(0, 0);
	
	
	// GUI
	btnOscActive.display();
	btnSettings.display();
	btnConsole.display();
	
	
	// Host: xxx.xxx.xxx.xxx Port: xxxx, Touch Count
    ofFill();
	ofSetColor(0);
	vera.drawString("Host: "+ofToString(settings.oscHost)+" Port: "+ofToString(settings.oscPort),
	                330, 25);
	
    ofSetColor(255);
	vera.drawString("Touch Count: "+ofToString(pad.getTouchCount(), 0),
                    40, 580);
	
	
	// Display finger blobs
	// connect all touches with a line
    std::vector<ofPoint>touches;
    pad.getTouchesAsOfPoints(&touches);
	
    for(int i=0; (i<touches.size()-1 && touches.size()>1); i++) {
        ofSetColor(0 ,255, 255);
        int x1 = ofMap(touches.at(i).x,   0.0, 1.0, 40, ofGetWidth()-40);
		int y1 = ofMap(touches.at(i).y,   0.0, 1.0, 80, ofGetHeight()-40);
		int x2 = ofMap(touches.at(i+1).x, 0.0, 1.0, 40, ofGetWidth()-40);
		int y2 = ofMap(touches.at(i+1).y, 0.0, 1.0, 80, ofGetHeight()-40);
		ofLine(x1, y1, x2, y2);
    }
    
	
	// display all finger blobs
	for(int i=0; i<pad.getTouchCount(); i++) {
		// get a single touch as MTouch struct....
		MTouch touch;
		if(!pad.getTouchAt(i,&touch)) continue; // guard..
		
		// using MTouch struct
		int x = ofMap(touch.x, 0.0, 1.0, 40, ofGetWidth()-40);
		int y = ofMap(touch.y, 0.0, 1.0, 80, ofGetHeight()-40);
		int size = touch.size*50;
		
		// Transform
		ofPushMatrix();
		ofTranslate(x, y, 0);
		ofRotateZ(touch.angle);
		
		ofEnableSmoothing();
		
		// finger blob circle
		ofSetColor(0, 155, 255);
		ofFill();
		ofEllipse(0, 0, size, size*0.625);
		
		// cross at the circle center
		ofSetColor(0);
		ofNoFill();
		ofLine(-5, 0, 5, 0);
		ofLine(0, -5, 0, +5);
		
		ofDisableSmoothing();
		
		ofPopMatrix();
		
		
		// draw info
		/*char _s [128];
		 sprintf(_s, "ID %05i, frame: %05i, x: %6.3f, y: %6.3f, angle: %8.3f,"
		 "size: %6.3f nFingers: %d\n",
		 touch.ID,touch.frame,touch.x,touch.y,touch.angle,
		 touch.size,pad.getTouchCount());
		 ofSetHexColor(0xffffff);
		 ofDrawBitmapString((string)_s, 0,0);*/
		
		
		
		// OSC
		if(settings.oscOut == 0) {
			
			// Check if padFrame is active
			if (settings.padFrame == 0) {
				// Send osc message, integer value with the current frame.
				// e.g. /mt/1/frame/23
				string sFrame = ofToString("/") + ofToString(settings.padDevicename) + ofToString("/") + ofToString(i) + "/frame";
				oscSender.intMessage(sFrame, touch.frame);
				console.addString(ofToString("OSC ") + ofToString(sFrame) + ofToString("/") + ofToString(touch.frame));
			}
			 
			// check if padTimestamp is active
			/*if (settings.padTimestamp == 0) {
				cout << "padTimestamp " << touch. << endl;
			}*/
			 
			// check if padPosition is active
			if (settings.padPosition == 0) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/x/0.5
				string sX = ofToString("/") + ofToString(settings.padDevicename) + ofToString("/") + ofToString(i) + "/x";
				string sY = ofToString("/") + ofToString(settings.padDevicename) + ofToString("/") + ofToString(i) + "/y";
				oscSender.floatMessage(sX, touch.x);
				oscSender.floatMessage(sY, touch.y);
				console.addString(ofToString("OSC ") + ofToString(sX) + ofToString("/") + ofToString(touch.x));
				console.addString(ofToString("OSC ") + ofToString(sY) + ofToString("/") + ofToString(touch.y));
			}
			 
			// check if padVelocity is active
			/*if (settings.padVelocity == 0) {
				cout << "padVelocity" << endl;
			}*/
			 
			// check if padSize is active
			if (settings.padSize == 0) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/size/0.5
				string sSize = ofToString("/") + ofToString(settings.padDevicename) + ofToString("/") + ofToString(i) + "/size";
				oscSender.floatMessage(sSize, touch.size);
				console.addString(ofToString("OSC ") + ofToString(sSize) + ofToString("/") + ofToString(touch.size));
			}
			 
			// check if padAngle is active
			if (settings.padAngle == 0) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/angle/0.5
				string sAngle = ofToString("/") + ofToString(settings.padDevicename) + ofToString("/") + ofToString(i) + "/angle";
				oscSender.floatMessage(sAngle, touch.angle);
				console.addString(ofToString("OSC ") + ofToString(sAngle) + ofToString("/") + ofToString(touch.angle));
			}
		}
    }
	
	
	// settings button
	if(btnSettings.status == true) {
		// ground
		ofEnableAlphaBlending();
		ofSetColor(0, 150);
		ofFill();
		ofRect(55, 40, ofGetWidth()-110, 500);
		ofDisableAlphaBlending();
		// headline text
		ofSetColor(0, 255, 255);
		vera.drawString("OSC SETTINGS", 60, 70);
		
		vera.drawString("device name (change name at config file)", 60, 115);
		cbFrame.display();
		cbTimestamp.display();
		cbPosition.display();
		cbVelocity.display();
		cbMaxis.display();
		cbSize.display();
		cbAngle.display();
		// shortcuts
		vera.drawString("[Shortcut: 2]", 450, 140);
		vera.drawString("[Shortcut: 3]", 450, 155);
		vera.drawString("[Shortcut: 4]", 450, 170);
		vera.drawString("[Shortcut: 5]", 450, 185);
		vera.drawString("[Shortcut: 6]", 450, 200);
		vera.drawString("[Shortcut: 7]", 450, 215);
		vera.drawString("[Shortcut: 8]", 450, 230);
		
		vera.drawString(ofToString("Number of Devices: ") + ofToString(pad.getNumDevices()), 60, 250);
	}
	
	// console button
	if(btnConsole.status == true) {
		// ground
		ofEnableAlphaBlending();
		ofSetColor(0, 150);
		ofFill();
		ofRect(55, 40, ofGetWidth()-110, 500);
		ofDisableAlphaBlending();
		
		// headline text
		ofSetColor(0, 255, 255);
		vera.drawString("OSC CONSOLE - SEND MESSAGES", 60, 70);
		
		//ofDrawBitmapString("device name (change name at config file)", 60, 115);
		console.display(60, 115);
	}
}



/**
 * Trackpad update
 */
void MultitouchPadOscApp::padUpdates(int & t) {
	printf("pad updates & has %i touches\n",t);
}



/**
 * Trackpad new touch
 */
void MultitouchPadOscApp::newTouch(int & n) {
    printf("+ a new touch\n",n);
}



/**
 * Trackpad remove touch
 */
void MultitouchPadOscApp::removedTouch(int & r) {
    printf("- a removed touch\n",r);
}



/**
 * Key pressed
 */
void MultitouchPadOscApp::keyPressed(int key) {
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
void MultitouchPadOscApp::keyReleased(int key) {
}



/**
 * Mouse moved
 */
void MultitouchPadOscApp::mouseMoved(int x, int y) {
}



/**
 * Mouse dragged
 */
void MultitouchPadOscApp::mouseDragged(int x, int y, int button) {
}



/**
 * Mouse pressed
 */
void MultitouchPadOscApp::mousePressed(int x, int y, int button) {
	// GUI
	btnOscActive.pressed(x, y);
	if(btnOscActive.status == true) {
		settings.oscOut = 0;
	} else {
		settings.oscOut = 1;
	}
	
	
	btnSettings.pressed(x, y);
	if(btnSettings.status == true) {
		// hide console panel
		btnConsole.status = false;
		
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
	
	
	btnConsole.pressed(x, y);
	if(btnConsole.status == true) {
		// hide settings panel
		btnSettings.status = false;
	}
}



/**
 * Mouse released
 */
void MultitouchPadOscApp::mouseReleased(int x, int y, int button) {
}



/**
 * Window resized
 */
void MultitouchPadOscApp::windowResized(int w, int h) {
}



/**
 * Got message
 */
void MultitouchPadOscApp::gotMessage(ofMessage msg) {
}



/**
 * Drag event
 */
void MultitouchPadOscApp::dragEvent(ofDragInfo dragInfo) {
}



/**
 * Exit
 *
 * Update XML settings variables.
 * Save the current app count, window position and framerate.
 * Save OSC variables like Host, Port etc.
 */
void MultitouchPadOscApp::exit() {
	// Update settings file.
	settings.save();
}
