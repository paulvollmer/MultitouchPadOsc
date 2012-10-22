//
// TouchpointsMVC.h
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

#ifndef TOUCHPOINTS_MVC_H_
#define TOUCHPOINTS_MVC_H_

#include "ofMain.h"
#include "ofxXmlDefaultSettings.h"
#include "wCheckbox.h"
#include "ofxMultiTouchPad.h"

#include "Variables.h"

/**
 * The Touchpoints MVC class
 */
class TouchpointsMVC {	
public:
	TouchpointsMVC();
	void init(ofTrueTypeFont font);
	void getXml(ofxXmlDefaultSettings xml);
	void addXml(ofxXmlDefaultSettings xml);
	void setXml(ofxXmlDefaultSettings xml);
	void log();
	void draw(ofTrueTypeFont font, ofxMultiTouchPad & pad, bool touchpointsMenuActive);
	void mousePressed(int x, int y);
	
	/* GUI
	 */
	wCheckbox checkboxShowTouchpoints;
	wCheckbox checkboxShowLines;
	wCheckbox checkboxShowInfo;
	
	/* Touchpoint color variables
	 */
	ofColor touchpointColor;
	ofColor touchpointLines;
	ofColor touchpointCross;
	
private:
	void drawSingleTouchpoint(int size);
	void drawSingleTouchpointCross();
	void drawSingleTouchpointInfo(ofTrueTypeFont font, MTouch & touch);
};
#endif // TOUCHPOINTS_MVC_H_
