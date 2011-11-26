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
 * @modified    2011.11.25
 * @version     0.1.0
 */

import com.alderstone.multitouch.mac.touchpad.*;





class Touchpad implements Observer {
  
  private static final int MAX_FINGER_BLOBS = 10;
  private int width, height;
  
  TouchpadObservable tpo;
  Finger blobs[] = new Finger[MAX_FINGER_BLOBS];





  public Touchpad(int width, int height) {	
    this.width  = width;
    this.height = height;
    tpo = TouchpadObservable.getInstance();
    tpo.addObserver(this);
  }





  // Magic Trackpad Multitouch update event 
  public void update(Observable obj, Object arg) {
    // The event 'arg' is of type: com.alderstone.multitouch.mac.touchpad.Finger
    Finger f = (Finger) arg;
    
    
    int angle = f.getAngle();
    float rAngle = f.getAngleInRadians();
    int frame = f.getFrame();
    int id = f.getID();
    float majorAxis = f.getMajorAxis();
    float minorAxis = f.getMinorAxis();
    float size = f.getSize();
    FingerState state = f.getState(); 
    double timestamp = f.getTimestamp();
    float x = f.getX();
    float xVelo = f.getXVelocity();
    float y = f.getY();
    float yVelo = f.getYVelocity();
    
    println("ID: "+id+
            ", Frame: "+frame+
            ", Timestamp: "+(int)timestamp+
            ", State: "+state+
            ", X: "+x+
            ", Y: "+y+
            ", X-Velo: "+xVelo+
            ", Y-Velo: "+yVelo+
            ", Angle: "+angle+
            ", Size: "+size+
            ", MajorAxis: "+majorAxis+
            ", MinorAxis: "+minorAxis);
    
   if (f != null && f.getState() == FingerState.PRESSED) { 
     println(FingerState.PRESSED);
   }
   if (f != null && f.getState() == FingerState.RELEASED) { 
     println(FingerState.RELEASED);
   }
    
   if (id <= MAX_FINGER_BLOBS)
     blobs[id-1]= f;
  }	





  public void draw() {
    for (int i=0; i<MAX_FINGER_BLOBS;i++) {
      Finger f = blobs[i];
      if (f != null && f.getState() == FingerState.PRESSED) {

        int x     = (int) (width  * (f.getX()));
        int y     = (int) (height * (1-f.getY()));
        int xsize = (int) (10*f.getSize() * (f.getMajorAxis()/2));
        int ysize = (int) (10*f.getSize() * (f.getMinorAxis()/2));
        int ang   = f.getAngle();

        
        pushMatrix();  
          translate(x-xsize/2, y-ysize/2);
      
          pushMatrix();
            rotate(radians(-ang));  // convert degrees to radians
            noStroke();
            fill(255);
            ellipse(0, 0, xsize, ysize);
          popMatrix();
          
          stroke(255, 0, 0);
          noFill();
          line(-5, 0, 5, 0);
          line(0, -5, 0, 5);
          
          fill(255, 0, 0);
          text(""+i, 5, -5);
        popMatrix();
      }
    }
  }
  
}

