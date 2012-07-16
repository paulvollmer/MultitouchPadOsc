/**
 *  MultitouchPadOscApp.cpp
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
 *  @version          0.1.2
 */

#include "MultitouchPadOscApp.h"





/**
 * Setup
 * 
 * Load the default settings xml.
 * Load Font
 * Initialize osc sender
 * Initialize ofxMultiTouchPad
 * Load background image.
 * Initialize GUI
 */
void MultitouchPadOscApp::setup() {
	
	// ofxXmlDefaultSettings
	// Load our default xml file.
	defXml.load();
	
	defXml.setFrameRate();
	defXml.setFullscreen();
	//defXml.setWindowShape();
	ofSetWindowShape(500, 400);
	defXml.setWindowPosition();
	//defXml.setWindowTitle();
	ofSetWindowTitle("MultitouchPadOsc");
	
	// OSC variables
	if (defXml.tagExists("osc", 0)) {
		defXmlOscOut  = defXml.getValue("osc:out", 1);
		defXmlOscHost = defXml.getValue("osc:host", "127.0.0.1");
		defXmlOscPort = defXml.getValue("osc:port", 12345);
	}
	// if no default parameter exist, let create some.
	else {
		defXmlOscOut  = 1;
		defXmlOscHost = "127.0.0.1";
		defXmlOscPort = 12345;
		
		defXml.addTag("osc");
		defXml.pushTag("osc", 0);
		defXml.addValue("out", defXmlOscOut);
		defXml.addValue("host", defXmlOscHost);
		defXml.addValue("port", defXmlOscPort);
		defXml.popTag();
		defXml.saveFile();
	}
	// Trackpad variables
	if (defXml.tagExists("pad", 0)) {
		defXmlPadDevicename = defXml.getValue("pad:devicename", "mtpadosc");
		defXmlPadFrame      = defXml.getValue("pad:frame", 1);
		defXmlPadTimestamp  = defXml.getValue("pad:timestamp", 1);
		defXmlPadPosition   = defXml.getValue("pad:position", 1);
		defXmlPadVelocity   = defXml.getValue("pad:velocity", 1);
		defXmlPadSize       = defXml.getValue("pad:size", 1);
		defXmlPadMaxis      = defXml.getValue("pad:maxis", 1);
		defXmlPadAngle      = defXml.getValue("pad:angle", 1);
	}
	else {
		defXmlPadDevicename = "mtpadosc";
		defXmlPadFrame      = 1;
		defXmlPadTimestamp  = 1;
		defXmlPadPosition   = 1;
		defXmlPadVelocity   = 1;
		defXmlPadSize       = 1;
		defXmlPadMaxis      = 1;
		defXmlPadAngle      = 1;
		
		defXml.addTag("pad");
		defXml.pushTag("pad", 0);
		defXml.addValue("devicename", defXmlPadDevicename);
		defXml.addValue("frame", defXmlPadFrame);
		defXml.addValue("timestamp", defXmlPadTimestamp);
		defXml.addValue("position", defXmlPadPosition);
		defXml.addValue("velocity", defXmlPadVelocity);
		defXml.addValue("size", defXmlPadSize);
		defXml.addValue("maxis", defXmlPadMaxis);
		defXml.addValue("angle", defXmlPadAngle);
		defXml.popTag();
		defXml.saveFile();
	}
	
	ofLog() << "[MultitouchPadOsc] XML default settings loaded";
	ofLog() << "[MultitouchPadOsc] XML osc:out        = " << defXmlOscOut;
	ofLog() << "[MultitouchPadOsc] XML osc:host       = " << defXmlOscHost;
	ofLog() << "[MultitouchPadOsc] XML osc:port       = " << defXmlOscPort;
	ofLog() << "[MultitouchPadOsc] XML pad:devicename = " << defXmlPadDevicename;
	ofLog() << "[MultitouchPadOsc] XML pad:frame      = " << defXmlPadFrame;
	ofLog() << "[MultitouchPadOsc] XML pad:timestamp  = " << defXmlPadTimestamp;
	ofLog() << "[MultitouchPadOsc] XML pad:position   = " << defXmlPadPosition;
	ofLog() << "[MultitouchPadOsc] XML pad:velocity   = " << defXmlPadVelocity;
	ofLog() << "[MultitouchPadOsc] XML pad:size       = " << defXmlPadSize;
	ofLog() << "[MultitouchPadOsc] XML pad:maxis      = " << defXmlPadMaxis;
	ofLog() << "[MultitouchPadOsc] XML pad:angle      = " << defXmlPadAngle;
	
	
	
	// Set the data-path to application/Recource directory.
	// Use the Application Support directory for RELEASE mode.
	//ofSetDataPathRoot("/Library/Application Support/MultitouchPadOsc/");
	
	
	// Font
	vera.loadFont(ofFilePath::getCurrentWorkingDirectory() + "/Font/Vera.ttf", 9, true, false);
	
	
	// OSC
	oscSender.init(defXmlOscHost, defXmlOscPort);
	console.addString(ofToString("Host: ") + ofToString(defXmlOscHost) + ofToString(" Port: ") + ofToString(defXmlOscPort) + " connected");
	
	
	// Console
	console.init(vera);
	
	
	// Images
	oscSendImage.loadImage(ofFilePath::getCurrentWorkingDirectory() + "/gui/oscactive_send.png");
	
	
	// GUI
	// set the status to osc:out settings value
	btnOscActive.init(ofFilePath::getCurrentWorkingDirectory() + "/gui/oscactive_on.png", ofFilePath::getCurrentWorkingDirectory() + "/gui/oscactive_off.png", ofGetWidth()-36, 0);
	if(defXmlOscOut == 0) btnOscActive.status = true;
	else btnOscActive.status = false;
	
	btnSettings.init(ofFilePath::getCurrentWorkingDirectory() + "/gui/settings_on.png",  ofFilePath::getCurrentWorkingDirectory() + "/gui/settings_off.png",  10,  0);
	btnConsole.init(ofFilePath::getCurrentWorkingDirectory() + "/gui/console_on.png",    ofFilePath::getCurrentWorkingDirectory() + "/gui/console_off.png",   87, 0);
	
	cbFrame.init(vera,      "frame active",               15, 190, defXmlPadFrame);
	//cbTimestamp.init(vera,  "timestamp active",           60, 170, defXmlPadTimestamp);
	cbPosition.init(vera,   "x-, y-position active",      15, 210, defXmlPadPosition);
	//cbVelocity.init(vera,   "x-, y-velocity active",      60, 200, defXmlPadVelocity);
	//cbMaxis.init(vera,      "minor-, major-axis active",  60, 215, defXmlPadMaxis);
	cbSize.init(vera,       "size active",                15, 230, defXmlPadSize);
	cbAngle.init(vera,      "angle active",               15, 250, defXmlPadAngle);
	
	
	// Multitouch Trackpad
	// Add the listeners
    ofAddListener(pad.update, this, &MultitouchPadOscApp::padUpdates);
    ofAddListener(pad.touchAdded, this, &MultitouchPadOscApp::newTouch);
    ofAddListener(pad.touchRemoved, this, &MultitouchPadOscApp::removedTouch);
	//cout << "  number of trackpad devices: " << pad.getNumDevices() << endl;
	
	
	// Add messages to Console
	console.addString("Application started!");
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
void MultitouchPadOscApp::draw(){
	
	// background
	ofBackground(111, 112, 114);
	
	ofFill();
	ofSetColor(88, 88, 90);
	ofRect(10, 30, ofGetWidth()-20, ofGetHeight()-40);
	
	
	// GUI
	ofSetColor(255);
	btnOscActive.display();
	btnSettings.display();
	btnConsole.display();
	
	
	//
    ofSetColor(255);
	vera.drawString("Touch Count: "+ofToString(pad.getTouchCount(), 0), 15, ofGetHeight()-15);
	
	
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
		if(defXmlOscOut == 0) {
			// if osc message will be send,
			// show osc send icon.
			ofSetColor(255);
			ofFill();
			oscSendImage.draw(ofGetWidth()-36, 0);
		
			
			// Check if padFrame is active
			if (defXmlPadFrame == 0) {
				// Send osc message, integer value with the current frame.
				// e.g. /mt/1/frame/23
				string sFrame = ofToString("/") + ofToString(defXmlPadDevicename) + ofToString("/") + ofToString(i) + "/frame";
				oscSender.intMessage(sFrame, touch.frame);
				console.addString(ofToString("OSC ") + ofToString(sFrame) + ofToString("/") + ofToString(touch.frame));
			}
			 
			// check if padTimestamp is active
			/*if (settings.padTimestamp == 0) {
				Finger finger;
				cout << "padTimestamp " << finger.timestamp << endl;
			}*/
			 
			// check if padPosition is active
			if (defXmlPadPosition == 0) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/x/0.5
				string sX = ofToString("/") + ofToString(defXmlPadDevicename) + ofToString("/") + ofToString(i) + "/x";
				string sY = ofToString("/") + ofToString(defXmlPadDevicename) + ofToString("/") + ofToString(i) + "/y";
				oscSender.floatMessage(sX, touch.x);
				oscSender.floatMessage(sY, touch.y);
				console.addString(ofToString("OSC ") + ofToString(sX) + ofToString("/") + ofToString(touch.x));
				console.addString(ofToString("OSC ") + ofToString(sY) + ofToString("/") + ofToString(touch.y));
			}
			 
			// check if padVelocity is active
			/*if (settings.padVelocity == 0) {
				Finger finger;
				cout << "padVelocity " << finger.mm.vel.x << endl;
			}*/
			 
			// check if padSize is active
			if (defXmlPadSize == 0) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/size/0.5
				string sSize = ofToString("/") + ofToString(defXmlPadDevicename) + ofToString("/") + ofToString(i) + "/size";
				oscSender.floatMessage(sSize, touch.size);
				console.addString(ofToString("OSC ") + ofToString(sSize) + ofToString("/") + ofToString(touch.size));
			}
			 
			// check if padAngle is active
			if (defXmlPadAngle == 0) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/angle/0.5
				string sAngle = ofToString("/") + ofToString(defXmlPadDevicename) + ofToString("/") + ofToString(i) + "/angle";
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
		ofRect(10, 30, ofGetWidth()-20, ofGetHeight()-40);
		ofDisableAlphaBlending();
		// Osc settings
		ofSetColor(ofColor::white);
		ofFill();
		vera.drawString("OSC SETTINGS", 15, 50);
		// Host: xxx.xxx.xxx.xxx Port: xxxx, Touch Count
		vera.drawString("Host: "+ofToString(defXmlOscHost), 15, 90);
		vera.drawString("[change at settings.xml file]", 251, 90);
		vera.drawString("Port: "+ofToString(defXmlOscPort), 15, 110);
		vera.drawString("[change at settings.xml file]", 251, 110);
		vera.drawString("Devicename: " + defXmlPadDevicename, 15, 130);
		vera.drawString("[change at settings.xml file]", 251, 130);
		vera.drawString("[To open the settings xml, press key '0']", 167, 150);
		cbFrame.display();
		//cbTimestamp.display();
		cbPosition.display();
		//cbVelocity.display();
		//cbMaxis.display();
		cbSize.display();
		cbAngle.display();
		// shortcuts
		vera.drawString("[Shortcut: 2]", 350, 200);
		vera.drawString("[Shortcut: 3]", 350, 220);
		vera.drawString("[Shortcut: 4]", 350, 240);
		vera.drawString("[Shortcut: 5]", 350, 260);
		
		//vera.drawString(ofToString("Number of Devices: ") + ofToString(pad.getNumDevices()), 15, 150);
	}
	
	// console button
	if(btnConsole.status == true) {
		// ground
		ofEnableAlphaBlending();
		ofSetColor(0, 150);
		ofFill();
		ofRect(10, 30, ofGetWidth()-20, ofGetHeight()-40);
		ofDisableAlphaBlending();
		
		// headline text
		ofSetColor(ofColor::white);
		vera.drawString("OSC CONSOLE - SEND MESSAGES", 15, 50);
		console.display(15, 90);
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
	// Open the settings xml file
	if(key == '0') {
		string commandStr = "open " + ofFilePath::getCurrentWorkingDirectory() + "/ofSettings.xml";
		system(commandStr.c_str());
	}
	
	
	switch(key) {
		// OSC out
		case '1':
			if (defXmlOscOut == 0) {
				defXmlOscOut = 1;
				btnOscActive.status = !btnOscActive.status;
			} else {
				defXmlOscOut = 0;
				btnOscActive.status = !btnOscActive.status;
			}
			cout << "Shortcut oscOut: " << defXmlOscOut << endl;
			break;
		
		// OSC frame
		case '2':
			if (defXmlPadFrame == 0) {
				defXmlPadFrame = 1;
			} else {
				defXmlPadFrame = 0;
			}
			cbFrame.status = defXmlPadFrame;
			
			cout << "Shortcut padFrame: " << defXmlPadFrame << endl;
			break;
		
		// OSC timestamp
		/*case '3':
			if (settings.padTimestamp == 0) {
				settings.padTimestamp = 1;
			} else {
				settings.padTimestamp = 0;
			}
			cbTimestamp.status = settings.padTimestamp;
			
			cout << "Shortcut padTimestamp: " << settings.padTimestamp << endl;
			break;*/
		
		// OSC position
		case '3':
			if (defXmlPadPosition == 0) {
				defXmlPadPosition = 1;
			} else {
				defXmlPadPosition = 0;
			}
			cbPosition.status = defXmlPadPosition;
			
			cout << "Shortcut padPosition: " << defXmlPadPosition << endl;
			break;

		// OSC velocity
		/*case '5':
			if (settings.padVelocity == 0) {
				settings.padVelocity = 1;
			} else {
				settings.padVelocity = 0;
			}
			cbVelocity.status = settings.padVelocity;
			
			cout << "Shortcut padVelocity: " << settings.padVelocity << endl;
			break;*/

		// OSC maxis
		/*case '4':
			if (settings.padMaxis == 0) {
				settings.padMaxis = 1;
			} else {
				settings.padMaxis = 0;
			}
			cbMaxis.status = settings.padMaxis;
			
			cout << "Shortcut padMaxis: " << settings.padMaxis << endl;
			break;*/

		// OSC maxis
		case '4':
			if (defXmlPadSize == 0) {
				defXmlPadSize = 1;
			} else {
				defXmlPadSize = 0;
			}
			cbSize.status = defXmlPadSize;
			
			cout << "Shortcut padSize: " << defXmlPadSize << endl;
			break;

		// OSC angle
		case '5':
			if (defXmlPadAngle == 0) {
				defXmlPadAngle = 1;
			} else {
				defXmlPadAngle = 0;
			}
			cbAngle.status = defXmlPadAngle;
			
			cout << "Shortcut padAngle: " << defXmlPadAngle << endl;
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
		defXmlOscOut = 0;
	} else {
		defXmlOscOut = 1;
	}
	
	
	btnSettings.pressed(x, y);
	if(btnSettings.status == true) {
		// hide console panel
		btnConsole.status = false;
		
		cbFrame.pressed(x, y);
		defXmlPadFrame = cbFrame.status;
		
		//cbTimestamp.pressed(x, y);
		//settings.padTimestamp = cbTimestamp.status;
		
		cbPosition.pressed(x, y);
		defXmlPadPosition = cbPosition.status;
		
		//cbVelocity.pressed(x, y);
		//settings.padVelocity = cbVelocity.status;
		
		//cbMaxis.pressed(x, y);
		//settings.padMaxis = cbMaxis.status;
		
		cbSize.pressed(x, y);
		defXmlPadSize = cbSize.status;
		
		cbAngle.pressed(x, y);
		defXmlPadAngle = cbAngle.status;
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
	btnOscActive.setPosition(w-36, 0);
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
	
	//defXML.setWindowPosition();
	defXml.setValue("pad:devicename", defXmlPadDevicename, 0);
	defXml.setValue("pad:frame", defXmlPadFrame, 0);
	defXml.setValue("pad:timestamp", defXmlPadTimestamp, 0);
	defXml.setValue("pad:position", defXmlPadPosition, 0);
	defXml.setValue("pad:velocity", defXmlPadVelocity, 0);
	defXml.setValue("pad:size", defXmlPadSize, 0);
	defXml.setValue("pad:maxis", defXmlPadMaxis, 0);
	defXml.setValue("pad:angle", defXmlPadAngle, 0);
	
	// Save the current settings to xml.
	defXml.saveSettings();
}
