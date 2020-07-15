# ableton_project

This is my solution to the third prompt which details a program for placing warp markers between
a beat and timestamp timeline.

# build

Run `make` in the root directory.

# build test

To build the units tests, the gtest framework is required. If it is installed on the host machine
then there should be no need to install the dependency. There is a script for pulling and installing
gtest as a static library in the scripts folder and can be run by calling `make install_deps`.
Once the dependencies are in place, to build the tests simply run `make test` and it will build the
warpedrecord_test binary.

# usage

`./warpedrecord`

The binary can receive input manually until sent `SIGINT` or by piping in with `cat`.
