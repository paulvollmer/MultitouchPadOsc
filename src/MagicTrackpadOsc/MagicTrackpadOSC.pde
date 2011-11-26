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
 * @modified    2011.11.25
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
String oscTrackpadName;



/**
 * Setup
 */
void setup() {
  // Load Property file
  config.loadStatic(dataPath("")+"config.txt");
  config.list();

  log = new Log(this);
  log.init();
  log.info("SETUP Starts");

  size(593, 600);
  smooth();
  int tempFramerate = config.getIntProperty("app.framerate", 30);
  frameRate(tempFramerate);
  log.info("SETUP Framerate: "+tempFramerate);

  // Load background image
  backgroundImage = loadImage("MagicTrackpad-01.png");

  // Set osc host-, oortnumber
  outHost = config.getStringProperty("osc.outhost", "127.0.0.1");
  outPort = config.getIntProperty("osc.outport", 9000);
  log.info("OSC Output Host: "+outHost+", Output Port: "+outPort);
  oscTrackpadName = config.getStringProperty("osc.trackpadname", "magictrackpad");
  log.info("OSC Trackpad Name: "+oscTrackpadName);

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

