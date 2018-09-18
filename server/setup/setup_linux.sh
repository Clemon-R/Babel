#!/bin/bash

######################################################################################
### Execute this script once. It gonna pull required dependencies for this project ###
######################################################################################

echo -e "installing into /build ..."
mkdir -p ../build && cd ../build && conan install --build=missing .. && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release