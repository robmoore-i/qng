// === Libpng ===
\d .png

libpngk:{`libpngk 2: (x;1)}
k)fromfh:{{x `$1_$:y}[libpngk x;]}

// Returns the version string of libpng
libpngversion:libpngk `libpngversion

// Returns 1b for a valid png, 0b for an invalid png
checkpng:fromfh `checkpng

// Returns a two element I list of (width;height)
dimensions:{`width`height!fromfh[`dimensions] x}

// Returns a dictionary of `r`g`b`a!(red;green;blue;alpha)
// where each value is a height*width matrix of pixel values (aka a list of rows).
pixels:{`r`g`b!"h"$/:dimensions[x][`width] cut/: fromfh[`readpng] x}

write:{[fn;w;h;rbuf;gbuf;bbuf]
    f:`libpngk 2: (`writepng;6);
    f[`$1_string fn;"i"$w;"i"$h;"h"$rbuf;"h"$gbuf;"h"$bbuf]}

// === Note on PNGs ===

// === PNG FILE FORMAT ===
// 8 byte signiature 0x89504e470d0a1a0a
// 13 byte IHDR chunk (width;height;bitdepth;colourtype;compressionmethod;filtermethod;interlacemethod)
// Optional chunks
// IDAT chunks
// IEND chunk

// === CHUNK FORMAT ===
// Chunks are (datalength;chunktype;   data     ;   crc).
// with sizes (4 bytes   ;4 bytes  ;??? bytes;4 bytes).
// The 4 critical chunks are IHDR (header), PLTE (palette), IDAT (data), IEND (eof).
// If the first letter of the chunktype is upper case, then the chunk is considered critical.
// If a critical chunk's crc fails, abort reading the file, or supply an appropriate warning.
// If a non-critical chunk's crc fails or it's not understood, it can just be discarded.
