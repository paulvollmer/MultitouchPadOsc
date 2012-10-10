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
 *  @modified         2012.08.01
 *  @version          0.1.2b
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
	
	/* Set the xml tag names and root-version, -url attributes.
	 */
	XML.changeSyntax(XML.ROOT, "multitouchPadOscApp");
	XML.changeSyntax(XML.ROOT_VERSION, PROJECTVERSION);
	XML.changeSyntax(XML.ROOT_URL, "http://www.wng.cc");
	XML.changeSyntax(XML.CORE, "appCore");
	
	/* Set the default Settings parameter.
	 */
	XML.defaultSettings.frameRate = 60;
	XML.defaultSettings.windowX = 100;
	XML.defaultSettings.windowY = 100;
	XML.defaultSettings.windowWidth = 500;
	XML.defaultSettings.windowHeight = 400;
	XML.defaultSettings.windowTitle = PROJECTNAME;
	XML.defaultSettings.cursor = false;
	XML.defaultSettings.fullscreen = false;
	XML.defaultSettings.escapeQuitsApp = true;
	XML.defaultSettings.log = true;
	
	/* ofxXmlDefaultSettings
	 * Load the xml file from default path.
	 */
	XML.load();
	
	/* Set the openFrameworks app settings.
	 */
	XML.setSettings();
	ofLog() << "XML: " << XML.getStatusMessage();
	
	/* Add custom settings to the xml default file.
	 * To read/write content from the root directory, you can use
	 * the pushRoot/popRoot methods.
	 */
	XML.pushRoot();
	if (XML.fileExist) {
		/* OSC variables
		 */
		defXmlOscOut  = XML.getValue("osc", 1);
		defXmlOscHost = XML.getAttribute("osc", "host", "127.0.0.1", 0);
		defXmlOscPort = XML.getAttribute("osc", "port", 12345, 0);
		/* Touchpoint color
		 */
		defXmlTouchpointColor[0] = XML.getAttribute("touchpoints:pointColor", "r", 0, 0);
		defXmlTouchpointColor[1] = XML.getAttribute("touchpoints:pointColor", "g", 155, 0);
		defXmlTouchpointColor[2] = XML.getAttribute("touchpoints:pointColor", "b", 255, 0);
		defXmlTouchpointColor[3] = XML.getAttribute("touchpoints:pointColor", "a", 255, 0);
		defXmlTouchpointLines[0] = XML.getAttribute("touchpoints:lineColor", "r", 0, 0);
		defXmlTouchpointLines[1] = XML.getAttribute("touchpoints:lineColor", "g", 255, 0);
		defXmlTouchpointLines[2] = XML.getAttribute("touchpoints:lineColor", "b", 255, 0);
		defXmlTouchpointLines[3] = XML.getAttribute("touchpoints:lineColor", "a", 255, 0);
		defXmlTouchpointCross[0] = XML.getAttribute("touchpoints:crossColor", "r", 255, 0);
		defXmlTouchpointCross[1] = XML.getAttribute("touchpoints:crossColor", "g", 0, 0);
		defXmlTouchpointCross[2] = XML.getAttribute("touchpoints:crossColor", "b", 0, 0);
		defXmlTouchpointCross[3] = XML.getAttribute("touchpoints:crossColor", "a", 255, 0);
		/* Trackpad variables
		 */
		defXmlPadDevicename = XML.getValue("pad:devicename", "mtpadosc");
		defXmlPadFrame      = XML.getValue("pad:frame", 1);
		defXmlPadTimestamp  = XML.getValue("pad:timestamp", 1);
		defXmlPadPosition   = XML.getValue("pad:position", 1);
		defXmlPadVelocity   = XML.getValue("pad:velocity", 1);
		defXmlPadSize       = XML.getValue("pad:size", 1);
		defXmlPadMaxis      = XML.getValue("pad:maxis", 1);
		defXmlPadAngle      = XML.getValue("pad:angle", 1);
	}
	/* If no xml file exist, create the <balls> tag and add some parameter.
	 */
	else {
		/* OSC variables
		 */
		defXmlOscOut  = 1;
		defXmlOscHost = "127.0.0.1";
		defXmlOscPort = 12345;
		XML.addValue("osc", defXmlOscOut);
		XML.addAttribute("osc", "host", defXmlOscHost, 0);
		XML.addAttribute("osc", "post", defXmlOscPort, 0);
		/* Touchpoint color
		 */
		defXmlTouchpointColor.set(0, 155, 255, 255);
		defXmlTouchpointLines.set(0, 255, 255, 255);
		defXmlTouchpointCross.set(255, 255, 255, 255);
		XML.addTag("touchpoints");
		XML.pushTag("touchpoints", 0);
		XML.addTag("pointColor");
		XML.addAttribute("pointColor", "r", defXmlTouchpointColor[0], 0);
		XML.addAttribute("pointColor", "g", defXmlTouchpointColor[1], 0);
		XML.addAttribute("pointColor", "b", defXmlTouchpointColor[2], 0);
		XML.addAttribute("pointColor", "a", defXmlTouchpointColor[3], 0);
		XML.addTag("lineColor");
		XML.addAttribute("lineColor", "r", defXmlTouchpointLines[0], 0);
		XML.addAttribute("lineColor", "g", defXmlTouchpointLines[1], 0);
		XML.addAttribute("lineColor", "b", defXmlTouchpointLines[2], 0);
		XML.addAttribute("lineColor", "a", defXmlTouchpointLines[3], 0);
		XML.addTag("crossColor");
		XML.addAttribute("crossColor", "r", defXmlTouchpointCross[0], 0);
		XML.addAttribute("crossColor", "g", defXmlTouchpointCross[1], 0);
		XML.addAttribute("crossColor", "b", defXmlTouchpointCross[2], 0);
		XML.addAttribute("crossColor", "a", defXmlTouchpointCross[3], 0);
		XML.popTag();
		/* Trackpad variables
		 */
		defXmlPadDevicename = "mtpad";
		defXmlPadFrame      = 1;
		defXmlPadTimestamp  = 1;
		defXmlPadPosition   = 1;
		defXmlPadVelocity   = 1;
		defXmlPadSize       = 1;
		defXmlPadMaxis      = 1;
		defXmlPadAngle      = 1;
		XML.addTag("pad");
		XML.pushTag("pad", 0);
		XML.addValue("devicename", defXmlPadDevicename);
		XML.addValue("frame", defXmlPadFrame);
		XML.addValue("timestamp", defXmlPadTimestamp);
		XML.addValue("position", defXmlPadPosition);
		XML.addValue("velocity", defXmlPadVelocity);
		XML.addValue("size", defXmlPadSize);
		XML.addValue("maxis", defXmlPadMaxis);
		XML.addValue("angle", defXmlPadAngle);
		XML.popTag();
	}

	/* Pop root xml tag.
	 */
	XML.popRoot();
	
	/* Log the XML parameter
	 */
	ofLog() << "XML: osc:out         = " << defXmlOscOut;
	ofLog() << "XML: osc:host        = " << defXmlOscHost;
	ofLog() << "XML: osc:port        = " << defXmlOscPort;
	ofLog() << "XML: pad:devicename  = " << defXmlPadDevicename;
	ofLog() << "XML: pad:frame       = " << defXmlPadFrame;
	ofLog() << "XML: pad:timestamp   = " << defXmlPadTimestamp;
	ofLog() << "XML: pad:position    = " << defXmlPadPosition;
	ofLog() << "XML: pad:velocity    = " << defXmlPadVelocity;
	ofLog() << "XML: pad:size        = " << defXmlPadSize;
	ofLog() << "XML: pad:maxis       = " << defXmlPadMaxis;
	ofLog() << "XML: pad:angle       = " << defXmlPadAngle;
	ofLog() << "XML: pointColor rgba =" << defXmlTouchpointColor.getClamped();
	ofLog() << "XML: lineColor rgba  =" << defXmlTouchpointLines.getClamped();
	ofLog() << "XML: crossColor rgba =" << defXmlTouchpointCross.getClamped();
	
	/* Save the XML file if no file existed
	 */
	if (XML.fileExist == false) {
		XML.saveFile();
	}
	
	
	/* Load the font
	 */
	vera.loadFont(ofFilePath::getCurrentWorkingDirectory() + "/Font/Vera.ttf", 9, true, false);
	
	
	/* OSC
	 * Open an outgoing connection to oscHost, oscPort
	 */
	oscSender.setup(defXmlOscHost, defXmlOscPort);
	console.addString(ofToString("Host: ") + ofToString(defXmlOscHost) + ofToString(" Port: ") + ofToString(defXmlOscPort) + " connected");
	
	
	/* Console
	 */
	console.init(vera);
	
	
	/* Images
	 */
	oscSendImage.loadImage(ofFilePath::getCurrentWorkingDirectory() + "/gui/oscactive_send.png");
	
	
	/* GUI
	 * set the status to osc:out settings value
	 */
	gui = new ofxUICanvas();
	gui->setFont(ofFilePath::getCurrentWorkingDirectory() + "/Font/Vera.ttf"); //This loads a new font and sets the GUI font
    gui->setFontSize(OFX_UI_FONT_LARGE, 9);                                   //These call are optional, but if you want to resize the LARGE, MEDIUM, and SMALL fonts, here is how to do it. 
    gui->setFontSize(OFX_UI_FONT_MEDIUM, 8);           
    gui->setFontSize(OFX_UI_FONT_SMALL, 6);                                   //SUPER IMPORTANT NOTE: CALL THESE FUNTIONS BEFORE ADDING ANY WIDGETS, THIS AFFECTS THE SPACING OF THE GUI
	gui->addWidget(new ofxUITextInput("TEXT HOST", defXmlOscHost, 150, 20, 100,100, OFX_UI_FONT_SMALL));
	gui->addWidget(new ofxUITextInput("TEXT PORT", ofToString(defXmlOscPort), 150, 20, 100,130, OFX_UI_FONT_SMALL));
	ofAddListener(gui->newGUIEvent, this, &MultitouchPadOscApp::guiEvent);
	gui->setVisible(false);
	
	
	btnOscActive.init(ofFilePath::getCurrentWorkingDirectory() + "/gui/oscactive_on.png", ofFilePath::getCurrentWorkingDirectory() + "/gui/oscactive_off.png", ofGetWidth()-36, 0);
	if (defXmlOscOut == 0) {
		btnOscActive.status = true;
	} else {
		btnOscActive.status = false;
	}
	
	btnTouchpoints.init(ofFilePath::getCurrentWorkingDirectory() + "/gui/settings_on.png",  ofFilePath::getCurrentWorkingDirectory() + "/gui/settings_off.png", 10, 0);
	btnTouchpoints.status = true;
	btnSettings.init(ofFilePath::getCurrentWorkingDirectory() + "/gui/settings_on.png",  ofFilePath::getCurrentWorkingDirectory() + "/gui/settings_off.png", 87, 0);
	btnConsole.init(ofFilePath::getCurrentWorkingDirectory() + "/gui/console_on.png",    ofFilePath::getCurrentWorkingDirectory() + "/gui/console_off.png", 164, 0);
	
	cbFrame.init(vera,      "frame active",               15, 190, defXmlPadFrame);
	//cbTimestamp.init(vera,  "timestamp active",           60, 170, defXmlPadTimestamp);
	cbPosition.init(vera,   "x-, y-position active",      15, 210, defXmlPadPosition);
	//cbVelocity.init(vera,   "x-, y-velocity active",      60, 200, defXmlPadVelocity);
	//cbMaxis.init(vera,      "minor-, major-axis active",  60, 215, defXmlPadMaxis);
	cbSize.init(vera,       "size active",                15, 230, defXmlPadSize);
	cbAngle.init(vera,      "angle active",               15, 250, defXmlPadAngle);
	
	
	/* Multitouch Trackpad
	 * Add the listeners
	 */
    ofAddListener(pad.update, this, &MultitouchPadOscApp::padUpdates);
    ofAddListener(pad.touchAdded, this, &MultitouchPadOscApp::newTouch);
    ofAddListener(pad.touchRemoved, this, &MultitouchPadOscApp::removedTouch);
	cout << "  number of trackpad devices: " << pad.getNumDevices() << endl;
	
	
	/* Add messages to Console
	 */
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
	btnTouchpoints.display();
	btnOscActive.display();
	btnSettings.display();
	btnConsole.display();
	
	
	// Draw the touch count typo
    ofSetColor(255);
	vera.drawString("Viewer", 20, 18);
	vera.drawString("Settings", 120, 18);
	vera.drawString("Console", 220, 18);
	vera.drawString("Touch Count: "+ofToString(pad.getTouchCount(), 0), 15, ofGetHeight()-15);
	
	
	// Display finger blobs
	// connect all touches with a line
    std::vector<ofPoint>touches;
    pad.getTouchesAsOfPoints(&touches);
	
	ofEnableSmoothing();
    for(int i=0; (i<touches.size()-1 && touches.size()>1); i++) {
        ofSetColor(defXmlTouchpointLines);
        int x1 = ofMap(touches.at(i).x,   0.0, 1.0, 40, ofGetWidth()-40);
		int y1 = ofMap(touches.at(i).y,   0.0, 1.0, 80, ofGetHeight()-40);
		int x2 = ofMap(touches.at(i+1).x, 0.0, 1.0, 40, ofGetWidth()-40);
		int y2 = ofMap(touches.at(i+1).y, 0.0, 1.0, 80, ofGetHeight()-40);
		ofLine(x1, y1, x2, y2);
    }
	ofDisableSmoothing();
    
	
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
		ofSetColor(defXmlTouchpointColor);
		ofFill();
		ofEllipse(0, 0, size, size*0.625);
		
		// cross at the circle center
		ofSetColor(defXmlTouchpointCross);
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
				
				intMessage(sFrame, touch.frame);
				
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
				floatMessage(sX, touch.x);
				floatMessage(sY, touch.y);
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
				floatMessage(sSize, touch.size);
				console.addString(ofToString("OSC ") + ofToString(sSize) + ofToString("/") + ofToString(touch.size));
			}
			 
			// check if padAngle is active
			if (defXmlPadAngle == 0) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/angle/0.5
				string sAngle = ofToString("/") + ofToString(defXmlPadDevicename) + ofToString("/") + ofToString(i) + "/angle";
				floatMessage(sAngle, touch.angle);
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
 * Exit
 *
 * Update XML settings variables.
 * Save the current app count, window position and framerate.
 * Save OSC variables like Host, Port etc.
 */
void MultitouchPadOscApp::exit() {
	
	XML.pushRoot();
	//defXML.setWindowPosition();
	XML.setValue("osc", defXmlOscOut, 0);
	XML.setValue("pad:devicename", defXmlPadDevicename, 0);
	XML.setValue("pad:frame", defXmlPadFrame, 0);
	XML.setValue("pad:timestamp", defXmlPadTimestamp, 0);
	XML.setValue("pad:position", defXmlPadPosition, 0);
	XML.setValue("pad:velocity", defXmlPadVelocity, 0);
	XML.setValue("pad:size", defXmlPadSize, 0);
	XML.setValue("pad:maxis", defXmlPadMaxis, 0);
	XML.setValue("pad:angle", defXmlPadAngle, 0);
	XML.popRoot();
	
	/* Save the current settings to xml.
	 */
	XML.save();
	
	/* GUI
	 */
	delete gui;
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
			#ifdef MULTITOUCHPADOSC_DEBUG
				cout << "Shortcut oscOut: " << defXmlOscOut << endl;
			#endif
			break;
		
		// OSC frame
		case '2':
			if (defXmlPadFrame == 0) {
				defXmlPadFrame = 1;
			} else {
				defXmlPadFrame = 0;
			}
			cbFrame.status = defXmlPadFrame;
			
			#ifdef MULTITOUCHPADOSC_DEBUG
				cout << "Shortcut padFrame: " << defXmlPadFrame << endl;
			#endif
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
			
			#ifdef MULTITOUCHPADOSC_DEBUG
				cout << "Shortcut padPosition: " << defXmlPadPosition << endl;
			#endif
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
			
			#ifdef MULTITOUCHPADOSC_DEBUG
				cout << "Shortcut padSize: " << defXmlPadSize << endl;
			#endif
			break;

		// OSC angle
		case '5':
			if (defXmlPadAngle == 0) {
				defXmlPadAngle = 1;
			} else {
				defXmlPadAngle = 0;
			}
			cbAngle.status = defXmlPadAngle;
			
			#ifdef MULTITOUCHPADOSC_DEBUG
				cout << "Shortcut padAngle: " << defXmlPadAngle << endl;
			#endif
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
	
	
	btnTouchpoints.pressed(x, y);
	if(btnTouchpoints.status == true) {
		// hide touchpoint, settings panel
		btnSettings.status = false;
		btnConsole.status = false;
		
		/* hide GUI textfield
		 */
		gui->setVisible(false);
	}
	
	
	btnSettings.pressed(x, y);
	if(btnSettings.status == true) {
		// hide touchpoint, console panel
		btnTouchpoints.status = false;
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
		
		/* show GUI textfield
		 */
		gui->setVisible(true);
	}
	
	
	btnConsole.pressed(x, y);
	if(btnConsole.status == true) {
		// hide touchpoint, settings panel
		btnTouchpoints.status = false;
		btnSettings.status = false;
		
		/* hide GUI textfield
		 */
		gui->setVisible(false);
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
 * Send an osc message (integer value)
 */
void MultitouchPadOscApp::intMessage(string s, int val) {
	ofxOscMessage m;
	
	m.setAddress(s);
	m.addIntArg(val);
	
	oscSender.sendMessage(m);
}



/**
 * Send an osc message (float value)
 */
void MultitouchPadOscApp::floatMessage(string s, float val) {
	ofxOscMessage m;
	
	m.setAddress(s);
	m.addFloatArg(val);
	
	oscSender.sendMessage(m);
}



/**
 * Gui event
 */
void MultitouchPadOscApp::guiEvent(ofxUIEventArgs &e) {
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
	if (name == "TEXT HOST") {
		ofxUITextInput *textInput = (ofxUITextInput *) e.widget;
		cout << "### TEXT HOST = " << textInput->getTextString() << endl;
	} else if (name == "TEXT PORT") {
		ofxUITextInput *textInput = (ofxUITextInput *) e.widget;
		cout << "### TEXT HOST = " << textInput->getTextString() << endl;
	}
}
