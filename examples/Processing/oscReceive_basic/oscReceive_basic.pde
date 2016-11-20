/**
 * This example shows how to receive osc messages from MultitouchPadOsc App.
 * It will draw a ellipse with values from received x-, y position and size.
 *
 * Based on oscP5 oscP5sendreceive example by andreas schlegel [ http://www.sojamo.de/oscP5 ]
 *
 * MultitouchPadOsc version: 0.1.2
 *
 * @author   Paul Vollmer
 * @date     2012.10.12
 */

import oscP5.*;
OscP5 oscP5;

// Set the MultitouchPadOsc devicename
String DEVICENAME = "mtpad";
// The total number of Touchpoints
int TOTAL_TOUCHPOINTS = 20;
// Values we want to receive and store.
float[] x = new float[TOTAL_TOUCHPOINTS];
float[] y = new float[TOTAL_TOUCHPOINTS];
float[] size = new float[TOTAL_TOUCHPOINTS];



void setup() {
  size(400,400);
  smooth();
  frameRate(25);
  // start oscP5, listening for incoming messages
  oscP5 = new OscP5(this, 12345);
}

void draw() {
  background(255);

  noStroke();
  fill(#ff0000);
  for(int i=0; i<TOTAL_TOUCHPOINTS; i++){
    ellipse(x[i], y[i], size[i], size[i]);
  }
}


// incoming osc message are forwarded to the oscEvent method.
void oscEvent(OscMessage theOscMessage) {
  // print the address pattern and the typetag of the received OscMessage
  /*print("### received an osc message.");
   	print(" addrpattern: "+theOscMessage.addrPattern());
   	println(" typetag: "+theOscMessage.typetag());*/

  for(int i=0; i<TOTAL_TOUCHPOINTS; i++){
    if(theOscMessage.checkAddrPattern("/"+DEVICENAME+"/"+i+"/size") == true) {
      if(theOscMessage.checkTypetag("f")) {
        size[i] = theOscMessage.get(0).floatValue() * 50;
        println(size[i]);
      }
    }

    if(theOscMessage.checkAddrPattern("/"+DEVICENAME+"/"+i+"/x") == true) {
      x[i] = map(theOscMessage.get(0).floatValue(), 0, 1, 0, width);
    }
    if(theOscMessage.checkAddrPattern("/"+DEVICENAME+"/"+i+"/y") == true) {
      y[i] = map(theOscMessage.get(0).floatValue(), 0, 1, 0, height);
      println("Position x:"+x[i]+", y: "+y[i]);
    }
  }
}
