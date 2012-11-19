//
// ToolbarMVC.cpp
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

#include "ToolbarMVC.h"


ToolbarMVC::ToolbarMVC(){}


void ToolbarMVC::init() {
	string tempGuiFilepath = ofFilePath::getCurrentWorkingDirectory()+"/gui/";
	buttonOscActive.init(tempGuiFilepath+"oscactive_on.png", tempGuiFilepath+"oscactive_off.png", ofGetWidth()-OSC_ACTIVE_X, 0);
	oscSendImage.loadImage(tempGuiFilepath+"oscactive_send.png");
	buttonWindowMode.init(tempGuiFilepath+"window_mode_on.png", tempGuiFilepath+"window_mode_off.png", ofGetWidth()-WINDOW_MODE_IMAGE_WIDTH, 0);
	//btnSafetyMode.init(tempGuiFilepath+"oscactive_on.png", tempGuiFilepath+"oscactive_off.png", ofGetWidth()-56, 0);
	buttonTouchpoints.init(tempGuiFilepath+"btn_left_on.png",  tempGuiFilepath+"btn_left_off.png", 10, 0);
	buttonTouchpoints.status = true;
	buttonSettings.init(tempGuiFilepath+"btn_middle_on.png", tempGuiFilepath+"btn_middle_off.png", 81, 0);
	buttonConsole.init(tempGuiFilepath+"btn_right_on.png", tempGuiFilepath+"btn_right_off.png", 159, 0);
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
	buttonOscActive.status = true;
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


void ToolbarMVC::draw(ofTrueTypeFont font, bool oscIsSending) {
	/* GUI
	 */
	ofSetColor(255);
	buttonOscActive.display();
	// TODO:
	//btnSafetyMode.display();
	buttonTouchpoints.display();
	buttonSettings.display();
	buttonConsole.display();
	
	/* If osc message will be send, show osc send icon.
	 */
	if(oscIsSending == true) {
		ofSetColor(255);
		ofFill();
		oscSendImage.draw(ofGetWidth()-OSC_ACTIVE_X, 0);
	}
}


void ToolbarMVC::windowResized(int w, int h) {
	/* GUI
	 */
	buttonOscActive.setPosition(w-OSC_ACTIVE_X, 0);
	buttonWindowMode.setPosition(w-WINDOW_MODE_IMAGE_WIDTH, 0);
	// TODO:
	//btnSafetyMode.setPosition(w-66, 0);
}


void ToolbarMVC::mousePressed(int x, int y) {
	/* GUI
	 */
	buttonOscActive.pressed(x, y);
	
	buttonWindowMode.pressed(x, y);
	if (buttonWindowMode.status == true) {
		ofSetWindowShape(ofGetWidth(), WINDOW_MODE_MIN_HEIGHT);
		buttonWindowMode.setPosition(ofGetWidth()-WINDOW_MODE_IMAGE_WIDTH, 0);
	} else if (buttonWindowMode.status == false) {
		ofSetWindowShape(ofGetWidth(), 400);
		buttonWindowMode.setPosition(ofGetWidth()-WINDOW_MODE_IMAGE_WIDTH, 0);
	}
	
	// TODO:
	/*btnSafetyMode.pressed(x, y);
	 if (btnSafetyMode.status == true) {
	 cout << "### safety mode active" << endl;
	 ofSetFullscreen(true);
	 } else {
	 cout << "### safety mode not active" << endl;
	 ofSetFullscreen(false);
	 }*/
	
	/* Touchpoint button
	 */
	if (buttonTouchpoints.status == false) {
		buttonTouchpoints.pressed(x, y);
	}
	if (buttonTouchpoints.status == true) {
		/* hide settings, settings panel
		 */
		buttonSettings.status = false;
		buttonConsole.status = false;
	}
	
	/* Settings button
	 */
	if (buttonSettings.status == false) {
		buttonSettings.pressed(x, y);
	}
	if (buttonSettings.status == true) {
		/* hide touchpoint, console panel
		 */
		buttonTouchpoints.status = false;
		buttonConsole.status = false;
	}
	
	/* Console button
	 */
	if (buttonConsole.status == false) {
		buttonConsole.pressed(x, y);
	}
	if (buttonConsole.status == true) {
		/* hide touchpoint, settings panel
		 */
		buttonTouchpoints.status = false;
		buttonSettings.status = false;
	}
}


void ToolbarMVC::keyPressed(int key, bool cmdKeyPressed) {
	if (cmdKeyPressed == true) {
	
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
				// TODO:
				//console.addString("Shortcut oscOut: " + ofToString(btnOscActive.status), true);
				break;
				
				/* Window mode
				 */
			case 'p':
				if (buttonWindowMode.status == true) {
					buttonWindowMode.status = false;
					ofSetWindowShape(ofGetWidth(), 400);
					buttonWindowMode.setPosition(ofGetWidth()-WINDOW_MODE_IMAGE_WIDTH, 0);
				} else {
					buttonWindowMode.status = true;
					ofSetWindowShape(ofGetWidth(), WINDOW_MODE_MIN_HEIGHT);
					buttonWindowMode.setPosition(ofGetWidth()-WINDOW_MODE_IMAGE_WIDTH, 0);
				}
				break;
				
			default:
				break;
		}
		
	} // End if cmdKeyPressed
}
