/*
 *  ToolbarMVC.cpp
 *  MultitouchPadOsc
 *
 *  Created by Paul Vollmer on 16.10.12.
 *  Copyright 2012 Wrong-Entertainment. All rights reserved.
 *
 */

#include "ToolbarMVC.h"

ToolbarMVC::ToolbarMVC(){}

void ToolbarMVC::init() {
	string tempGuiFilepath = ofFilePath::getCurrentWorkingDirectory()+"/gui/";
	buttonOscActive.init(tempGuiFilepath+"oscactive_on.png", tempGuiFilepath+"oscactive_off.png", ofGetWidth()-56, 0);
	oscSendImage.loadImage(tempGuiFilepath+"oscactive_send.png");
	buttonWindowMode.init(tempGuiFilepath+"oscactive_send.png", tempGuiFilepath+"oscactive_send.png", ofGetWidth()-36, 0);
	//btnSafetyMode.init(tempGuiFilepath+"oscactive_on.png", tempGuiFilepath+"oscactive_off.png", ofGetWidth()-56, 0);
	buttonTouchpoints.init(tempGuiFilepath+"btn_left_on.png",  tempGuiFilepath+"btn_left_off.png", 10, 0);
	buttonTouchpoints.status = true;
	buttonSettings.init(tempGuiFilepath+"btn_middle_on.png", tempGuiFilepath+"btn_middle_off.png", 87, 0);
	buttonConsole.init(tempGuiFilepath+"btn_right_on.png", tempGuiFilepath+"btn_right_off.png", 164, 0);
}


void ToolbarMVC::getXml(ofxXmlDefaultSettings xml) {
	/* Other Application Core Settings
	 */
	buttonWindowMode.status = xml.getAttribute(xml.getSyntax(xml.CORE)+":window", "mode", false, 0);
	buttonOscActive.status = xml.getValue("osc", false, 0);
}


void ToolbarMVC::addXml(ofxXmlDefaultSettings xml) {
	buttonWindowMode.status = false;
	xml.addAttribute(xml.getSyntax(xml.CORE)+":window", "mode", buttonWindowMode.status, 0);
	buttonOscActive.status = false;
	xml.addValue("osc", buttonOscActive.status);
}

void ToolbarMVC::setXml(ofxXmlDefaultSettings xml) {
	xml.pushRoot();
	xml.setAttribute(xml.getSyntax(xml.CORE)+":window", "mode", buttonWindowMode.status, 0);
	xml.setValue("osc", buttonOscActive.status, 0);
	xml.popRoot();
}


void ToolbarMVC::log() {
	ofLog() << "XML: window mode     = " << buttonWindowMode.status;
	ofLog() << "XML: osc:out         = " << buttonOscActive.status;
}


void ToolbarMVC::draw() {
	/* GUI
	 */
	ofSetColor(255);
	buttonOscActive.display();
	//btnSafetyMode.display();
	buttonWindowMode.display();
	buttonTouchpoints.display();
	buttonSettings.display();
	buttonConsole.display();
	
	/* OSC
	 */
	if(buttonOscActive.status == 0) {
		// if osc message will be send,
		// show osc send icon.
		ofSetColor(255);
		ofFill();
		oscSendImage.draw(ofGetWidth()-56, 0);
	}
}


void ToolbarMVC::windowResized(int w, int h) {
	/* GUI
	 */
	buttonOscActive.setPosition(w-56, 0);
	buttonWindowMode.setPosition(w-36, 0);
	//btnSafetyMode.setPosition(w-66, 0);
}


void ToolbarMVC::mousePressed(int x, int y) {
	/* GUI
	 */
	buttonOscActive.pressed(x, y);
	buttonWindowMode.pressed(x, y);
	/*btnSafetyMode.pressed(x, y);
	 if (btnSafetyMode.status == true) {
	 cout << "### safety mode active" << endl;
	 ofSetFullscreen(true);
	 } else {
	 cout << "### safety mode not active" << endl;
	 ofSetFullscreen(false);
	 }*/
}


void ToolbarMVC::keyPressed(int key) {
	switch (key) {
		/* Shortcuts to select the toolbar buttons.
		 */
		case '1':
			buttonTouchpoints.status = true;
			buttonSettings.status = false;
			buttonConsole.status = false;
			break;
		case '2':
			buttonTouchpoints.status = false;
			buttonSettings.status = true;
			buttonConsole.status = false;
			break;
		case '3':
			buttonTouchpoints.status = false;
			buttonSettings.status = false;
			buttonConsole.status = true;
			break;
			
		/* OSC out
		 */
		case 'o':
			if (buttonOscActive.status == true) {
				buttonOscActive.status = false;
			} else {
				buttonOscActive.status = true;
			}
			//console.addString("Shortcut oscOut: " + ofToString(btnOscActive.status), true);
			break;
		
		/* Window mode
		 */
		case 'l':
			if (buttonWindowMode.status == true) {
				buttonWindowMode.status = false;
				ofSetWindowShape(ofGetWidth(), 400);
				buttonWindowMode.setPosition(ofGetWidth()-36, 0);
			} else {
				buttonWindowMode.status = true;
				ofSetWindowShape(ofGetWidth(), 40);
				buttonWindowMode.setPosition(ofGetWidth()-36, 0);
			}
			break;
	
		default:
			break;
	}
}
