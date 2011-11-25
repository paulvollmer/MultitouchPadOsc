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

Touchpad touchpad;





void setup() {
  size(800, 600);
  smooth();
  
  touchpad = new Touchpad(width, height);
}





void draw() {
  background(0);
  noStroke();
  
  touchpad.draw();
}

