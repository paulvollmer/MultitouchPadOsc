# [MultitouchPadOsc](http://paulvollmer.github.io/MultitouchPadOsc/)  
  
## General Information  
The MultitouchPadOsc application checks the incomming Multitouch Events and send them as an osc-message.  
It gives the possibility to use a Multitouch Pad as a control-device via osc protocol.  
  
The Project Page is Hosted at http://paulvollmer.github.com/MultitouchPadOsc/  
Check out for New released Version at https://github.com/paulvollmer/MultitouchPadOsc/releases  
  
The application is using the [Bitstream Vera](http://ftp.gnome.org/pub/GNOME/sources/ttf-bitstream-vera/1.10/) font.  
Build with [openFrameworks](http://www.openframeworks.cc)  
Third Party Code Additional copyright notices and license terms applicable to portions of the Software are set forth in the THIRDPARTYLICENSEREADME.txt file.  
  
  
MultitouchPadOsc (version 0.1.31 codename TouchDown) is developed by:  
Paul Vollmer [paulvollmer.net](http://paulvollmer.net)  
Copyright (c) 2011-2013 Paul Vollmer, paulvollmer.net  
  

**Platform**  
Mac OS  
**Dependencies**  
Software: Mac OS 10.6  
Hardware: MacBook, MacBook Pro with a Multitouch Trackpad or an Magic Trackpad.
  
**Issues and Bugs**  
You can find a list of all known bugs at [GitHub](https://github.com/paulvollmer/multitouchpadosc/issues). Please report if you find an unknown bug.  
  
  
## Development  
Download openFrameworks and clone the Repository by running:

    bash <(curl -s https://raw.github.com/paulvollmer/MultitouchPadOsc/bootstrap.sh)

The following openFrameworks addons are embed as submodule.  

[ofxUI](https://github.com/rezaali/ofxUI)  
[ofxModifierKeys](https://github.com/satoruhiga/ofxModifierKeys)  
[ofxXmlDefaultSettings](https://github.com/wrongentertainment/ofxXmlDefaultSettings)  
  
  
## Changelog  
A detailed changelog, intended for programmers.  

  0.1.33
Fixed Links
  
- 0.1.32  
Fixed osc array x-, y-position Bug  
Added openFrameworks addons as submodule  
Added bootstrap script for cloning the repository and downloading openFrameworks  

- 0.1.31  
Fixed Bug Entering port -> Crash  
Fixed Bug Wrong osc message on finger added/removed  
Fixed Bug Array is not being send  
  
- 0.1.3  
Changes at OSC messages  
Added Resize Window Mode  
Added GUI osc host/port textfield  
Added Finger Information  
  
- 0.1.2  
Changes at default xml settings, changes at gui.  
  
- 0.1.1  
Lot of changes at usability  
  
- 0.1.0  
Beginning MultitouchPadOsc App, first test  
  
  
## Author
MultitouchPadOsc is developed by Paul Vollmer    
Check out for new release at https://github.com/paulvollmer/MultitouchPadOsc/  
  
Url: http://paulvollmer.net  
Github: http://www.github.com/paulvollmer  
  
  
## License  
MultitouchPadOsc is Licensed under [MIT License](LICENSE.txt)  
