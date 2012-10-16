//
// ConsoleMVC.cpp
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

#include "ConsoleMVC.h"

ConsoleMVC::ConsoleMVC(){}


void ConsoleMVC::init(ofTrueTypeFont font) {
	/* Console
	 */
	console.init(font);
}


void ConsoleMVC::getXml(ofxXmlDefaultSettings xml) {
	
}


void ConsoleMVC::addXml(ofxXmlDefaultSettings xml) {
}

/*void TouchpointsMVC::setXml(ofxXmlDefaultSettings xml) {
 
 }*/

void ConsoleMVC::log() {
}


void ConsoleMVC::draw(ofTrueTypeFont font) {
	/* Ground
	 */
	ofEnableAlphaBlending();
	ofSetColor(0, 150);
	ofFill();
	ofRect(10, 30, ofGetWidth()-20, ofGetHeight()-40);
	ofDisableAlphaBlending();
	
	/* headline text
	 */
	ofSetColor(ofColor::white);
	font.drawString("Sended osc messages:", 15, 50);
	console.display(15, 90);
}

void ConsoleMVC::mousePressed(int x, int y) {
	
}

void ConsoleMVC::keyPressed(int key) {
	/* Open the settings xml file
	 */
	if(key == 's') {
		string commandStr = "open " + ofFilePath::getCurrentWorkingDirectory() + "/ofSettings.xml";
		system(commandStr.c_str());
		
		console.addString("Open XML settings file.");
	}
}
