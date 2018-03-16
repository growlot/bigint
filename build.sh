#!/bin/bash

BIN=`pwd`"/output"

touch AUTHORS NEWS README ChangeLog
sh autogen.sh
./configure --prefix=$BIN
make
make install 

