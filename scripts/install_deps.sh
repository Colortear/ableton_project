#!/bin/bash

if [ ! -d "./lib" ]
then
    git clone https://github.com/google/googletest.git
    if [ ! -d "googletest" ]
    then
        exit
    fi
    mkdir googletest/build &&
        cd googletest/build &&
        cmake .. &&
        cd .. &&
        make &&
        cd .. &&
        cp -r googletest/build/lib/ . &&
        mkdir include/test/ &&
        cp -r googletest/googletest/include/gtest include/test/ &&
        cp -r googletest/googlemock/include/gmock include/test/ &&
        rm -rf googletest
fi
