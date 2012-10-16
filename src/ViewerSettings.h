/*
 *  SettingsViewer.h
 *  MultitouchPadOsc
 *
 *  Created by Paul Vollmer on 16.10.12.
 *  Copyright 2012 Wrong-Entertainment. All rights reserved.
 *
 */

#ifndef VIEWER_SETTINGS_H_
#define VIEWER_SETTINGS_H_

#include "ofMain.h"
#include "ofxXmlDefaultSettings.h"
#include "wCheckbox.h"

/**
 * 
 */
class ViewerSettings {
public:
	ViewerSettings();
	void init(ofTrueTypeFont font);
	void getXml(ofxXmlDefaultSettings xml);
	void addXml(ofxXmlDefaultSettings xml);
	void setXml(ofxXmlDefaultSettings xml);
	void logCheckboxStatus();
	void draw(ofTrueTypeFont font);
	void mousePressed(int x, int y);
	void keyPressed(int key);
	
	wCheckbox     checkboxOscArray;     
	wCheckbox     checkboxFrame;        // checkbox to trigger pad frame on/off
	//wCheckbox   checkboxTimestamp;    // checkbox to trigger pad timestamp on/off
	wCheckbox     checkboxPosition;     // checkbox to trigger finger x-, y-position on/off
	//wCheckbox   checkboxVelocity;     // checkbox to trigger finger x-, y-velocity on/off
	//wCheckbox   checkboxMaxis;        // checkbox to trigger finger minor-, major-axis on/off
	wCheckbox     checkboxSize;         // checkbox to trigger finger size on/off
	wCheckbox     checkboxAngle;        // checkbox to trigger finger angle on/off
	
	string xmlPadDevicename;            // Trackpad devicename
	
	// OSC variables
	int    oscOut;                      // Send out OSC message, 0 = true, 1 = false
	string oscHost;                     // OSC host variable
	int    oscPort;                     // OSC port variable
	
	
private:
	
};
#endif // VIEWER_SETTINGS_H_