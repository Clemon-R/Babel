#!/bin/bash

######################################################################################
### Execute this script once. It gonna pull required dependencies for this project ###
######################################################################################

echo -e "adding needed conan remotes..."
available_sources="$(conan remote list)"

if ! [[ $available_sources = *"bincrafters"* ]]; then
    conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
    echo -e "added source: bincrafters"
fi

echo -e "installing into /build ..."
mkdir -p ../build && cd ../build && conan install --build=missing .. && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release