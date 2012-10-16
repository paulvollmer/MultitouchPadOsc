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

void TouchpointsMVC::getXml(ofxXmlDefaultSettings xml) {
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

/*void TouchpointsMVC::setXml(ofxXmlDefaultSettings xml) {
	
}*/

void TouchpointsMVC::log() {
	ofLog() << "XML: pointColor rgba = " << touchpointColor.getClamped();
	ofLog() << "XML: lineColor rgba  = " << touchpointLines.getClamped();
	ofLog() << "XML: crossColor rgba = " << touchpointCross.getClamped();
}


void TouchpointsMVC::draw(ofTrueTypeFont font, ofxMultiTouchPad & pad) {
	std::vector<ofPoint>touches;
	pad.getTouchesAsOfPoints(&touches);
	
	/* Draw the touch count typo
	 */
	font.drawString("Touch Count: "+ofToString(pad.getTouchCount(), 0), 15, ofGetHeight()-15);
	
	/* Display finger blobs
	 * connect all touches with a line
	 */
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
	
	/* display all finger blobs
	 */
	for(int i=0; i<pad.getTouchCount(); i++) {
		// get a single touch as MTouch struct....
		MTouch touch;
		if (!pad.getTouchAt(i,&touch)) continue; // guard..
		
		// using MTouch struct
		int x = ofMap(touch.x, 0.0, 1.0, 40, ofGetWidth()-40);
		int y = ofMap(touch.y, 0.0, 1.0, 80, ofGetHeight()-40);
		int size = touch.size*50;
		
		// Transform
		ofPushMatrix();
		ofTranslate(x, y, 0);
		ofRotateZ(touch.angle);
		
		ofEnableSmoothing();
		// finger blob circle
		ofSetColor(touchpointColor);
		ofFill();
		ofEllipse(0, 0, size, size*0.625);
		
		// cross at the circle center
		ofSetColor(touchpointCross);
		ofNoFill();
		ofLine(-5, 0, 5, 0);
		ofLine(0, -5, 0, +5);
		ofDisableSmoothing();
		
		ofPopMatrix();
		
		// draw info
		/*char _s [128];
		 sprintf(_s, "ID %05i, frame: %05i, x: %6.3f, y: %6.3f, angle: %8.3f,"
		 "size: %6.3f nFingers: %d\n",
		 touch.ID,touch.frame,touch.x,touch.y,touch.angle,
		 touch.size,pad.getTouchCount());
		 ofSetHexColor(0xffffff);
		 ofDrawBitmapString((string)_s, 0,0);*/
	}
	
}

void TouchpointsMVC::mousePressed(int x, int y) {

}

void TouchpointsMVC::keyPressed(int key) {

}
