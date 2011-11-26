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

import wrongPowder.io.Config;
import oscP5.*;
import netP5.*;

Config config = new Config();;
OscP5 osc;
NetAddress net;

PImage backgroundImage;
Touchpad touchpad;





/**
 * Setup
 */
void setup() {
  // Load Property file
  config.loadStatic(dataPath("")+"config.txt");
  config.list();
  
  size(593, 600);
  smooth();
  
  // Load background image
  backgroundImage = loadImage("MagicTrackpad-01.png");
  
  // start oscP5, listening for incoming messages at port XXXX
  osc = new OscP5(this, 8000);
  
  // myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
  // an ip address and a port number. myRemoteLocation is used as parameter in
  // oscP5.send() when sending osc packets to another computer, device, 
  // application. usage see below. for testing purposes the listening port
  // and the port of the remote location address are the same, hence you will
  // send messages back to this sketch.
  net = new NetAddress("192.168.178.151", 8000);
  
  touchpad = new Touchpad(width, height);
}



/**
 * Draw
 */
void draw() {
  background(backgroundImage);
  noStroke();
  
  touchpad.draw();
}

