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
- write

### Demonstration
```
$rob q64 png.q
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
q)r:10#enlist 10#0
q)g:10#enlist 10#255
q)b:10#enlist 10#0
q).png.write[`:littleGreenSquare.png;`r`g`b!(r;g;b)]
q)
```
## Performance

- Measure time to read all the pngs in images/

qng: 102ms
```
q)\t .png.pixels each {` sv/: x,/:key[x]} `:images
102
q)
```
scipy: 106ms
```
>>> import scipy.misc as scpm
>>> import os
>>> import time
>>> imagepaths = [os.path.join('images', f) for f in os.listdir('images')]
>>> def timeAllReads():
...     start=time.time()
...     for png in imagespaths:
...             scpm.imread(png)
...     t=time.time()-start
...     print(t)
... 
>>> timeAllReads()
0.10645079612731934
>>>
```

`¯\_(ツ)_/¯`


## Exception Handling

Throws '{filename} for a {filename} that doesn't exist.
Throws 'png if you give it non-pngs
There are some other error cases, but I've never seen them and I don't know
why they would happen other than some kind of corruption of the png file being
read. They are 'png_ptr 'info_ptr and 'setjmp.
