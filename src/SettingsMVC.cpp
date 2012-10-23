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
	
	checkboxOscArray.init(font, "OSC array xysa", FONT_POSITION_X, 160);
	checkboxFrame.init(font, "Frame active", FONT_POSITION_X, 180);
	//checkboxTimestamp.init(vera, "timestamp active",  60, 170, defXmlPadTimestamp);
	checkboxPosition.init(font, "X-, Y-Position active", FONT_POSITION_X, 200);
	//checkboxVelocity.init(vera, "x-, y-velocity active", 60, 200, defXmlPadVelocity);
	//checkboxMaxis.init(vera, "minor-, major-axis active", 60, 215, defXmlPadMaxis);
	checkboxSize.init(font, "Size active", FONT_POSITION_X, 220);
	checkboxAngle.init(font, "Angle active", FONT_POSITION_X, 240);
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
	checkboxPosition.status = true;
	//checkboxVelocity.status = false;
	checkboxSize.status = true;
	//checkboxMaxis.status = false;
	checkboxAngle.status = true;
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
	xml.pushRoot();
	
	xml.setAttribute("osc", "host", oscHost, 0);
	xml.setAttribute("osc", "port", oscPort, 0);
	
	xml.setValue("pad:devicename", oscTouchpadDevicename, 0);
	xml.setValue("pad:array", checkboxOscArray.status, 0);
	xml.setValue("pad:frame", checkboxFrame.status, 0);
	//xml.setValue("pad:timestamp", checkboxTimestamp.status, 0);
	xml.setValue("pad:position", checkboxPosition.status, 0);
	//xml.setValue("pad:velocity", checkboxVelocity.status, 0);
	xml.setValue("pad:size", checkboxSize.status, 0);
	//xml.setValue("pad:maxis", checkboxMaxis.status, 0);
	xml.setValue("pad:angle", checkboxAngle.status, 0);
	
	xml.popRoot();
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
	

void SettingsMVC::draw(ofTrueTypeFont font, ofxMultiTouchPad & pad) {
	/* ground
	 */
	ofEnableAlphaBlending();
	ofSetColor(0, 150);
	ofFill();
	ofRect(10, 30, ofGetWidth()-20, ofGetHeight()-40);
	ofDisableAlphaBlending();
	
	ofSetColor(COLOR_LIGHT_GREY);
	ofFill();
	
	/* Osc Main Settings
	 */
	font.drawString("OSC Main Settings", FONT_POSITION_X, 50);
	ofLine(FONT_POSITION_X, 60, ofGetWidth()-FONT_POSITION_X, 60);
	// Host: xxx.xxx.xxx.xxx Port: xxxx, Devicename
	font.drawString("Host: ", FONT_POSITION_X, 80);
	font.drawString("Port: ", 190, 80);
	font.drawString("Devicename: ", FONT_POSITION_X, 100);
	
	/* OSC Message Settings
	 */
	font.drawString("OSC Message Settings", FONT_POSITION_X, 140);
	ofLine(FONT_POSITION_X, 150, ofGetWidth()-FONT_POSITION_X, 150);
	checkboxOscArray.display();
	checkboxFrame.display();
	//cbTimestamp.display();
	checkboxPosition.display();
	//cbVelocity.display();
	//cbMaxis.display();
	checkboxSize.display();
	checkboxAngle.display();
	// shortcuts
	font.drawString("'cmd a'", 190, 170);
	font.drawString("'cmd s'", 190, 190);
	font.drawString("'cmd d'", 190, 210);
	font.drawString("'cmd f'", 190, 230);
	font.drawString("'cmd g'", 190, 250);
	
	/* Settings information
	 */
	font.drawString("Settings Information", FONT_POSITION_X, 290);
	ofLine(FONT_POSITION_X, 300, ofGetWidth()-FONT_POSITION_X, 300);
	font.drawString("Number of Devices: "+ofToString(pad.getNumDevices()), 15, 320);
	font.drawString("To open the settings xml, press key 'cmd x'", FONT_POSITION_X, 360);
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


void SettingsMVC::keyPressed(int key, bool cmdKeyPressed) {
	if (cmdKeyPressed == true) {
		
		switch (key) {
			/* OSC array
			 */
			case 'a':
				checkboxOscArray.status = !checkboxOscArray.status;
				break;

			/* OSC frame
			 */
			case 's':
				checkboxFrame.status = !checkboxFrame.status;
				// TODO:
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
			case 'd':
				checkboxPosition.status = !checkboxPosition.status;
				// TODO:
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
			case 'f':
				checkboxSize.status = !checkboxSize.status;
				// TODO:
				//console.addString("Shortcut padSize: " + ofToString(xmlPadSize), true);
				break;
				
			/* OSC angle
			 */
			case 'g':
				checkboxAngle.status = !checkboxAngle.status;
				// TODO:
				//console.addString("Shortcut padAngle: " + ofToString(xmlPadAngle), true);
				break;
				
			default:
				break;
		}
		
	} // End if cmdKeyPressed
}
