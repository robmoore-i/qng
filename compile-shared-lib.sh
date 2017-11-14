#!/bin/bash
sharedlibname="$QHOME/l64/$(basename $1 .c).so"
cc -O1 -I. -fPIC -shared -o $sharedlibname $1 -lpng16
exit 0
