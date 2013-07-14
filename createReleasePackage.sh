#! /bin/bash

SCRIPT_FOLDER=`dirname $0`
TEMP_PATH=$SCRIPT_FOLDER/bin/MultitouchPadOsc


echo "\033[7m\033[1m"
echo "Start running script\033[0m\033[7m"

echo "Create temporary folder"
mkdir $TEMP_PATH

echo "Copy Application to temporary folder"
cp -R $TEMP_PATH.app $TEMP_PATH/MultitouchPadOsc.app

echo "Making link to Applications dir"
ln -s /Applications $TEMP_PATH/Applications

echo "Copy License"
cp -R $SCRIPT_FOLDER/LICENSE.txt $TEMP_PATH/LICENSE.txt

echo "Generate .dmg file"
hdiutil create -format UDZO -srcfolder $TEMP_PATH $SCRIPT_FOLDER/bin/MultitouchPadOsc.dmg

echo "Delete temporary folder"
rm -rf $TEMP_PATH


echo "\033[0m"