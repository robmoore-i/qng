# qng

- simple png interface for l64 q

## Requirements:

- QHOME set, such that QHOME/l64/ is the directory containing your 64 bit q bianry
- libpng (I'm using 1.6.20, downloaded using ubuntu package manager)
- zlib (I'm using 1.2.5, installed using package manager)

## Build:

Since I don't know exactly which libraries were necessary in the end to make it work,
the build script is not at all conservative with the packages it downloads (I basically
did sudo apt install zlib* libpng16*).
