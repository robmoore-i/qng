#!/bin/bash
sharedlibname="$QHOME/l64/$(basename $1 .c).so"
cc -I. -fPIC -shared -o $sharedlibname $1 -lpng16
exit 0
