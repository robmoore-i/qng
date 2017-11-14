# qng

Simple png interface for q

## Requirements:

- QHOME set, such that QHOME/l64/ is the directory containing your 64 bit q binary
- libpng (I'm using 1.6.20, downloaded using ubuntu package manager)
- zlib (I'm using 1.2.5, installed using package manager)

## Build:

Since I don't know exactly which libraries were necessary in the end to make it work,
the build script is not at all conservative with the packages it downloads (I basically
did sudo apt install zlib* libpng16*).

## Functions:

- libpngversion
- checkpng
- dimensions
- pixels

### Demonstration:
```
$rob q png.q
q).png.libpngversion[]
"1.6.20"
q).png.checkpng `:blueblock.png
1b
q).png.checkpng `:README.md
0b
q).png.dimensions `:dustin.png
width | 840
height| 884
q)pixels:.png.pixels `:dustin.png
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
q)\t .png.pixels `:dustin.png
162
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
¯\_(ツ)_/¯

## Exception Handling

Will throw 'png if you give it non-pngs
