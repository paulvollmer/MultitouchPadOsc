//
// ToolbarMVC.cpp
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

#include "TouchpointsMVC.h"

TouchpointsMVC::TouchpointsMVC(){}

void TouchpointsMVC::init(ofTrueTypeFont font) {
	checkboxShowTouchpoints.init(font, "Touchpoints", 70, 40);
	checkboxShowLines.init(font, "Lines", 178, 40);
	checkboxShowInfo.init(font, "Information", 240, 40);
}


void TouchpointsMVC::getXml(ofxXmlDefaultSettings xml) {
	/* Touchpoint info
	 */
	checkboxShowTouchpoints.status = xml.getAttribute("touchpoints", "points", true, 0);
	checkboxShowLines.status = xml.getAttribute("touchpoints", "lines", true, 0);
	checkboxShowInfo.status = xml.getAttribute("touchpoints", "infos", true, 0);
	/* Touchpoint color
	 */
	touchpointColor[0] = xml.getAttribute("touchpoints:pointColor", "r", 0, 0);
	touchpointColor[1] = xml.getAttribute("touchpoints:pointColor", "g", 155, 0);
	touchpointColor[2] = xml.getAttribute("touchpoints:pointColor", "b", 255, 0);
	touchpointColor[3] = xml.getAttribute("touchpoints:pointColor", "a", 255, 0);
	touchpointLines[0] = xml.getAttribute("touchpoints:lineColor", "r", 0, 0);
	touchpointLines[1] = xml.getAttribute("touchpoints:lineColor", "g", 255, 0);
	touchpointLines[2] = xml.getAttribute("touchpoints:lineColor", "b", 255, 0);
	touchpointLines[3] = xml.getAttribute("touchpoints:lineColor", "a", 255, 0);
	touchpointCross[0] = xml.getAttribute("touchpoints:crossColor", "r", 255, 0);
	touchpointCross[1] = xml.getAttribute("touchpoints:crossColor", "g", 0, 0);
	touchpointCross[2] = xml.getAttribute("touchpoints:crossColor", "b", 0, 0);
	touchpointCross[3] = xml.getAttribute("touchpoints:crossColor", "a", 255, 0);
	
}


void TouchpointsMVC::addXml(ofxXmlDefaultSettings xml) {
	/* Touchpoint visual/infos
	 */
	checkboxShowTouchpoints.status = true;
	checkboxShowLines.status = true;
	checkboxShowInfo.status = true;
	xml.addAttribute("touchpoints", "points", checkboxShowTouchpoints.status, 0);
	xml.addAttribute("touchpoints", "lines", checkboxShowLines.status, 0);
	xml.addAttribute("touchpoints", "infos", checkboxShowInfo.status, 0);
	/* Touchpoint color
	 */
	touchpointColor.set(0, 155, 255, 255);
	touchpointLines.set(0, 255, 255, 255);
	touchpointCross.set(255, 255, 255, 255);
	xml.addTag("touchpoints");
	xml.pushTag("touchpoints", 0);
	xml.addTag("pointColor");
	xml.addAttribute("pointColor", "r", touchpointColor[0], 0);
	xml.addAttribute("pointColor", "g", touchpointColor[1], 0);
	xml.addAttribute("pointColor", "b", touchpointColor[2], 0);
	xml.addAttribute("pointColor", "a", touchpointColor[3], 0);
	xml.addTag("lineColor");
	xml.addAttribute("lineColor", "r", touchpointLines[0], 0);
	xml.addAttribute("lineColor", "g", touchpointLines[1], 0);
	xml.addAttribute("lineColor", "b", touchpointLines[2], 0);
	xml.addAttribute("lineColor", "a", touchpointLines[3], 0);
	xml.addTag("crossColor");
	xml.addAttribute("crossColor", "r", touchpointCross[0], 0);
	xml.addAttribute("crossColor", "g", touchpointCross[1], 0);
	xml.addAttribute("crossColor", "b", touchpointCross[2], 0);
	xml.addAttribute("crossColor", "a", touchpointCross[3], 0);
	xml.popTag();
}


void TouchpointsMVC::setXml(ofxXmlDefaultSettings xml) {
	xml.pushRoot();
	xml.setAttribute("touchpoints", "points", checkboxShowTouchpoints.status, 0);
	xml.setAttribute("touchpoints", "lines", checkboxShowLines.status, 0);
	xml.setAttribute("touchpoints", "infos", checkboxShowInfo.status, 0);
	xml.popRoot();
}


void TouchpointsMVC::log() {
	ofLog() << "XML: points          = " << checkboxShowTouchpoints.status;
	ofLog() << "XML: lines           = " << checkboxShowLines.status;
	ofLog() << "XML: infos           = " << checkboxShowInfo.status;
	ofLog() << "XML: pointColor rgba = " << touchpointColor.getClamped();
	ofLog() << "XML: lineColor rgba  = " << touchpointLines.getClamped();
	ofLog() << "XML: crossColor rgba = " << touchpointCross.getClamped();
}


void TouchpointsMVC::draw(ofTrueTypeFont font, ofxMultiTouchPad & pad, bool touchpointsMenuActive) {
	/* Draw if the menu is active
	 */
	if (touchpointsMenuActive == true) {
		/* GUI
		 */
		ofSetColor(COLOR_LIGHT_GREY);
		ofFill();
		font.drawString("Display", FONT_POSITION_X, 50);
		checkboxShowTouchpoints.display();
		checkboxShowLines.display();
		checkboxShowInfo.display();
		/* The touch count typo
		 */
		ofSetColor(COLOR_LIGHT_GREY);
		ofFill();
		font.drawString("Touch Count: "+ofToString(pad.getTouchCount(), 0), 15, ofGetHeight()-15);
	}
	
	std::vector<ofPoint>touches;
	pad.getTouchesAsOfPoints(&touches);
	
	/* Display finger blobs if the checkbox ist true.
	 * Connect all touches with a line.
	 */
	if (checkboxShowLines.status == true) {
		ofEnableSmoothing();
		for(int i=0; (i<touches.size()-1 && touches.size()>1); i++) {
			ofSetColor(touchpointLines);
			int x1 = ofMap(touches.at(i).x,   0.0, 1.0, 30, ofGetWidth()-30);
			int y1 = ofMap(touches.at(i).y,   0.0, 1.0, 70, ofGetHeight()-30);
			int x2 = ofMap(touches.at(i+1).x, 0.0, 1.0, 30, ofGetWidth()-30);
			int y2 = ofMap(touches.at(i+1).y, 0.0, 1.0, 70, ofGetHeight()-30);
			ofLine(x1, y1, x2, y2);
		}
		ofDisableSmoothing();
	}
	
	/* display all finger blobs
	 */
	for(int i=0; i<pad.getTouchCount(); i++) {
		/* get a single touch as MTouch struct....
		 */
		MTouch touch;
		if (!pad.getTouchAt(i,&touch)) continue; // guard..
		
		/* Using MTouch struct
		 */
		int x = ofMap(touch.x, 0.0, 1.0, 40, ofGetWidth()-40);
		int y = ofMap(touch.y, 0.0, 1.0, 80, ofGetHeight()-40);
		int size = touch.size*50;
		
		/* Transform
		 */
		if (checkboxShowTouchpoints.status == true) {
			ofPushMatrix();
			ofTranslate(x, y, 0);
			ofRotateZ(touch.angle);
			ofEnableSmoothing();
		
			drawSingleTouchpoint(size);
			drawSingleTouchpointCross();
		
			ofPopMatrix();
		}
		
		if (touchpointsMenuActive == true) {
			ofPushMatrix();
			ofTranslate(x, y, 0);
			drawSingleTouchpointInfo(font, touch);
			ofPopMatrix();
		}
	} // End for
}


void TouchpointsMVC::mousePressed(int x, int y) {
	checkboxShowTouchpoints.pressed(x, y);
	checkboxShowLines.pressed(x, y);
	checkboxShowInfo.pressed(x, y);
}


void TouchpointsMVC::drawSingleTouchpoint(int size) {
	/* finger blob circle
	 */
	ofSetColor(touchpointColor);
	ofFill();
	ofEllipse(0, 0, size, size*0.625);
}


void TouchpointsMVC::drawSingleTouchpointCross() {
	/* cross at the circle center
	 */
	ofSetColor(touchpointCross);
	ofNoFill();
	ofLine(-5, 0, 5, 0);
	ofLine(0, -5, 0, +5);
	ofDisableSmoothing();
}


void TouchpointsMVC::drawSingleTouchpointInfo(ofTrueTypeFont font, MTouch & touch) {
	if (checkboxShowInfo.status == true) {
		/* The info background
		 */
		ofEnableAlphaBlending();
		ofSetColor(ofColor::black, 127);
		ofFill();
		ofRect(5, 5, 245, 20);
		ofDisableAlphaBlending();
		/* The text info
		 */
		ofSetColor(ofColor::white);
		ofFill();
		char _s [128];
		sprintf(_s, "X:%4.3f Y:%4.3f Size:%3.2f Angle:%3.0f\n",
				touch.x, touch.y, touch.size, touch.angle);
		font.drawString((string)_s, 10, 20);
	}
}
