//
// ConsoleMVC.h
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

#ifndef CONSOLE_MVC_H_
#define CONSOLE_MVC_H_

#include "ofMain.h"
#include "ofxXmlDefaultSettings.h"
#include "Variables.h"

#define NUM_STRINGS 23


/**
 * This class is used to print out some information about the application.
 */
class ConsoleMVC {
public:
	ConsoleMVC();
	void init();
	void draw(ofTrueTypeFont font);
	/**
	 * add a string to console text
	 */
	void addString(string msg, bool log = false);

	/**
	 * Variables
	 */
	int    currentConsoleStrings;
	string consoleStrings[NUM_STRINGS];

};
#endif // CONSOLE_MVC_H_
