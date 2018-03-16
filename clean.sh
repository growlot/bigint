#!/bin/bash

BIN=`pwd`"/output"
BIGINT=bigint

rm -rf $BIN

rm -rf autom4te.cache

rm -f AUTHORS NEWS README ChangeLog
rm -f COPYING INSTALL
rm -f aclocal.m4
rm -f configure
rm -f depcomp
rm -f install-sh
rm -f missing
rm -f libtool
rm -f ltmain.sh
rm -f stamp-h1
rm -f compile

find . -name 'config.*' -exec rm -fv {} \;
find . -name *.o -exec rm -fv {} \;
find . -name *.a -exec rm -fv {} \;
find . -name *.lo -exec rm -fv {} \;
find . -name *.la -exec rm -fv {} \;
find . -name Makefile -exec rm -fv {} \;
find . -name Makefile.in -exec rm -fv {} \;
find . -name *~ -exec rm -fv {} \;

rm -f $BIGINT/bigint



