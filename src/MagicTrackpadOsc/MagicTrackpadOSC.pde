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
PImage oscactiveSendImage;

IconButton settingsButton;
String settingsContent;

IconButton consoleButton;
// Arraylist to store console messages
ArrayList<String> consoleContent = new ArrayList<String>();
// max size of arraylist
int consoleContentSize = 27;


// Osc
NetAddress oscnet;
// osc host, port
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

// Magic Trackpad
Touchpad touchpad;

// background image
PImage backgroundImage;

PFont font;





/**
 * Setup
 */
void setup() {
  // Initialize config class
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
  this.frame.setTitle("test");
  
  // Load background image
  backgroundImage = loadImage("MagicTrackpad-01.png");
  
  font = createFont("Courier", 12);
  textFont(font);
  
  // Setting up osc host-, port
  outHost = config.getStringProperty("osc.outhost", "127.0.0.1");
  outPort = config.getIntProperty("osc.outport", 9000);
  log.info("OSC Output Host: "+outHost+", Output Port: "+outPort);
  // set up a remote location
  oscnet = new NetAddress("192.168.178.116", 9000);
  
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
  oscPositionActive = config.getIntProperty("osc.position", 1);
  log.info("OSC X position: "+oscPositionActive);
  // x, y velocity
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
  
  
  
  // GUI
  oscactiveButton = new IconButton(this);
  oscactiveButton.init(loadImage("oscactive_on.png"), loadImage("oscactive_off.png"), 54, 50);
  oscactiveButton.status = oscOut;
  println(oscOut+", oscactiveButton: "+oscactiveButton.status);
  oscactiveSendImage = loadImage("oscactive_send.png");
  
  settingsButton = new IconButton(this);
  settingsButton.init(loadImage("settings_on.png"), loadImage("settings_off.png"), 90, 50);
  settingsButton.status = 1;
  settingsContent = "OSC SETTINGS\n"+
                    "\n"+
                    "   master name              (change at config file)\n"+
                    "   state active             (shortcut 1)\n"+
                    "   frame active             (shortcut 2)\n"+
                    "   timestamp active         (shortcut 3)\n"+
                    "   x, y position active     (shortcut 4)\n"+
                    "   x, y velocity active     (shortcut 5)\n"+
                    "   minor/major axis active  (shortcut 6)\n"+
                    "   size active              (shortcut 7)\n"+
                    "   angle active             (shortcut 8)";
                 
  
  consoleButton = new IconButton(this);
  consoleButton.init(loadImage("console_on.png"), loadImage("console_off.png"), 171, 50);
  consoleButton.status = 1;
  
  
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
  text("Host: "+outHost + ", Port: "+outPort, 54, 110);
  
  // GUI
  oscactiveButton.draw();
  settingsButton.draw();
  consoleButton.draw();
  
  
  if(settingsButton.status == 0) {
    consoleButton.status = 1;
   
    // ground
    noStroke();
    fill(0, 150);
    rect(55, 125, width-110, 420);
    
    fill(255);
    text(settingsContent, 60, 150);
    
    checkEllipse(oscStateActive,     65, 192);
    checkEllipse(oscFrameActive,     65, 207);
    checkEllipse(oscTimestampActive, 65, 222);
    checkEllipse(oscPositionActive,  65, 237);
    checkEllipse(oscVelocityActive,  65, 252);
    checkEllipse(oscMAxisActive,     65, 267);
    checkEllipse(oscSizeActive,      65, 282);
    checkEllipse(oscAngleActive,     65, 297);
  }
  
  if(consoleButton.status == 0) {
    settingsButton.status = 1;
    
    // ground
    noStroke();
    fill(0, 150);
    rect(55, 125, width-110, 420);
    
    // console text
    fill(#1CF6FF);
      for (int i = consoleContent.size()-1; i >= 0; i--) {
        text(consoleContent.get(i), 60, 145+(i*15));
      }
  }
  
  
  // send osc signal icon
  if(oscOut == 0 && touchpad.send == true) {
    // if message sended, green point indicator
    noStroke();
    noFill();
    image(oscactiveSendImage, 60, 50);
    touchpad.send = false;
  }
}






void checkEllipse(int var, int x, int y) {
  if(var == 0) {
    fill(0, 255, 0);
  }
  else {
    fill(255, 0, 0);
  }
  ellipse(x, y, 10, 10);
}





/**
 * mousePressed
 */
void mousePressed() {
  // GUI
  oscactiveButton.mousePressed(mouseX, mouseY);
  oscOut = oscactiveButton.status;
  config.setProperty("osc.out", oscOut);
  
  settingsButton.mousePressed(mouseX, mouseY);
  consoleButton.mousePressed(mouseX, mouseY);
  
  
  config.store(configPath);
}





/**
 * keyPressed
 */
void keyPressed() {
  switch(key) {
    // oscOut
    /*case 'q':
      oscactiveButton.status = oscOut;
      oscOut = intTrigger("osc.out", oscOut);
      break;
    */
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
