#!/usr/bin/env bash

echo "--> download openFrameworks v0073"
curl http://www.openframeworks.cc/versions/v0073/of_v0073_osx_release.zip -o openFrameworks_0073.zip

echo "--> unzip openFrameworks"
unzip openFrameworks_0073.zip

echo "--> rename folder and delete zip file"
mv of_v0073_osx_release MultitouchPadOsc_of
rm openFrameworks_0073.zip

echo "--> clone MultitouchPadOsc repo"
cd MultitouchPadOsc_of/apps/myApps
git clone git@github.com:WrongEntertainment/MultitouchPadOsc.git
