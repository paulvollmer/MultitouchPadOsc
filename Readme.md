#MagicTrackpadOsc#
* * *  
  
MagicTrackpadOsc (version 0.1.0 codename fTouch) is developed by: [wrong-entertainment](http://wrong-entertainment.com)  
Copyright 2011 Paul Vollmer   
  
The wrongPowder Project Page is Hosted at http://wrongentertainment.github.com/MagicTrackpadOsc/  
Check out for New released Version at https://github.com/WrongEntertainment/MagicTrackpadOsc  
  
This file is part of MagicTrackpadOsc.  
   
###Description  

<img src="http://www.wrong-entertainment.com/code/magictrackpadosc/magictrackpadosc_01.jpg" width=250 >
<img src="http://www.wrong-entertainment.com/code/magictrackpadosc/magictrackpadosc_02.jpg" width=250 >
<img src="http://www.wrong-entertainment.com/code/magictrackpadosc/magictrackpadosc_03.jpg"
  
MagicTrackpadOSC ist eine Applikation für das Magic Trackpad (Apple) mit dem man die eingehenden Multitouch Events  
als OSC-Message versenden kann. Dadurch ist es möglich,das Trackpad als Controller zu verwenden.  
Die MagicTrackpadOSC Applikation ist mit dem Betriebssystem MacOS 10.5+ zu benutzen, damit ein valider Support 
gewährleistet wird.  
  
###User Guide  

<img src="http://www.wrong-entertainment.com/code/magictrackpadosc/magictrackpadosc_01.jpg">  
Application standart screen  
<img src="http://www.wrong-entertainment.com/code/magictrackpadosc/magictrackpadosc_02.jpg">  
Application settings  
<img src="http://www.wrong-entertainment.com/code/magictrackpadosc/magictrackpadosc_03.jpg">  
Application console

Auswählbare OSC-Messages:  

    # TRACKPADNAME: settings name osc.trackpadname
    # FINGER-ID: the finger id (from 0 to 20) 

    TRACKPADNAME/FINGER-ID/frame
    TRACKPADNAME/FINGER-ID/timestamp 
    TRACKPADNAME/FINGER-ID/x 
    TRACKPADNAME/FINGER-ID/y 
    TRACKPADNAME/FINGER-ID/xvelocity 
    TRACKPADNAME/FINGER-ID/yvelocity 
    TRACKPADNAME/FINGER-ID/majoraxis 
    TRACKPADNAME/FINGER-ID/minoraxis 
    TRACKPADNAME/FINGER-ID/size 
    TRACKPADNAME/FINGER-ID/angle 
    TRACKPADNAME/FINGER-ID/rangle  


Build with [Processing](http://www.processing.org)  

* * *

###Download###  
![Github zip download](https://github.com/images/modules/download/zip.png "MagicTrackpadOsc Github download zip") 
![Github tar download](https://github.com/images/modules/download/tar.png "MagicTrackpadOsc Github download tar")  
You can download this project in either [zip](https://github.com/WrongEntertainment/MagicTrackpadOsc/zipball/master) or [tar](https://github.com/WrongEntertainment/MagicTrackpadOsc/tarball/master) formats.
You can also clone the project with [Git](http://git-scm.com/) by running.

    $ git clone git://github.com/WrongEntertainment/MagicTrackpadOsc

* * *

###Installation###

**License**  
GNU Lesser General Public License  
**Install**  
Mac Java Application, no installation needed.  
**Dependencies**  
Mac OS 10.5+  

* * *

###Contact###

Mail: [Paul Vollmer](paul.vollmer@fh-potsdam.de)
Url: [wrong-entertainment.com](http://www.wrong-entertainment.com)
Github: [github.com/WrongEntertainment](http://wrongentertainment.github.com/MagicTrackpadOsc)

* * *

###License  

MagicTrackpadOsc 0.1.0  
[github.com/MagicTrackPad](http://wrongentertainment.github.com/MagicTrackpadOsc)  
  
Copyright (c) 2011 Paul Vollmer  
  
MagicTrackpadOsc is free software; you can redistribute it and/or  
modify it under the terms of the GNU Lesser General Public  
License as published by the Free Software Foundation; either  
version 2.1 of the License, or (at your option) any later version.  
  
MagicTrackpadOsc is distributed in the hope that it will be useful,  
but WITHOUT ANY WARRANTY; without even the implied warranty of  
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  
Lesser General Public License for more details.  
  
You should have received a copy of the GNU Lesser General  
Public License along with MagicTrackpadOsc; if not, write to the  
Free Software Foundation, Inc., 59 Temple Place, Suite 330,  
Boston, MA  02111-1307  USA  
  
Author      Paul Vollmer  
Modified    2011.12.03  
Version     0.1.0