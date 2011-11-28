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
import wrongPowder.gui.*;
import oscP5.*;
import netP5.*;



// Log
Log log;

// Config
Config config = new Config();
String configPath;

// GUI
IconButton oscactiveButton;
PImage oscactiveSend;
PImage oscactiveSendImage;

IconButton settingsButton;
IconButton consoleButton;

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
int oscOut;
int oscStateActive;
int oscFrameActive;
int oscTimestampActive;
int oscPositionActive;
int oscVelocityActive;
int oscMAxisActive;
int oscSizeActive;
int oscAngleActive;





/**
 * Setup
 */
void setup() {
  configPath = dataPath("")+"config.txt";
  // Load Property file
  config.loadStatic(configPath);
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
  
  
  // GUI
  oscactiveButton = new IconButton(this);
  oscactiveButton.init(loadImage("oscactive_on.png"), loadImage("oscactive_off.png"), 45, 50);
  oscactiveButton.status = 1;
  oscactiveSend = loadImage("oscactive_send.png");
  
  settingsButton = new IconButton(this);
  settingsButton.init(loadImage("settings_on.png"), loadImage("settings_off.png"), 90, 50);
  settingsButton.status = 1;
  consoleButton = new IconButton(this);
  consoleButton.init(loadImage("console_on.png"), loadImage("console_off.png"), 171, 50);
  consoleButton.status = 1;
  
  
  // Setting up osc host-, port
  outHost = config.getStringProperty("osc.outhost", "127.0.0.1");
  outPort = config.getIntProperty("osc.outport", 9000);
  log.info("OSC Output Host: "+outHost+", Output Port: "+outPort);
  
  // osc message master name
  oscTrackpadName = config.getStringProperty("osc.trackpadname", "magictrackpad");
  log.info("OSC Trackpad Name: "+oscTrackpadName);
  
  // oscOut, if 0 it send messages
  oscOut = config.getIntProperty("osc.out", 1);
  log.info("OSC Out: "+oscOut);
  
  // state
  oscStateActive = config.getIntProperty("osc.state", 1);
  log.info("OSC State: "+oscStateActive);
  // frame
  oscFrameActive = config.getIntProperty("osc.frame", 1);
  log.info("OSC Frame: "+oscFrameActive);
  // timestamp
  oscTimestampActive = config.getIntProperty("osc.timestamp", 1);
  log.info("OSC Timestamp: "+oscTimestampActive);
  // x, y pos
  oscPositionActive = config.getIntProperty("osc.pos", 1);
  oscPositionActive = config.getIntProperty("osc.position", 1);
  log.info("OSC X position: "+oscPositionActive);
  // x, y velocity
  oscVelocityActive = config.getIntProperty("osc.xvelo", 1);
  oscVelocityActive = config.getIntProperty("osc.velocity", 1);
  log.info("OSC Velocity: "+oscVelocityActive);
  // major, minor axis
  oscMAxisActive = config.getIntProperty("osc.maxis", 1);
  log.info("OSC Minor axis: "+oscMAxisActive);
  // size
  oscSizeActive = config.getIntProperty("osc.size", 1);
  log.info("OSC Size: "+oscSizeActive);
  // angle, angle in radians
  oscAngleActive = config.getIntProperty("osc.angle", 1);
  log.info("OSC Angle: "+oscAngleActive);
  

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
  text("Host: "+outHost + ", Port: "+outPort, 45, 120);
    
  // GUI
  oscactiveButton.draw();
  settingsButton.draw();
  consoleButton.draw();
  
  if(settingsButton.status == 0) {
    fill(0, 150);
    rect(55, 125, width-110, 420);
  }
  if(consoleButton.status == 0) {
    fill(0, 150);
    rect(55, 125, width-110, 420);
  // send osc signal icon
  if(oscOut == 0 && touchpad.send == true) {
    // if message sended, green point indicator
    noStroke();
    noFill();
    image(oscactiveSendImage, 60, 50);
    touchpad.send = false;
  }
}






/**
 * mousePressed
 */
void mousePressed() {
  oscactiveButton.mousePressed(mouseX, mouseY);
  settingsButton.mousePressed(mouseX, mouseY);
  consoleButton.mousePressed(mouseX, mouseY);
}





/**
 * keyPressed
 */
void keyPressed() {
  switch(key) {
    // oscOut
    case 'q':
      oscOut = intTrigger("osc.out", oscOut);
      break;
    
    // oscStateActive
    case '1':
      oscStateActive = intTrigger("osc.state", oscStateActive);
      break;
    
    // oscFrameActive
    case '2':
      oscFrameActive = intTrigger("osc.frame", oscFrameActive);
      break;
    
    // oscTimestampActive
    case '3':
      oscTimestampActive = intTrigger("osc.timestamp", oscTimestampActive);
      break;
    
    // oscPositionActive
    case '4':
      oscPositionActive = intTrigger("osc.position", oscPositionActive);
      break;
      
    // oscVelocityActive
    case '5':
      oscVelocityActive = intTrigger("osc.velocity", oscVelocityActive);
      break;
      
    // oscMAxisActive
    case '6':
      oscMAxisActive = intTrigger("osc.maxis", oscMAxisActive);
      break;
      
    // oscSizeActive
    case '7':
      oscSizeActive = intTrigger("osc.size", oscSizeActive);
      break;
      
    // oscAngleActive
    case '8':
      oscAngleActive = intTrigger("osc.angle", oscAngleActive);
      break;
  }
}





/**
 * intTrigger
 * Trigger a valuebetween 0 and 1.
 * 0 = true
 * 1 = false
 * 
 * @param property Config property name
 * @param i Trigger status
 * @return  
 */
int intTrigger(String property, int i) {
  int temp = 0;
  
  if(i == 0) {
    temp = 1;
  }
  else if(i == 1) {
    temp = 0;
  }
  else {
    println("Not correct keyEvent");
  }
  
  println(property+"; "+temp);
  config.setProperty(property, temp);
  // Save a copy to data folder.
  config.store(configPath);
  return temp;
}
