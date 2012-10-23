//
// main.cpp
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

/**
 * @plattform        MacOs 10.6
 *                   Win XXX
 *                   Linux XXX
 * @openFrameworks   0071
 * @dependencies     ofxXmlSettings
 *                   ofxXmlDefaultSettings
 *                   ofxOsc
 *                   ofxUI
 *                   ofxModifierKeys
 * @modified         2012.10.23
 * @version          0.1.3
 */

#include "ofMain.h"
#include "MultitouchPadOscApp.h"
#include "ofAppGlutWindow.h"
#include "Cocoa/Cocoa.h"

int main() {
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 500, 400, OF_WINDOW); // setup the GL context
	
	// Setting up the menubar.
	if (NSApp){  
        NSMenu      *menu;  
        NSMenuItem  *menuItem;   
        [NSApp setMainMenu:[[NSMenu alloc] init]];  
		// Appname menu
		menu = [[NSMenu alloc] initWithTitle:@""];  
		[menu addItemWithTitle:@"About MultitouchPadOsc" action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];
		[menu addItem:[NSMenuItem separatorItem]];
		[menu addItemWithTitle:@"Hide MultitouchPadOsc" action:@selector(hide:) keyEquivalent:@"h"];
		menuItem = (NSMenuItem *)[menu addItemWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
		[menuItem setKeyEquivalentModifierMask:(NSAlternateKeyMask|NSCommandKeyMask)];
		[menu addItemWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];
		[menu addItem:[NSMenuItem separatorItem]];
		[menu addItemWithTitle:@"Quit MultitouchPadOsc" action:@selector(terminate:) keyEquivalent:@"q"]; 
		// Put menu into the menubar
		menuItem = [[NSMenuItem alloc] initWithTitle:@"Apple" action:nil keyEquivalent:@""];  
		[menuItem setSubmenu:menu];  
		[[NSApp mainMenu] addItem:menuItem];
    }
	
	// this kicks off the running of my app can be
	// OF_WINDOW or OF_FULLSCREEN pass in width and height too:
	ofRunApp(new MultitouchPadOscApp());
}
