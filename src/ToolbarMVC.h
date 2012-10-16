//
// ToolbarMVC.h
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