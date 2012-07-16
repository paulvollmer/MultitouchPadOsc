/**
 * This example shows how to receive osc messages from MultitouchPadOsc App.
 * It will draw a ellipse with values from received x-, y position and size.
 * 
 * Based on oscP5 oscP5sendreceive example by andreas schlegel [ http://www.sojamo.de/oscP5 ]
 *
 * MultitouchPadOsc version:   0.1.2
 */

import oscP5.*;
OscP5 oscP5;


// Set the osc port
int oscPort = 12345;
// Set the MultitouchPadOsc devicename
String devicename = "mtpadosc";

// Values we want to receive and store.
float x, y, diam;



void setup(){
	size(400,400);
	smooth();
	frameRate(25);
	// start oscP5, listening for incoming messages
	oscP5 = new OscP5(this, oscPort);
}

void draw(){
	background(255);

	noStroke();
	fill(#ff0000);
	ellipse(x, y, diam, diam);
}


// incoming osc message are forwarded to the oscEvent method.
void oscEvent(OscMessage theOscMessage){
	// print the address pattern and the typetag of the received OscMessage
	/*print("### received an osc message.");
	print(" addrpattern: "+theOscMessage.addrPattern());
	println(" typetag: "+theOscMessage.typetag());*/
	
	for(int i=0; i<20; i++) {
		if(theOscMessage.checkAddrPattern("/"+devicename+"/"+i+"/size") == true) {
			if(theOscMessage.checkTypetag("f")) {
				diam = theOscMessage.get(0).floatValue() * 50;
				println(diam);

			}
		}

		if(theOscMessage.checkAddrPattern("/"+devicename+"/"+i+"/x") == true) {
			x = map(theOscMessage.get(0).floatValue(), 0, 1, 0, width);
		}
		if(theOscMessage.checkAddrPattern("/"+devicename+"/"+i+"/y") == true) {
			y = map(theOscMessage.get(0).floatValue(), 1, 0, 0, height);
			println("Position x:"+x+", y: "+y);
		}

	}

}

