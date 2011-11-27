/**
 * MagicTrackpadOsc is developed by Paul Vollmer (wrong-entertainment.com)
 * 
 * 
 * Copyright (c) 2011 Paul Vollmer
 *
 * MagicTrackpadOsc is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * MagicTrackpadOsc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with MagicTrackpadOsc; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * @author      Paul Vollmer
 * @modified    2011.11.26
 * @version     0.1.0
 */

import wrongPowder.io.Log;
import wrongPowder.io.Config;
import oscP5.*;
import netP5.*;



// classes
Log log;
Config config = new Config();
NetAddress oscnet;
Touchpad touchpad;

// background image
PImage backgroundImage;

// osc variables
String outHost;
int outPort;
// osc master name
String oscTrackpadName;
// what will be send
boolean oscOut;
boolean oscStateActive;
boolean oscFrameActive;
boolean oscTimestampActive;
boolean oscXposActive;
boolean oscYposActive;
boolean oscXveloActive;
boolean oscYveloActive;
boolean oscMajorAxisActive;
boolean oscMinorAxisActive;
boolean oscSizeActive;
boolean oscAngleActive;
boolean oscAngleRadiansActive;





/**
 * Setup
 */
void setup() {
  // Load Property file
  config.loadStatic(dataPath("")+"config.txt");
  config.list();
  
  
  // Initialize log class
  log = new Log(this);
  log.init();
  log.info("SETUP Starts");
  
  
  // Set size and framerate
  size(593, 600);
  smooth();
  int tempFramerate = config.getIntProperty("app.framerate", 30);
  frameRate(tempFramerate);
  log.info("SETUP Framerate: "+tempFramerate);
  
  
  // Load background image
  backgroundImage = loadImage("MagicTrackpad-01.png");
  
  
  // Setting up osc host-, port
  outHost = config.getStringProperty("osc.outhost", "127.0.0.1");
  outPort = config.getIntProperty("osc.outport", 9000);
  log.info("OSC Output Host: "+outHost+", Output Port: "+outPort);
  // osc message master name
  oscTrackpadName = config.getStringProperty("osc.trackpadname", "magictrackpad");
  log.info("OSC Trackpad Name: "+oscTrackpadName);
  // oscOut, if true it send messages
  oscOut = config.getBooleanProperty("osc.out", false);
  log.info("OSC Out: "+oscOut);
  // state
  oscStateActive = config.getBooleanProperty("osc.state", false);
  log.info("OSC State: "+oscStateActive);
  // frame
  oscFrameActive = config.getBooleanProperty("osc.frame", false);
  log.info("OSC Frame: "+oscFrameActive);
  // timestamp
  oscTimestampActive = config.getBooleanProperty("osc.timestamp", false);
  log.info("OSC Timestamp: "+oscTimestampActive);
  // x, y pos
  oscXposActive = config.getBooleanProperty("osc.x", false);
  oscYposActive = config.getBooleanProperty("osc.y", false);
  log.info("OSC X position: "+oscXposActive+", Y position: "+oscYposActive);
  // x, y velocity
  oscXveloActive = config.getBooleanProperty("osc.xvelo", false);
  oscYveloActive = config.getBooleanProperty("osc.yvelo", false);
  log.info("OSC X velocity: "+oscXveloActive+", Y velocity: "+oscYveloActive);
  // major, minor axis
  oscMajorAxisActive = config.getBooleanProperty("osc.majoraxis", false);
  oscMinorAxisActive = config.getBooleanProperty("osc.minoraxis", false);
  log.info("OSC Minor axis: "+oscMajorAxisActive+", Mayor axis: "+oscMinorAxisActive);
  // size
  oscSizeActive = config.getBooleanProperty("osc.size", false);
  log.info("OSC Size: "+oscSizeActive);
  // angle, angle in radians
  oscAngleActive = config.getBooleanProperty("osc.angle", false);
  oscAngleRadiansActive = config.getBooleanProperty("osc.angleradians", false);
  log.info("OSC Angle: "+oscAngleActive+", Angle in radians: "+oscAngleRadiansActive);
  

  // set up a remote location
  oscnet = new NetAddress("192.168.178.151", 9000);
  
  
  touchpad = new Touchpad(width, height);
  
  
  log.info("SETUP Ready");
}






/**
 * Draw
 */
void draw() {
  background(backgroundImage);
  noStroke();
  
  
  touchpad.draw();
  
  
  noStroke();
  fill(0);
  text("Port: "+outPort+
    "\nHost: "+outHost, 45, 50);
}





/**
 *
 * @param path The osc path. bsp. "/example/"
 * @param n The float value
 */
void oscmessage(String path, float n) {
  String tempPath = oscTrackpadName+"/"+path;
  
  // create a new OscMessage with an address pattern, in this case /test.
  OscMessage myOscMessage = new OscMessage(tempPath);
  
  // add a value (an integer) to the OscMessage
  myOscMessage.add(n);
  
  // send the OscMessage to the remote location. 
  OscP5.flush(myOscMessage, oscnet);
  
  log.info("OSC MESSAGE "+tempPath+n);
}

