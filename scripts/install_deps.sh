#!/bin/bash

cd ..
if [ ! -d "./lib" ]
then
    git clone https://github.com/google/googletest.git
    if [ ! -d "googletest" ]
    then
        exit
    fi
    mkdir googletest/build
    cmake googletest
    cd googletest
    make
    cd ..
    mkdir lib
    cp -r googletest/build/lib/ .
    mkdir include/tests/
    cp -r googletest/googletest/include/gtest include/tests/
    cp -r googletest/googlemock/include/gmock include/tests/
    rm -rf googletest
fi
