/**
 * MagicTrackpadOsc is developed by Paul Vollmer (wrong-entertainment.com)
 * Based on http://kenai.com/projects/macmultitouch/
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

import com.alderstone.multitouch.mac.touchpad.*;





class Touchpad implements Observer {

  public boolean send;
  private static final int MAX_FINGER_BLOBS = 10;
  private int width, height;

  TouchpadObservable tpo;
  Finger blobs[] = new Finger[MAX_FINGER_BLOBS];
  
  
  // multitouch variables
  int id;
  //FingerState state = f.getState();
  int frame;
  int timestamp;
  float x;
  float xVelo;
  float y;
  float yVelo;
  float majorAxis;
  float minorAxis;
  float size;
  int angle;
  float rAngle;
  



  /**
   * Constructor
   */
  public Touchpad(int width, int height) {	
    this.width  = width;
    this.height = height;
    tpo = TouchpadObservable.getInstance();
    tpo.addObserver(this);
  }




  /**
   * Magic Trackpad Multitouch update event 
   */
  public void update(Observable obj, Object arg) {
    // The event 'arg' is of type: com.alderstone.multitouch.mac.touchpad.Finger
    Finger f = (Finger) arg;
    
    // check if osc.out = 0, send osc message
    if(oscOut == 0) {
      // id of finger
      id = f.getID();
      FingerState state = f.getState();
      frame = f.getFrame();
      timestamp = (int)f.getTimestamp();
      x = f.getX();
      xVelo = f.getXVelocity();
      y = f.getY();
      yVelo = f.getYVelocity();
      majorAxis = f.getMajorAxis();
      minorAxis = f.getMinorAxis();
      size = f.getSize();
      angle = f.getAngle();
      rAngle = f.getAngleInRadians();
    }
    
    
    /*if (f != null && f.getState() == FingerState.PRESSED) { 
      //println(FingerState.PRESSED);
    }
    if (f != null && f.getState() == FingerState.RELEASED) { 
      //println(FingerState.RELEASED);
    }*/
    
    if (id <= MAX_FINGER_BLOBS)
      blobs[id]= f;
  }	





  /**
   * draw
   */
  public void draw() {
    for (int i=0; i<MAX_FINGER_BLOBS;i++) {
      Finger f = blobs[i];
      if (f != null && f.getState() == FingerState.PRESSED) {
        
        // check if osc.out = 0, send osc message
        if(oscOut == 0) {
          if(oscFrameActive == 0) oscmessage(""+id+"/frame/", frame);
          if(oscTimestampActive == 0) oscmessage(""+id+"/timestamp/", timestamp);
          if(oscPositionActive == 0) oscmessage(""+id+"/x/", x);
          if(oscPositionActive == 0) oscmessage(""+id+"/y/", y);
          if(oscVelocityActive == 0) oscmessage(""+id+"/xvelo/", xVelo);
          if(oscVelocityActive == 0) oscmessage(""+id+"/yvelo/", yVelo);
          if(oscMAxisActive == 0) oscmessage(""+id+"/majoraxis/", majorAxis);
          if(oscMAxisActive == 0) oscmessage(""+id+"/minoraxis/", minorAxis);
          if(oscSizeActive == 0) oscmessage(""+id+"/size/", size);
          if(oscAngleActive == 0) oscmessage(""+id+"/angle/", angle);
          if(oscAngleActive == 0) oscmessage(""+id+"/rangle/", rAngle);
        }
        
        int x     = (int) ((width-80)  * (f.getX()));
        int y     = (int) ((height-165) * (1-f.getY()));
        int xsize = (int) (10*f.getSize() * (f.getMajorAxis()/2));
        int ysize = (int) (10*f.getSize() * (f.getMinorAxis()/2));
        int ang   = f.getAngle();


        pushMatrix();  
        translate((x+(45))-xsize/2, (y+125)-ysize/2);

        pushMatrix();
        rotate(radians(-ang));  // convert degrees to radians
        noStroke();
        fill(0, 155, 255);
        ellipse(0, 0, xsize, ysize);
        popMatrix();

        stroke(255);
        noFill();
        line(-5, 0, 5, 0);
        line(0, -5, 0, 5);

        fill(0);
        text("ID: "+(i+1), 5, -5);
        
        popMatrix();
        
        send = true;
      }
    }
  }
  
  
  
  
  /**
 *
 * @param path The osc path. bsp. "/example/"
 * @param n The float value
 * @return osc event
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

/**
 *
 * @param path The osc path. bsp. "/example/"
 * @param n The float value
 * @return osc event
 */
void oscmessage(String path, String s) {
  String tempPath = oscTrackpadName+"/"+path;
  
  // create a new OscMessage with an address pattern, in this case /test.
  OscMessage myOscMessage = new OscMessage(tempPath);
  
  // add a value (an string) to the OscMessage
  myOscMessage.add(s);
  
  // send the OscMessage to the remote location. 
  OscP5.flush(myOscMessage, oscnet);
  
  log.info("OSC MESSAGE "+tempPath+s);
}





}

