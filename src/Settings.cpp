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
	cout << "hets";
}



/**
 * Initialize XML settings file.
 * Store all XML tags to variables.
 */
void Settings::init(string _filepath) {
	// set the _filepath to variable filepath
	// filepath is used to save changes at settings xml file.
	filepath = _filepath;
	
	
	// We load our settings file.
	// If it doesn't exist we can still make...
	if( xmlSettings.loadFile(filepath) ) {
		cout << "  " << filepath << " loaded!" << endl;
	} else {
		cout << "  unable to load " << filepath << " check data/ folder" << endl;
	}
	
	
	// Read the settings file.
	// Application settings
	appFramerate = xmlSettings.getValue("app:framerate", 60);
	appWindowx   = xmlSettings.getValue("app:windowx", 50);
	appWindowy   = xmlSettings.getValue("app:windowy", 50);
	appCount     = xmlSettings.getValue("app:count", 1);
	cout << "  app:framerate  = " << appFramerate << endl;
	cout << "  app:windowx    = " << appWindowx << endl;
	cout << "  app:windowy    = " << appWindowy << endl;
	cout << "  app:count      = " << appCount << endl;
}
