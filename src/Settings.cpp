/**
 * MagicTrackpadOsc is developed by Paul Vollmer (wrong-entertainment.com)
 * 
 * 
 * Copyright (c) 2011 Paul Vollmer
 *
 * MagicTrackpadOsc is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * MagicTrackpadOsc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with MagicTrackpadOsc; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * @author      Paul Vollmer
 * @modified    2011.12.14
 * @version     0.1.1
 */



#include "Settings.h"





/**
 * Constructor
 */
Settings::Settings() {
}



/**
 * Initialize XML settings file.
 * Load file and store all XML tags to variables.
 */
void Settings::init(string _filepath) {
	// set the _filepath to variable filepath
	// filepath is used to save changes at settings xml file.
	filepath = _filepath;
	
	
	// We load our settings file.
	// If it doesn't exist we can still make...
	if( xmlSettings.loadFile(filepath) ) {
		cout << "Settings - " << filepath << " loaded!" << endl;
	} else {
		cout << "Settings - unable to load " << filepath << " check data/ folder" << endl;
	}
	
	
	// Read the settings file.
	// Application variables
	appFramerate = xmlSettings.getValue("app:framerate", 60);
	appWindowx   = xmlSettings.getValue("app:windowx", 50);
	appWindowy   = xmlSettings.getValue("app:windowy", 50);
	appCount     = xmlSettings.getValue("app:count", 1);
	cout << "Settings - app:framerate  = " << appFramerate << endl;
	cout << "Settings - app:windowx    = " << appWindowx << endl;
	cout << "Settings - app:windowy    = " << appWindowy << endl;
	cout << "Settings - app:count      = " << appCount << endl;
	// Add +1 to appCount for the correct start of the application.
	appCount++;
	
	// OSC variables
	// If 0 = true, 1 = false
	oscHost = xmlSettings.getValue("osc:outhost", "127.0.0.1");
	oscPort = xmlSettings.getValue("osc:outport", 1234);
	oscOut  = xmlSettings.getValue("osc:out", 1);
	cout << "Settings - osc:outhost    = " << oscHost << endl;
	cout << "Settings - osc:outport    = " << oscPort << endl;
	cout << "Settings - osc:out        = " << oscOut << endl;
	
	// Trackpad variables
	padDevicename = xmlSettings.getValue("pad:devicename", "mtosc");
	padFrame      = xmlSettings.getValue("pad:frame", 1);
	padTimestamp  = xmlSettings.getValue("pad:timestamp", 1);
	padPosition   = xmlSettings.getValue("pad:position", 1);
	padVelocity   = xmlSettings.getValue("pad:velocity", 1);
	padSize       = xmlSettings.getValue("pad:size", 1);
	padMaxis      = xmlSettings.getValue("pad:maxis", 1);
	padAngle      = xmlSettings.getValue("pad:angle", 1);
	cout << "Settings - pad:devicename = " << padDevicename << endl;
	cout << "Settings - pad:frame      = " << padFrame << endl;
	cout << "Settings - pad:timestamp  = " << padTimestamp << endl;
	cout << "Settings - pad:position   = " << padPosition << endl;
	cout << "Settings - pad:velocity   = " << padVelocity << endl;
	cout << "Settings - pad:size       = " << padSize << endl;
	cout << "Settings - pad:maxis      = " << padMaxis << endl;
	cout << "Settings - pad:angle      = " << padAngle << endl;
}



/**
 * Update all variables.
 */
void Settings::save() {
	// Application variable update
	// Save the current app count to XML file.
	
	xmlSettings.setValue("app:count", appCount);
	cout << "Settings - appCount      = " << appCount << endl;
	
	// Get the current window x, y position and save to XML file.
	appWindowx = ofGetWindowPositionX();
	appWindowy = ofGetWindowPositionY();
	xmlSettings.setValue("app:windowx", appWindowx);
	xmlSettings.setValue("app:windowy", appWindowy);
	cout << "Settings - appWindowx    = " << appWindowx << endl;
	cout << "Settings - appWindowy    = " << appWindowy << endl;
	
	
	// OSC variable update
	// Save the current OSC variables to XML file.
	xmlSettings.setValue("osc:outhost", oscHost);
	xmlSettings.setValue("osc:outport", oscPort);
	xmlSettings.setValue("osc:out", oscOut);
	cout << "Settings - osc:outhost       = " << oscHost << endl;
	cout << "Settings - osc:outport       = " << oscPort << endl;
	cout << "Settings - osc:out        = " << oscOut << endl;
	
	xmlSettings.setValue("pad:devicename", padDevicename);
	xmlSettings.setValue("pad:frame", padFrame);
	xmlSettings.setValue("pad:timestamp", padTimestamp);
	xmlSettings.setValue("pad:position", padPosition);
	xmlSettings.setValue("pad:velocity", padVelocity);
	xmlSettings.setValue("pad:size", padSize);
	xmlSettings.setValue("pad:maxis", padMaxis);
	xmlSettings.setValue("pad:angle", padAngle);
	cout << "Settings - pad:devicename = " << padDevicename << endl;
	cout << "Settings - pad:frame      = " << padFrame << endl;
	cout << "Settings - pad:timestamp  = " << padTimestamp << endl;
	cout << "Settings - pad:position   = " << padPosition << endl;
	cout << "Settings - pad:velocity   = " << padVelocity << endl;
	cout << "Settings - pad:size       = " << padSize << endl;
	cout << "Settings - pad:maxis      = " << padMaxis << endl;
	cout << "Settings - pad:angle      = " << padAngle << endl;
	
	
	// save the settings file.
	xmlSettings.saveFile(filepath);
	cout << "Settings - file saved to " << filepath << " xml!" << endl;
}
