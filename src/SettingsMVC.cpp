//
// SettingsMVC.cpp
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

#include "SettingsMVC.h"


SettingsMVC::SettingsMVC(){}


void SettingsMVC::init(ofTrueTypeFont font) {
	cout << "ViewerSettings init()";
	
	checkboxOscArray.init(font, "osc array xysa", 15, 170);
	checkboxFrame.init(font, "frame active", 15, 190);
	//checkboxTimestamp.init(vera, "timestamp active",  60, 170, defXmlPadTimestamp);
	checkboxPosition.init(font, "x-, y-position active", 15, 210);
	//checkboxVelocity.init(vera, "x-, y-velocity active", 60, 200, defXmlPadVelocity);
	//checkboxMaxis.init(vera, "minor-, major-axis active", 60, 215, defXmlPadMaxis);
	checkboxSize.init(font, "size active", 15, 230);
	checkboxAngle.init(font, "angle active", 15, 250);
}


void SettingsMVC::getXml(ofxXmlDefaultSettings xml) {
	/* OSC variables
	 */
	oscHost = xml.getAttribute("osc", "host", "127.0.0.1", 0);
	oscPort = xml.getAttribute("osc", "port", 12345, 0);
	
	/* Trackpad variables
	 */
	oscTouchpadDevicename = xml.getValue("pad:devicename", "mtpadosc");
	checkboxOscArray.status  = xml.getValue("pad:array", false, 0);
	//oscArrayActive = xml.getValue("pad:array", false, 0);
	checkboxFrame.status = xml.getValue("pad:frame", false, 0);
	//checkboxTimestamp.status = xml.getValue("pad:timestamp", false, 0);
	checkboxPosition.status = xml.getValue("pad:position", false, 0);
	//checkboxVelocity.status = xml.getValue("pad:velocity", false, 0);
	checkboxSize.status = xml.getValue("pad:size", false, 0);
	//checkboxMaxis.status = xml.getValue("pad:maxis", false, 0);
	checkboxAngle.status = xml.getValue("pad:angle", false, 0);
}


void SettingsMVC::addXml(ofxXmlDefaultSettings xml) {
	/* OSC variables
	 */
	oscHost = "127.0.0.1";
	oscPort = 12345;
	xml.addAttribute("osc", "host", oscHost, 0);
	xml.addAttribute("osc", "post", oscPort, 0);
	
	/* Trackpad variables
	 */
	oscTouchpadDevicename = "mtpad";
	
 	checkboxOscArray.status = false;
	checkboxFrame.status = false;
	//checkboxTimestamp.status = false;
	checkboxPosition.status = false;
	//checkboxVelocity.status = false;
	checkboxSize.status = false;
	//checkboxMaxis.status = false;
	checkboxAngle.status = false;
	xml.addTag("pad");
	xml.pushTag("pad", 0);
	xml.addValue("devicename", oscTouchpadDevicename);
	xml.addValue("array", checkboxOscArray.status);
	xml.addValue("frame", checkboxFrame.status);
	//xml.addValue("timestamp", checkboxTimestamp.status);
	xml.addValue("position", checkboxPosition.status);
	//xml.addValue("velocity", checkboxVelocity.status);
	xml.addValue("size", checkboxSize.status);
	//xml.addValue("maxis", checkboxMaxis.status);
	xml.addValue("angle", checkboxAngle.status);
	xml.popTag();
}


void SettingsMVC::setXml(ofxXmlDefaultSettings xml) {
	xml.setValue("pad:devicename", oscTouchpadDevicename, 0);
	
	xml.setValue("pad:array", checkboxOscArray.status, 0);
	xml.setValue("pad:frame", checkboxFrame.status, 0);
	//xml.setValue("pad:timestamp", checkboxTimestamp.status, 0);
	xml.setValue("pad:position", checkboxPosition.status, 0);
	//xml.setValue("pad:velocity", checkboxVelocity.status, 0);
	xml.setValue("pad:size", checkboxSize.status, 0);
	//xml.setValue("pad:maxis", checkboxMaxis.status, 0);
	xml.setValue("pad:angle", checkboxAngle.status, 0);
}


void SettingsMVC::log(){
	ofLog() << "XML: osc:host        = " << oscHost;
	ofLog() << "XML: osc:port        = " << oscPort;
	
	ofLog() << "pad:devicename  = " << oscTouchpadDevicename;
	ofLog() << "pad:array       = " << checkboxOscArray.status;
	ofLog() << "pad:frame       = " << checkboxFrame.status;
	//ofLog() << "pad:timestamp   = " << checkboxTimestamp.status;
	ofLog() << "pad:position    = " << checkboxPosition.status;
	//ofLog() << "pad:velocity    = " << checkboxVelocity.status;
	ofLog() << "pad:size        = " << checkboxSize.status;
	//ofLog() << "pad:maxis       = " << checkboxMaxis.status;
	ofLog() << "pad:angle       = " << checkboxAngle.status;
}
	

void SettingsMVC::draw(ofTrueTypeFont font) {
	// ground
	ofEnableAlphaBlending();
	ofSetColor(0, 150);
	ofFill();
	ofRect(10, 30, ofGetWidth()-20, ofGetHeight()-40);
	ofDisableAlphaBlending();
	// Osc settings
	ofSetColor(ofColor::white);
	ofFill();
	font.drawString("OSC SETTINGS", 15, 50);
	// Host: xxx.xxx.xxx.xxx Port: xxxx, Touch Count
	font.drawString("Host: ", 15, 90);
	font.drawString("Port: ", 15, 110);
	font.drawString("Devicename: ", 15, 130);
	font.drawString("[To open the settings xml, press key 's']", 167, 150);
	
	checkboxOscArray.display();
	checkboxFrame.display();
	//cbTimestamp.display();
	checkboxPosition.display();
	//cbVelocity.display();
	//cbMaxis.display();
	checkboxSize.display();
	checkboxAngle.display();
	// shortcuts
	font.drawString("[Shortcut: 2]", 350, 200);
	font.drawString("[Shortcut: 3]", 350, 220);
	font.drawString("[Shortcut: 4]", 350, 240);
	font.drawString("[Shortcut: 5]", 350, 260);
	
	// TODO: 
	//vera.drawString(ofToString("Number of Devices: ") + ofToString(pad.getNumDevices()), 15, 150);
}


void SettingsMVC::mousePressed(int x, int y) {
	cout << "ViewerSettings mousePressed()";
	/* Check boxes
	 */
	checkboxOscArray.pressed(x, y);
	checkboxFrame.pressed(x, y);
	//cbTimestamp.pressed(x, y);
	checkboxPosition.pressed(x, y);
	//cbVelocity.pressed(x, y);
	//cbMaxis.pressed(x, y);
	checkboxSize.pressed(x, y);
	checkboxAngle.pressed(x, y);
}


void SettingsMVC::keyPressed(int key) {
	switch (key) {
		/* OSC frame
		 */
		case 'w':
			if (checkboxFrame.status == true) {
				checkboxFrame.status = false;
			} else {
				checkboxFrame.status = true;
			}
			//console.addString("Shortcut padFrame: " + ofToString(xmlPadFrame), true);
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
			if (checkboxPosition.status == true) {
				checkboxPosition.status = false;
			} else {
				checkboxPosition.status = true;
			}
			//console.addString("Shortcut padPosition: " + ofToString(xmlPadPosition), true);
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
			if (checkboxSize.status == true) {
				checkboxSize.status = false;
			} else {
				checkboxSize.status = true;
			}
			//console.addString("Shortcut padSize: " + ofToString(xmlPadSize), true);
			break;
			
		/* OSC angle
		 */
		case 't':
			if (checkboxAngle.status == true) {
				checkboxAngle.status = false;
			} else {
				checkboxAngle.status = true;
			}
			//console.addString("Shortcut padAngle: " + ofToString(xmlPadAngle), true);
			break;
			
		default:
			break;
	}
}
