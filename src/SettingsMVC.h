//
// SettingsMVC.h
// MultitouchPadOsc is released under the MIT License.
//
// Copyright (c) 2011-2016, Paul Vollmer
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

#ifndef VIEWER_MVC_H_
#define VIEWER_MVC_H_

#include "ofMain.h"
#include "ofxXmlDefaultSettings.h"
#include "ofxMultiTouchPad.h"
#include "Checkbox.h"

#include "Variables.h"

/**
 * This class contains all settings stuff (host, port, devicename etc.)
 */
class SettingsMVC {
public:
	SettingsMVC();
	void init(ofTrueTypeFont font);
	void getXml(ofxXmlDefaultSettings xml);
	void addXml(ofxXmlDefaultSettings xml);
	void setXml(ofxXmlDefaultSettings xml);
	void log();
	void draw(ofTrueTypeFont font, ofxMultiTouchPad & pad);
	void mousePressed(int x, int y);
	void keyPressed(int key, bool cmdKeyPressed);

	/**
	 * Checkbox to trigger osc send on/off
	 */
	Checkbox checkboxOscArray;
	/**
	 * Checkbox to trigger pad frame on/off
	 */
	Checkbox checkboxFrame;
	/**
	 * Checkbox to trigger pad timestamp on/off
	 */
	//Checkbox checkboxTimestamp;
	/**
	 * Checkbox to trigger finger x-, y-position on/off
	 */
	Checkbox checkboxPosition;
	/**
	 * Checkbox to trigger finger x-, y-velocity on/off
	 */
	//Checkbox checkboxVelocity;
	/**
	 * Checkbox to trigger finger minor-, major-axis on/off
	 */
	//Checkbox checkboxMaxis;
	/**
	 * Checkbox to trigger finger size on/off
	 */
	Checkbox checkboxSize;
	/**
	 * Checkbox to trigger finger angle on/off
	 */
	Checkbox checkboxAngle;

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
#endif // VIEWER_MVC_H_
