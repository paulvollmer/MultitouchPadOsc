#!/bin/bash

# erstelle die main addon directory
mkdir $(dirname $0)/addons

# function für den script download des addons
function func () {
	SHELL_SCRIPT_PATH="$(dirname $0)/addons/temp.sh"   # create a variable to store script file path.	
	curl -o $SHELL_SCRIPT_PATH $1                      # download the addon script
	source $SHELL_SCRIPT_PATH                          # run the script
	rm $SHELL_SCRIPT_PATH                              # delete the script
}

# die function "func" ausführen
func https://raw.github.com/gist/3658304/download_ofxXmlDefaultSettings
# move folder to addon folder
mv $(dirname $0)/ofxXmlDefaultSettings $(dirname $0)/addons