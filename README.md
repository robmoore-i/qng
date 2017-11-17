# qng

Simple png interface for q

## Requirements

- QHOME set, such that QHOME/l64/ is the directory containing
your 64 bit q binary
- libpng (I'm using 1.6.20, downloaded using package manager)
- zlib (I'm using 1.2.5, installed using package manager)
- Currently tested only on linux, should extend easily to *nix,
not sure about windows. (I'm using ubuntu 16.04)

## Build

```
you$ git clone https://github.com/robknows/qng.git
you$ cd qng
you$ ./build.sh
# Verifies environment variables
# Downloads dependencies
# Compiles C into QHOME/l64/
# Verifies that everything is okay
# Moves png.q into QHOME so you can load it from any q session
you$ q64
q)\l png.q
q)key`
`q`Q`h`j`o`png
q) // And away you go
```

## Functions

- libpngversion
- checkpng
- dimensions
- pixels

### Demonstration
```
$rob q png.q
q).png.libpngversion[]
"1.6.20"
q).png.checkpng `:images/blueblock.png
1b
q).png.checkpng `:README.md
0b
q).png.dimensions `:images/dustin.png
width | 840
height| 884
q)pixels:.png.pixels `:images/dustin.png
q)pixels
r| 14  14  14  14  14  14  14  14  14  14  14  14  14  14  14  14 14 14 14 14..
g| 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13..
b| 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14..
a| 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 25..
q)pixels `r
14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14..
14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14..
14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14..
14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14 14..
13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13..
13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 14 14 14 14 14 14..
13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 13 16 16 16 16 16 16..
..
q)count pixels[`r]
884
q)count first pixels[`r]
840
```
## Performance

qng: 162ms
```
q)\t .png.pixels `:images/dustin.png
92
q)
```
scipy: 120ms
```
>>> import scipy.misc as scpm
>>> import time
>>> def getReadTime():
...     start = time.time()
...     scpm.imread('dustin.png')
...     end = time.time()
...     print(end - start)
...
>>> getReadTime()
0.1199188232421875
>>>
```

`¯\_(ツ)_/¯`


## Exception Handling

Throws 'png if you give it non-pngs
