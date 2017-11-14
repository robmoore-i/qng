#!/bin/bash

# Note:
# I'm not sure how many of these are necessary, but I have 1TB disk so I don't care.
# If this isn't the case for you, use a docker container to figure out which ones are
#   truly necessary, and if you let me know which they are I'll update this file.

# zlib for libpng
sudo apt install zlib1g zlib1g-dev

# libpng16
sudo apt install libpng16-16 libpng16-dev libpng16-devtools libpng16-tools

exit 0
