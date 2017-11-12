#!/bin/bash
sharedlibname="$QHOME/l32/$(basename $1 .c).so"
cc -I. -fPIC -shared -o $sharedlibname $1
