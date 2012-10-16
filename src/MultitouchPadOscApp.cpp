//
// MultitouchPadOscApp.cpp
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
	
	/* Load the font
	 */
	//ofTrueTypeFont::setGlobalDpi(96);
	vera.loadFont(ofFilePath::getCurrentWorkingDirectory() + "/Font/Vera.ttf", 9, true, false);
	if (vera.isLoaded()) {
		ofLog() << "FONT: Is loaded";
	} else {
		ofLog() << "FONT: Not loaded";
	}
	
	/* Settings Viewer
	 */
	toolbarMVC.init();
	settingsMVC.init(vera);
	
	
	
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
		
		toolbarMVC.getXml(XML);
		settingsMVC.getXml(XML);
	}
	/* If no xml file exist, create the <balls> tag and add some parameter.
	 */
	else {
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
		
		toolbarMVC.addXml(XML);
		settingsMVC.addXml(XML);
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
	ofLog() << "XML: pointColor rgba = " << xmlTouchpointColor.getClamped();
	ofLog() << "XML: lineColor rgba  = " << xmlTouchpointLines.getClamped();
	ofLog() << "XML: crossColor rgba = " << xmlTouchpointCross.getClamped();
	toolbarMVC.log();
	settingsMVC.logCheckboxStatus();
	
	/* Save the XML file if no file existed
	 */
	if (XML.fileExist == false) {
		XML.saveFile();
	}
	
	
	/* OSC
	 * Open an outgoing connection to oscHost, oscPort
	 */
	oscSender.setup(settingsMVC.oscHost, settingsMVC.oscPort);
	ofLog() << "OSC: setup host \"" << settingsMVC.oscHost << "\", port " << "\"" << settingsMVC.oscPort << "\"";
	
	
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
	gui->addWidget(new ofxUITextInput("TEXT HOST", settingsMVC.oscHost, 130,20, 50,77, OFX_UI_FONT_SMALL));
	gui->addWidget(new ofxUITextInput("TEXT PORT", ofToString(settingsMVC.oscPort), 130,20, 50,97, OFX_UI_FONT_SMALL));
	gui->addWidget(new ofxUITextInput("TEXT DEVICENAME", ofToString(settingsMVC.oscTouchpadDevicename), 150, 20, 100,113, OFX_UI_FONT_SMALL));
	ofAddListener(gui->newGUIEvent, this, &MultitouchPadOscApp::guiEvent);
	gui->setVisible(false);
	
	
		
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
	
	
	toolbarMVC.draw();
	
	
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
		if(toolbarMVC.buttonOscActive.status == true) {
		
			
			// Check if padFrame is active
			if (settingsMVC.checkboxFrame.status == true) {
				// Send osc message, integer value with the current frame.
				// e.g. /mt/1/frame/23
				string sFrame = ofToString("/") + ofToString(settingsMVC.oscTouchpadDevicename) + ofToString("/") + ofToString(i) + "/frame";
				
				oscIntMessage(sFrame, touch.frame);
				
				console.addString(ofToString("OSC ") + ofToString(sFrame) + ofToString("/") + ofToString(touch.frame));
			}
			 
			// check if padTimestamp is active
			/*if (settings.padTimestamp == 0) {
				Finger finger;
				cout << "padTimestamp " << finger.timestamp << endl;
			}*/
			 
			// check if padPosition is active
			if (settingsMVC.checkboxPosition.status == true) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/x/0.5
				string sX = ofToString("/") + ofToString(settingsMVC.oscTouchpadDevicename) + ofToString("/") + ofToString(i) + "/x";
				string sY = ofToString("/") + ofToString(settingsMVC.oscTouchpadDevicename) + ofToString("/") + ofToString(i) + "/y";
				oscFloatMessage(sX, touch.x);
				oscFloatMessage(sY, touch.y);
				console.addString(ofToString("OSC ") + ofToString(sX) + ofToString("/") + ofToString(touch.x));
				console.addString(ofToString("OSC ") + ofToString(sY) + ofToString("/") + ofToString(touch.y));
			}
			 
			// check if padVelocity is active
			/*if (settings.padVelocity == 0) {
				Finger finger;
				cout << "padVelocity " << finger.mm.vel.x << endl;
			}*/
			 
			// check if padSize is active
			if (settingsMVC.checkboxSize.status == true) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/size/0.5
				string sSize = ofToString("/") + ofToString(settingsMVC.oscTouchpadDevicename) + ofToString("/") + ofToString(i) + "/size";
				oscFloatMessage(sSize, touch.size);
				console.addString(ofToString("OSC ") + ofToString(sSize) + ofToString("/") + ofToString(touch.size));
			}
			 
			// check if padAngle is active
			if (settingsMVC.checkboxAngle.status == true) {
				// Send osc message, float value between 0 and 1.
				// e.g. /mt/1/angle/0.5
				string sAngle = ofToString("/") + ofToString(settingsMVC.oscTouchpadDevicename) + ofToString("/") + ofToString(i) + "/angle";
				oscFloatMessage(sAngle, touch.angle);
				console.addString(ofToString("OSC ") + ofToString(sAngle) + ofToString("/") + ofToString(touch.angle));
			}
		}
    }
	
	
	/* settings button
	 */
	if(toolbarMVC.buttonSettings.status == true) {
		/* Settings Viewer
		 */
		settingsMVC.draw(vera);
	}
	
	/* console button
	 */
	if(toolbarMVC.buttonConsole.status == true) {
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
	XML.setAttribute("osc", "host", settingsMVC.oscHost, 0);
	XML.setAttribute("osc", "port", settingsMVC.oscPort, 0);
	settingsMVC.setXml(XML);
	XML.popRoot();
	
	
	toolbarMVC.setXml(XML);
	
	
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
	
	toolbarMVC.keyPressed(key);
	settingsMVC.keyPressed(key);
}



void MultitouchPadOscApp::keyReleased(int key) {
}



void MultitouchPadOscApp::mouseMoved(int x, int y) {
}



void MultitouchPadOscApp::mouseDragged(int x, int y, int button) {
}



void MultitouchPadOscApp::mousePressed(int x, int y, int button) {
	
	
	toolbarMVC.mousePressed(x, y);
	
	
	if (toolbarMVC.buttonTouchpoints.status == false) {
		toolbarMVC.buttonTouchpoints.pressed(x, y);
	}
	if (toolbarMVC.buttonTouchpoints.status == true) {
		/* hide settings, settings panel
		 */
		toolbarMVC.buttonSettings.status = false;
		toolbarMVC.buttonConsole.status = false;
		/* hide GUI textfield
		 */
		gui->setVisible(false);
	}
	
	/* Settings button
	 */
	if (toolbarMVC.buttonSettings.status == false) {
		toolbarMVC.buttonSettings.pressed(x, y);
	}
	if (toolbarMVC.buttonSettings.status == true) {
		/* hide touchpoint, console panel
		 */
		toolbarMVC.buttonTouchpoints.status = false;
		toolbarMVC.buttonConsole.status = false;
		
		settingsMVC.mousePressed(x, y);
		
		/* show GUI textfield
		 */
		gui->setVisible(true);
	}
	
	/* Console button
	 */
	if (toolbarMVC.buttonConsole.status == false) {
		toolbarMVC.buttonConsole.pressed(x, y);
	}
	if (toolbarMVC.buttonConsole.status == true) {
		/* hide touchpoint, settings panel
		 */
		toolbarMVC.buttonTouchpoints.status = false;
		toolbarMVC.buttonSettings.status = false;
		/* hide GUI textfield
		 */
		gui->setVisible(false);
	}
}



void MultitouchPadOscApp::mouseReleased(int x, int y, int button) {
}



void MultitouchPadOscApp::windowResized(int w, int h) {
	toolbarMVC.windowResized(w, h);
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
	m.setAddress("/" + settingsMVC.oscTouchpadDevicename + "/" + ofToString(n) + "/added");
	oscSender.sendMessage(m);
}



void MultitouchPadOscApp::removedTouch(int & r) {
    //printf("- a removed touch\n",r);
	
	/* Send an osc message if the touchpoint is removed.
	 */
	ofxOscMessage m;
	m.setAddress("/" + settingsMVC.oscTouchpadDevicename + "/" + ofToString(r) + "/removed");
	oscSender.sendMessage(m);
}



void MultitouchPadOscApp::guiEvent(ofxUIEventArgs &e) {
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
	if (name == "TEXT HOST") {
		ofxUITextInput *textInput = (ofxUITextInput *) e.widget;
		settingsMVC.oscHost = textInput->getTextString();
		oscSender.setup(settingsMVC.oscHost, settingsMVC.oscPort);
		setWindowTitle();
		console.addString("Change host to " + textInput->getTextString(), true);
	}
	else if (name == "TEXT PORT") {
		ofxUITextInput *textInput = (ofxUITextInput *) e.widget;
		settingsMVC.oscPort = ofToInt(textInput->getTextString());
		oscSender.setup(settingsMVC.oscHost, settingsMVC.oscPort);
		setWindowTitle();
		console.addString("Change port to " + textInput->getTextString(), true);
	}
	else if (name == "TEXT DEVICENAME") {
		ofxUITextInput *textInput = (ofxUITextInput *) e.widget;
		settingsMVC.oscTouchpadDevicename = textInput->getTextString();
		console.addString("Change devicename to " + textInput->getTextString(), true);
	}
}



void MultitouchPadOscApp::setWindowTitle(){
	ofSetWindowTitle(ofToString(PROJECTNAME) + " - Host: " + settingsMVC.oscHost + " Port: " + ofToString(settingsMVC.oscPort));
}



void MultitouchPadOscApp::oscIntMessage(string s, int val) {
	ofxOscMessage m;
	m.setAddress(s);
	m.addIntArg(val);
	oscSender.sendMessage(m);
}



void MultitouchPadOscApp::oscFloatMessage(string s, float val) {
	ofxOscMessage m;
	m.setAddress(s);
	m.addFloatArg(val);
	oscSender.sendMessage(m);
}
