/*
 *  SettingsViewer.cpp
 *  MultitouchPadOsc
 *
 *  Created by Paul Vollmer on 16.10.12.
 *  Copyright 2012 Wrong-Entertainment. All rights reserved.
 *
 */

#include "ViewerSettings.h"

ViewerSettings::ViewerSettings(){}

void ViewerSettings::init(ofTrueTypeFont font) {
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


void ViewerSettings::getXml(ofxXmlDefaultSettings xml) {
	/* Trackpad variables
	 */
	xmlPadDevicename = xml.getValue("pad:devicename", "mtpadosc");
	
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

void ViewerSettings::addXml(ofxXmlDefaultSettings xml) {
	/* Trackpad variables
	 */
	xmlPadDevicename = "mtpad";
	
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
	xml.addValue("devicename", xmlPadDevicename);
	
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

void ViewerSettings::setXml(ofxXmlDefaultSettings xml) {
	xml.setValue("pad:devicename", xmlPadDevicename, 0);
	
	xml.setValue("pad:array", checkboxOscArray.status, 0);
	xml.setValue("pad:frame", checkboxFrame.status, 0);
	//xml.setValue("pad:timestamp", checkboxTimestamp.status, 0);
	xml.setValue("pad:position", checkboxPosition.status, 0);
	//xml.setValue("pad:velocity", checkboxVelocity.status, 0);
	xml.setValue("pad:size", checkboxSize.status, 0);
	//xml.setValue("pad:maxis", checkboxMaxis.status, 0);
	xml.setValue("pad:angle", checkboxAngle.status, 0);
}


void ViewerSettings::logCheckboxStatus(){
	ofLog() << "pad:devicename  = " << xmlPadDevicename;
	
	ofLog() << "pad:array       = " << checkboxOscArray.status;
	ofLog() << "pad:frame       = " << checkboxFrame.status;
	//ofLog() << "pad:timestamp   = " << checkboxTimestamp.status;
	ofLog() << "pad:position    = " << checkboxPosition.status;
	//ofLog() << "pad:velocity    = " << checkboxVelocity.status;
	ofLog() << "pad:size        = " << checkboxSize.status;
	//ofLog() << "pad:maxis       = " << checkboxMaxis.status;
	ofLog() << "pad:angle       = " << checkboxAngle.status;
}
	

void ViewerSettings::draw(ofTrueTypeFont font) {
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
	
	//vera.drawString(ofToString("Number of Devices: ") + ofToString(pad.getNumDevices()), 15, 150);
}


void ViewerSettings::mousePressed(int x, int y) {
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


void ViewerSettings::keyPressed(int key) {
	cout << "ViewerSettings keyPressed()";
	
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
