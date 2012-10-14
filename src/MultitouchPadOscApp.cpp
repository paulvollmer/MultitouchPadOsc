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

#include "MultitouchPadOscApp.h"



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
	
	/* Add custom settings to the xml default file.
	 * To read/write content from the root directory, you can use
	 * the pushRoot/popRoot methods.
	 */
	XML.pushRoot();
	if (XML.fileExist) {
		/* Other Application Core Settings
		 */
		xmlWindowMode = XML.getAttribute(XML.getSyntax(XML.CORE)+":window", "mode", false, 0);
		
		/* OSC variables
		 */
		xmlOscOut  = XML.getValue("osc", 1);
		xmlOscHost = XML.getAttribute("osc", "host", "127.0.0.1", 0);
		xmlOscPort = XML.getAttribute("osc", "port", 12345, 0);
		/* Touchpoint color
		 */
		xmlTouchpointColor[0] = XML.getAttribute("touchpoints:pointColor", "r", 0, 0);
		xmlTouchpointColor[1] = XML.getAttribute("touchpoints:pointColor", "g", 155, 0);
		xmlTouchpointColor[2] = XML.getAttribute("touchpoints:pointColor", "b", 255, 0);
		xmlTouchpointColor[3] = XML.getAttribute("touchpoints:pointColor", "a", 255, 0);
		xmlTouchpointLines[0] = XML.getAttribute("touchpoints:lineColor", "r", 0, 0);
		xmlTouchpointLines[1] = XML.getAttribute("touchpoints:lineColor", "g", 255, 0);
		xmlTouchpointLines[2] = XML.getAttribute("touchpoints:lineColor", "b", 255, 0);
		xmlTouchpointLines[3] = XML.getAttribute("touchpoints:lineColor", "a", 255, 0);
		xmlTouchpointCross[0] = XML.getAttribute("touchpoints:crossColor", "r", 255, 0);
		xmlTouchpointCross[1] = XML.getAttribute("touchpoints:crossColor", "g", 0, 0);
		xmlTouchpointCross[2] = XML.getAttribute("touchpoints:crossColor", "b", 0, 0);
		xmlTouchpointCross[3] = XML.getAttribute("touchpoints:crossColor", "a", 255, 0);
		/* Trackpad variables
		 */
		xmlPadDevicename = XML.getValue("pad:devicename", "mtpadosc");
		xmlPadFrame      = XML.getValue("pad:frame", 1);
		xmlPadTimestamp  = XML.getValue("pad:timestamp", 1);
		xmlPadPosition   = XML.getValue("pad:position", 1);
		xmlPadVelocity   = XML.getValue("pad:velocity", 1);
		xmlPadSize       = XML.getValue("pad:size", 1);
		xmlPadMaxis      = XML.getValue("pad:maxis", 1);
		xmlPadAngle      = XML.getValue("pad:angle", 1);
	}
	/* If no xml file exist, create the <balls> tag and add some parameter.
	 */
	else {
		/* Other Application Core Settings
		 */
		xmlWindowMode = false;
		XML.pushTag(XML.getSyntax(XML.CORE), 0);
		XML.addAttribute("window", "mode", xmlWindowMode, 0);
		XML.popTag();
		/* OSC variables
		 */
		xmlOscOut  = 1;
		xmlOscHost = "127.0.0.1";
		xmlOscPort = 12345;
		XML.addValue("osc", xmlOscOut);
		XML.addAttribute("osc", "host", xmlOscHost, 0);
		XML.addAttribute("osc", "post", xmlOscPort, 0);
		/* Touchpoint color
		 */
		xmlTouchpointColor.set(0, 155, 255, 255);
		xmlTouchpointLines.set(0, 255, 255, 255);
		xmlTouchpointCross.set(255, 255, 255, 255);
		XML.addTag("touchpoints");
		XML.pushTag("touchpoints", 0);
		XML.addTag("pointColor");
		XML.addAttribute("pointColor", "r", xmlTouchpointColor[0], 0);
		XML.addAttribute("pointColor", "g", xmlTouchpointColor[1], 0);
		XML.addAttribute("pointColor", "b", xmlTouchpointColor[2], 0);
		XML.addAttribute("pointColor", "a", xmlTouchpointColor[3], 0);
		XML.addTag("lineColor");
		XML.addAttribute("lineColor", "r", xmlTouchpointLines[0], 0);
		XML.addAttribute("lineColor", "g", xmlTouchpointLines[1], 0);
		XML.addAttribute("lineColor", "b", xmlTouchpointLines[2], 0);
		XML.addAttribute("lineColor", "a", xmlTouchpointLines[3], 0);
		XML.addTag("crossColor");
		XML.addAttribute("crossColor", "r", xmlTouchpointCross[0], 0);
		XML.addAttribute("crossColor", "g", xmlTouchpointCross[1], 0);
		XML.addAttribute("crossColor", "b", xmlTouchpointCross[2], 0);
		XML.addAttribute("crossColor", "a", xmlTouchpointCross[3], 0);
		XML.popTag();
		/* Trackpad variables
		 */
		xmlPadDevicename = "mtpad";
		xmlPadFrame      = 1;
		xmlPadTimestamp  = 1;
		xmlPadPosition   = 1;
		xmlPadVelocity   = 1;
		xmlPadSize       = 1;
		xmlPadMaxis      = 1;
		xmlPadAngle      = 1;
		XML.addTag("pad");
		XML.pushTag("pad", 0);
		XML.addValue("devicename", xmlPadDevicename);
		XML.addValue("frame", xmlPadFrame);
		XML.addValue("timestamp", xmlPadTimestamp);
		XML.addValue("position", xmlPadPosition);
		XML.addValue("velocity", xmlPadVelocity);
		XML.addValue("size", xmlPadSize);
		XML.addValue("maxis", xmlPadMaxis);
		XML.addValue("angle", xmlPadAngle);
		XML.popTag();
	}

	/* Pop root xml tag.
	 */
	XML.popRoot();
	
	/* Set the openFrameworks app settings.
	 */
	XML.setSettings();
	ofLog() << "XML: " << XML.getStatusMessage();
	setWindowTitle();
	
	/* Log the XML parameter
	 */
	ofLog() << "XML: window mode     = " << xmlWindowMode;
	ofLog() << "XML: osc:out         = " << xmlOscOut;
	ofLog() << "XML: osc:host        = " << xmlOscHost;
	ofLog() << "XML: osc:port        = " << xmlOscPort;
	ofLog() << "XML: pad:devicename  = " << xmlPadDevicename;
	ofLog() << "XML: pad:frame       = " << xmlPadFrame;
	ofLog() << "XML: pad:timestamp   = " << xmlPadTimestamp;
	ofLog() << "XML: pad:position    = " << xmlPadPosition;
	ofLog() << "XML: pad:velocity    = " << xmlPadVelocity;
	ofLog() << "XML: pad:size        = " << xmlPadSize;
	ofLog() << "XML: pad:maxis       = " << xmlPadMaxis;
	ofLog() << "XML: pad:angle       = " << xmlPadAngle;
	ofLog() << "XML: pointColor rgba = " << xmlTouchpointColor.getClamped();
	ofLog() << "XML: lineColor rgba  = " << xmlTouchpointLines.getClamped();
	ofLog() << "XML: crossColor rgba = " << xmlTouchpointCross.getClamped();
	
	/* Save the XML file if no file existed
	 */
	if (XML.fileExist == false) {
		XML.saveFile();
	}
	
	
	/* Load the font
	 */
	//ofTrueTypeFont::setGlobalDpi(96);
	vera.loadFont(ofFilePath::getCurrentWorkingDirectory() + "/Font/Vera.ttf", 9, true, false);
	if (vera.isLoaded()) {
		ofLog() << "FONT: Is loaded";
	} else {
		ofLog() << "FONT: Not loaded";
	}

	
	/* OSC
	 * Open an outgoing connection to oscHost, oscPort
	 */
	oscSender.setup(xmlOscHost, xmlOscPort);
	ofLog() << "OSC: setup host \"" << xmlOscHost << "\", port " << "\"" << xmlOscPort << "\"";
	
	
	/* Console
	 */
	console.init(vera);
	
	
	/* GUI
	 * set the status to osc:out settings value
	 */
	gui = new ofxUICanvas();
	gui->setFont(ofFilePath::getCurrentWorkingDirectory() + "/Font/Vera.ttf"); //This loads a new font and sets the GUI font
    gui->setFontSize(OFX_UI_FONT_LARGE, 12);                                    //These call are optional, but if you want to resize the LARGE, MEDIUM, and SMALL fonts, here is how to do it. 
    gui->setFontSize(OFX_UI_FONT_MEDIUM, 8);           
    gui->setFontSize(OFX_UI_FONT_SMALL, 6);                                    //SUPER IMPORTANT NOTE: CALL THESE FUNTIONS BEFORE ADDING ANY WIDGETS, THIS AFFECTS THE SPACING OF THE GUI
	gui->addWidget(new ofxUITextInput("TEXT HOST", xmlOscHost, 130,20, 50,77, OFX_UI_FONT_SMALL));
	gui->addWidget(new ofxUITextInput("TEXT PORT", ofToString(xmlOscPort), 130,20, 50,97, OFX_UI_FONT_SMALL));
	gui->addWidget(new ofxUITextInput("TEXT DEVICENAME", ofToString(xmlPadDevicename), 150, 20, 100,113, OFX_UI_FONT_SMALL));
	ofAddListener(gui->newGUIEvent, this, &MultitouchPadOscApp::guiEvent);
	gui->setVisible(false);
	
	
	string tempGuiFilepath = ofFilePath::getCurrentWorkingDirectory() + "/gui/";
	btnOscActive.init(tempGuiFilepath+"oscactive_on.png", tempGuiFilepath+"oscactive_off.png", ofGetWidth()-56, 0);
	if (xmlOscOut == 0) {
		btnOscActive.status = true;
	} else {
		btnOscActive.status = false;
	}
	oscSendImage.loadImage(tempGuiFilepath+"oscactive_send.png");
	//btnSafetyMode.init(tempGuiFilepath+"oscactive_on.png", tempGuiFilepath+"oscactive_off.png", ofGetWidth()-56, 0);
	btnWindowMode.init(tempGuiFilepath+"oscactive_send.png", tempGuiFilepath+"oscactive_send.png", ofGetWidth()-36, 0);
	if (xmlWindowMode == true) {
		btnWindowMode.status = true;
	} else {
		btnWindowMode.status = false;
	}

	btnTouchpoints.init(tempGuiFilepath+"btn_left_on.png",  tempGuiFilepath+"btn_left_off.png", 10, 0);
	btnTouchpoints.status = true;
	btnSettings.init(tempGuiFilepath+"btn_middle_on.png", tempGuiFilepath+"btn_middle_off.png", 87, 0);
	btnConsole.init(tempGuiFilepath+ "btn_right_on.png", tempGuiFilepath+"btn_right_off.png", 164, 0);
	
	cbFrame.init(vera,      "frame active",               15, 190, xmlPadFrame);
	//cbTimestamp.init(vera,  "timestamp active",           60, 170, defXmlPadTimestamp);
	cbPosition.init(vera,   "x-, y-position active",      15, 210, xmlPadPosition);
	//cbVelocity.init(vera,   "x-, y-velocity active",      60, 200, defXmlPadVelocity);
	//cbMaxis.init(vera,      "minor-, major-axis active",  60, 215, defXmlPadMaxis);
	cbSize.init(vera,       "size active",                15, 230, xmlPadSize);
	cbAngle.init(vera,      "angle active",               15, 250, xmlPadAngle);
	
	
	/* Multitouch Trackpad
	 * Add the listeners
	 */
    ofAddListener(pad.update, this, &MultitouchPadOscApp::padUpdates);
    ofAddListener(pad.touchAdded, this, &MultitouchPadOscApp::newTouch);
    ofAddListener(pad.touchRemoved, this, &MultitouchPadOscApp::removedTouch);
	
	
	ofLog() << "Number of Devices: "<< pad.getNumDevices();
	ofLog() << "SETUP: ready";
}



void MultitouchPadOscApp::update() {
}



void MultitouchPadOscApp::draw(){
	/* background
	 */
	ofBackground(111, 112, 114);
	ofFill();
	ofSetColor(88, 88, 90);
	ofRect(10, 30, ofGetWidth()-20, ofGetHeight()-40);
	
	
	/* GUI
	 */
	ofSetColor(255);
	btnOscActive.display();
	//btnSafetyMode.display();
	btnWindowMode.display();
	btnTouchpoints.display();
	btnSettings.display();
	btnConsole.display();
	
	
	/* Draw the touch count typo
	 */
    ofSetColor(255);
	vera.drawString("Viewer", 30, 18);
	vera.drawString("Settings", 107, 18);
	vera.drawString("Console", 184, 18);
	vera.drawString("Touch Count: "+ofToString(pad.getTouchCount(), 0), 15, ofGetHeight()-15);
	
	
	/* Display finger blobs
	 * connect all touches with a line
	 */
    std::vector<ofPoint>touches;
    pad.getTouchesAsOfPoints(&touches);
	
	ofEnableSmoothing();
    for(int i=0; (i<touches.size()-1 && touches.size()>1); i++) {
        ofSetColor(xmlTouchpointLines);
        int x1 = ofMap(touches.at(i).x,   0.0, 1.0, 30, ofGetWidth()-30);
		int y1 = ofMap(touches.at(i).y,   0.0, 1.0, 70, ofGetHeight()-30);
		int x2 = ofMap(touches.at(i+1).x, 0.0, 1.0, 30, ofGetWidth()-30);
		int y2 = ofMap(touches.at(i+1).y, 0.0, 1.0, 70, ofGetHeight()-30);
		ofLine(x1, y1, x2, y2);
    }
	ofDisableSmoothing();
    
	
	/* display all finger blobs
	 */
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
		ofSetColor(xmlTouchpointColor);
		ofFill();
		ofEllipse(0, 0, size, size*0.625);
		
		// cross at the circle center
		ofSetColor(xmlTouchpointCross);
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
		
		
		
		/* OSC
		 */
		if(xmlOscOut == 0) {
			// if osc message will be send,
			// show osc send icon.
			ofSetColor(255);
			ofFill();
			oscSendImage.draw(ofGetWidth()-36, 0);
		
			
			// Check if padFrame is active
			if (xmlPadFrame == 0) {
				// Send osc message, integer value with the current frame.
				// e.g. /mt/1/frame/23
				string sFrame = ofToString("/") + ofToString(xmlPadDevicename) + ofToString("/") + ofToString(i) + "/frame";
				
				intMessage(sFrame, touch.frame);
				
				console.addString(ofToString("OSC ") + ofToString(sFrame) + ofToString("/") + ofToString(touch.frame));
			}
			 
			// check if padTimestamp is active
			/*if (settings.padTimestamp == 0) {
				Finger finger;
				cout << "padTimestamp " << finger.timestamp << endl;
			}*/
			 
			// check if padPosition is active
			if (xmlPadPosition == 0) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/x/0.5
				string sX = ofToString("/") + ofToString(xmlPadDevicename) + ofToString("/") + ofToString(i) + "/x";
				string sY = ofToString("/") + ofToString(xmlPadDevicename) + ofToString("/") + ofToString(i) + "/y";
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
			if (xmlPadSize == 0) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/size/0.5
				string sSize = ofToString("/") + ofToString(xmlPadDevicename) + ofToString("/") + ofToString(i) + "/size";
				floatMessage(sSize, touch.size);
				console.addString(ofToString("OSC ") + ofToString(sSize) + ofToString("/") + ofToString(touch.size));
			}
			 
			// check if padAngle is active
			if (xmlPadAngle == 0) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/angle/0.5
				string sAngle = ofToString("/") + ofToString(xmlPadDevicename) + ofToString("/") + ofToString(i) + "/angle";
				floatMessage(sAngle, touch.angle);
				console.addString(ofToString("OSC ") + ofToString(sAngle) + ofToString("/") + ofToString(touch.angle));
			}
		}
    }
	
	
	/* settings button
	 */
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
		vera.drawString("Host: ", 15, 90);
		vera.drawString("Port: ", 15, 110);
		vera.drawString("Devicename: ", 15, 130);
		vera.drawString("[To open the settings xml, press key 's']", 167, 150);
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
	
	/* console button
	 */
	if(btnConsole.status == true) {
		// ground
		ofEnableAlphaBlending();
		ofSetColor(0, 150);
		ofFill();
		ofRect(10, 30, ofGetWidth()-20, ofGetHeight()-40);
		ofDisableAlphaBlending();
		
		// headline text
		ofSetColor(ofColor::white);
		vera.drawString("Sended osc messages:", 15, 50);
		console.display(15, 90);
	}
}



void MultitouchPadOscApp::exit() {
	/* XML file
	 */
	XML.pushRoot();
	XML.setAttribute(XML.CORE+":window", "mode", xmlWindowMode, 0);
	XML.setValue("osc", xmlOscOut, 0);
	XML.setAttribute("osc", "host", xmlOscHost, 0);
	XML.setAttribute("osc", "port", xmlOscPort, 0);
	XML.setValue("pad:devicename", xmlPadDevicename, 0);
	XML.setValue("pad:frame", xmlPadFrame, 0);
	XML.setValue("pad:timestamp", xmlPadTimestamp, 0);
	XML.setValue("pad:position", xmlPadPosition, 0);
	XML.setValue("pad:velocity", xmlPadVelocity, 0);
	XML.setValue("pad:size", xmlPadSize, 0);
	XML.setValue("pad:maxis", xmlPadMaxis, 0);
	XML.setValue("pad:angle", xmlPadAngle, 0);
	XML.popRoot();
	
	/* Save the current settings to xml.
	 */
	XML.save();
	
	/* GUI
	 */
	delete gui;
}



void MultitouchPadOscApp::keyPressed(int key) {
	/* Open the settings xml file
	 */
	if(key == 's') {
		string commandStr = "open " + ofFilePath::getCurrentWorkingDirectory() + "/ofSettings.xml";
		system(commandStr.c_str());
		
		console.addString("Open XML settings file.");
	}
	
	switch(key) {
		/* Shortcuts to select the toolbar buttons.
		 */
		case '1':
			btnTouchpoints.status = true;
			btnSettings.status = false;
			btnConsole.status = false;
			break;
		case '2':
			btnTouchpoints.status = false;
			btnSettings.status = true;
			btnConsole.status = false;
			break;
		case '3':
			btnTouchpoints.status = false;
			btnSettings.status = false;
			btnConsole.status = true;
			break;

		/* OSC out
		 */
		case 'q':
			if (xmlOscOut == 0) {
				xmlOscOut = 1;
				btnOscActive.status = !btnOscActive.status;
			} else {
				xmlOscOut = 0;
				btnOscActive.status = !btnOscActive.status;
			}
			console.addString("Shortcut oscOut: " + ofToString(xmlOscOut), true);
			break;
		
		/* OSC frame
		 */
		case 'w':
			if (xmlPadFrame == 0) {
				xmlPadFrame = 1;
			} else {
				xmlPadFrame = 0;
			}
			cbFrame.status = xmlPadFrame;
			console.addString("Shortcut padFrame: " + ofToString(xmlPadFrame), true);
			break;
		
		/* OSC timestamp
		 */
		/*case '3':
			if (settings.padTimestamp == 0) {
				settings.padTimestamp = 1;
			} else {
				settings.padTimestamp = 0;
			}
			cbTimestamp.status = settings.padTimestamp;
			
			cout << "Shortcut padTimestamp: " << settings.padTimestamp << endl;
			break;*/
		
		/* OSC position
		 */
		case 'e':
			if (xmlPadPosition == 0) {
				xmlPadPosition = 1;
			} else {
				xmlPadPosition = 0;
			}
			cbPosition.status = xmlPadPosition;
			console.addString("Shortcut padPosition: " + ofToString(xmlPadPosition), true);
			break;

		/* OSC velocity
		 */
		/*case '5':
			if (settings.padVelocity == 0) {
				settings.padVelocity = 1;
			} else {
				settings.padVelocity = 0;
			}
			cbVelocity.status = settings.padVelocity;
			
			cout << "Shortcut padVelocity: " << settings.padVelocity << endl;
			break;*/

		/* OSC maxis
		 */
		/*case '4':
			if (settings.padMaxis == 0) {
				settings.padMaxis = 1;
			} else {
				settings.padMaxis = 0;
			}
			cbMaxis.status = settings.padMaxis;
			
			cout << "Shortcut padMaxis: " << settings.padMaxis << endl;
			break;*/

		/* OSC maxis
		 */
		case 'r':
			if (xmlPadSize == 0) {
				xmlPadSize = 1;
			} else {
				xmlPadSize = 0;
			}
			cbSize.status = xmlPadSize;
			console.addString("Shortcut padSize: " + ofToString(xmlPadSize), true);
			break;

		/* OSC angle
		 */
		case 't':
			if (xmlPadAngle == 0) {
				xmlPadAngle = 1;
			} else {
				xmlPadAngle = 0;
			}
			cbAngle.status = xmlPadAngle;
			console.addString("Shortcut padAngle: " + ofToString(xmlPadAngle), true);
			break;

		default:
			break;
	}
}



void MultitouchPadOscApp::keyReleased(int key) {
}



void MultitouchPadOscApp::mouseMoved(int x, int y) {
}



void MultitouchPadOscApp::mouseDragged(int x, int y, int button) {
}



void MultitouchPadOscApp::mousePressed(int x, int y, int button) {
	/* GUI
	 */
	btnOscActive.pressed(x, y);
	if (btnOscActive.status == true) {
		xmlOscOut = 0;
	} else {
		xmlOscOut = 1;
	}
	
	/*btnSafetyMode.pressed(x, y);
	if (btnSafetyMode.status == true) {
		cout << "### safety mode active" << endl;
		ofSetFullscreen(true);
	} else {
		cout << "### safety mode not active" << endl;
		ofSetFullscreen(false);
	}*/
	
	btnWindowMode.pressed(x, y);
	if (btnWindowMode.status == true) {
		ofSetWindowShape(400, 100);
	} else {
		XML.setWindowShape();
	}

	
	if (btnTouchpoints.status == false) {
		btnTouchpoints.pressed(x, y);
	}
	if (btnTouchpoints.status == true) {
		/* hide settings, settings panel
		 */
		btnSettings.status = false;
		btnConsole.status = false;
		/* hide GUI textfield
		 */
		gui->setVisible(false);
	}
	
	/* Settings button
	 */
	if (btnSettings.status == false) {
		btnSettings.pressed(x, y);
	}
	if (btnSettings.status == true) {
		/* hide touchpoint, console panel
		 */
		btnTouchpoints.status = false;
		btnConsole.status = false;
		/* Check boxes
		 */
		cbFrame.pressed(x, y);
		xmlPadFrame = cbFrame.status;
		//cbTimestamp.pressed(x, y);
		//settings.padTimestamp = cbTimestamp.status;
		cbPosition.pressed(x, y);
		xmlPadPosition = cbPosition.status;
		//cbVelocity.pressed(x, y);
		//settings.padVelocity = cbVelocity.status;
		//cbMaxis.pressed(x, y);
		//settings.padMaxis = cbMaxis.status;
		cbSize.pressed(x, y);
		xmlPadSize = cbSize.status;
		cbAngle.pressed(x, y);
		xmlPadAngle = cbAngle.status;
		/* show GUI textfield
		 */
		gui->setVisible(true);
	}
	
	/* Console button
	 */
	if (btnConsole.status == false) {
		btnConsole.pressed(x, y);
	}
	if (btnConsole.status == true) {
		/* hide touchpoint, settings panel
		 */
		btnTouchpoints.status = false;
		btnSettings.status = false;
		/* hide GUI textfield
		 */
		gui->setVisible(false);
	}
}



void MultitouchPadOscApp::mouseReleased(int x, int y, int button) {
}



void MultitouchPadOscApp::windowResized(int w, int h) {
	/* GUI
	 */
	btnOscActive.setPosition(w-56, 0);
	//btnSafetyMode.setPosition(w-66, 0);
	btnWindowMode.setPosition(w-36, 0);
}



void MultitouchPadOscApp::gotMessage(ofMessage msg) {
}



void MultitouchPadOscApp::dragEvent(ofDragInfo dragInfo) {
}



void MultitouchPadOscApp::padUpdates(int & t) {
	printf("pad updates & has %i touches\n",t);
}



void MultitouchPadOscApp::newTouch(int & n) {
    //printf("+ a new touch\n", n);
	
	/* Send an osc message if the touchpoint is added.
	 */
	ofxOscMessage m;
	m.setAddress("/" + xmlPadDevicename + "/" + ofToString(n) + "/added");
	oscSender.sendMessage(m);
}



void MultitouchPadOscApp::removedTouch(int & r) {
    //printf("- a removed touch\n",r);
	
	/* Send an osc message if the touchpoint is removed.
	 */
	ofxOscMessage m;
	m.setAddress("/" + xmlPadDevicename + "/" + ofToString(r) + "/removed");
	oscSender.sendMessage(m);
}



void MultitouchPadOscApp::intMessage(string s, int val) {
	ofxOscMessage m;
	m.setAddress(s);
	m.addIntArg(val);
	oscSender.sendMessage(m);
}



void MultitouchPadOscApp::floatMessage(string s, float val) {
	ofxOscMessage m;
	m.setAddress(s);
	m.addFloatArg(val);
	oscSender.sendMessage(m);
}



void MultitouchPadOscApp::guiEvent(ofxUIEventArgs &e) {
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
	if (name == "TEXT HOST") {
		ofxUITextInput *textInput = (ofxUITextInput *) e.widget;
		xmlOscHost = textInput->getTextString();
		oscSender.setup(xmlOscHost, xmlOscPort);
		setWindowTitle();
		console.addString("Change host to " + textInput->getTextString(), true);
	}
	else if (name == "TEXT PORT") {
		ofxUITextInput *textInput = (ofxUITextInput *) e.widget;
		xmlOscPort = ofToInt(textInput->getTextString());
		oscSender.setup(xmlOscHost, xmlOscPort);
		setWindowTitle();
		console.addString("Change port to " + textInput->getTextString(), true);
	}
	else if (name == "TEXT DEVICENAME") {
		ofxUITextInput *textInput = (ofxUITextInput *) e.widget;
		xmlPadDevicename = textInput->getTextString();
		console.addString("Change devicename to " + textInput->getTextString(), true);
	}
}



void MultitouchPadOscApp::setWindowTitle(){
	ofSetWindowTitle(ofToString(PROJECTNAME) + " - Host: " + xmlOscHost + " Port: " + ofToString(xmlOscPort));
}