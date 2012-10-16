/*
 *  ToolbarMVC.h
 *  MultitouchPadOsc
 *
 *  Created by Paul Vollmer on 16.10.12.
 *  Copyright 2012 Wrong-Entertainment. All rights reserved.
 *
 */


#ifndef TOOLBAR_MVC_H_
#define TOOLBAR_MVC_H_

#include "ofMain.h"
#include "ofxXmlDefaultSettings.h"
#include "wImageButton.h"

class ToolbarMVC {	
public:
	ToolbarMVC();
	void init();
	void getXml(ofxXmlDefaultSettings xml);
	void addXml(ofxXmlDefaultSettings xml);
	void setXml(ofxXmlDefaultSettings xml);
	void log();
	void draw();
	void windowResized(int w, int h);
	void mousePressed(int x, int y);
	void keyPressed(int key);
	
	/**
	 * Button to trigger osc activity on/off
	 */
	wImageButton buttonOscActive;
	ofImage      oscSendImage;
	
	/**
	 * The current window mode. Normal or mini
	 */
	wImageButton buttonWindowMode;
	
	/**
	 * This mode can be used to run in safety mode.
	 * No dock or other system stuff can be selected.
	 */
	//wImageButton btnSafetyMode;
	
	/**
	 * Button to show/hide touchpoints
	 */
	wImageButton buttonTouchpoints;
	
	/**
	 * Button to show/hide settings
	 */
	wImageButton buttonSettings;
	
	/**
	 * Button to show/hide console
	 */
	wImageButton buttonConsole;
	
};
#endif // TOOLBAR_MVC_H_