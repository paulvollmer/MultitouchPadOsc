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
	
	/**
	 * Checkbox to trigger osc send on/off
	 */
	wCheckbox     checkboxOscArray;
	/**
	 * Checkbox to trigger pad frame on/off
	 */
	wCheckbox     checkboxFrame;
	
	// Checkbox to trigger pad timestamp on/off
	//wCheckbox   checkboxTimestamp;
	
	/**
	 * Checkbox to trigger finger x-, y-position on/off
	 */
	wCheckbox     checkboxPosition;
	
	/**
	 * Checkbox to trigger finger x-, y-velocity on/off
	 */
	//wCheckbox   checkboxVelocity;
	/**
	 * Checkbox to trigger finger minor-, major-axis on/off
	 */
	//wCheckbox   checkboxMaxis;
	
	/**
	 * Checkbox to trigger finger size on/off
	 */
	wCheckbox     checkboxSize;
	
	/**
	 * Checkbox to trigger finger angle on/off
	 */
	wCheckbox     checkboxAngle;
	
	/**
	 * OSC host variable
	 */
	string oscHost;
	
	/**
	 * OSC port variable
	 */
	int    oscPort;
	
	/**
	 * Trackpad devicename for the osc message
	 */
	string oscTouchpadDevicename;
	
};
#endif // VIEWER_SETTINGS_H_