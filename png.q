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

// === Libpng ===
\d .libpng

libpngk:{`libpngk 2: (x;1)}
version:libpngk `version
k)checkpng:{(libpngk `checkpng) `$1_$:x}

// === Wheel reinvention (temporary) ===

\d .qng

// Every valid PNG file starts with the bytes 0x89504e470d0a1a0a
pngsigniature:(0x89) , ("x"$"PNG") , "x"$/:13 10 26 10
checksigniature:{[bytes]pngsigniature~8#bytes}
dropsigniature:{8_x}

takechunk:{[bytes](12+0x0 sv 4#bytes)#bytes}
dropchunk:{[bytes](12+0x0 sv 4#bytes)_bytes}
parsechunk:{[chunk]`length`type`data`crc!(0x0 sv 4#chunk;"c"$4_8#chunk;-4_8_chunk;-4#chunk)}
parseIHDR:{[ihdr]
    if[99h=type ihdr;ihdr:0x000000,raze value "x"$ihdr];
    components:@[("xcxxiiiiix")$'(0 4;4 4;8 4;12 4;16 1;17 1;18 1;19 1;20 1;21 4) sublist\: ihdr;0 2 3;{0x0 sv x}];
    if[13i<>components 0;'ihdrlength];
    if[not "IHDR"~components 1;'notihdr];
    `width`height`bitdepth`colourtype`compression`filter`interlace`crc!2 8 sublist @[components;4 5 6 7 8;first]}

processverbose:{[fh]
    -1 "- Reading `:blueblock.png bytes: ";
    -1 raze string bytes:read1 fh;
    -1 "- Checking pngheader: ",string checksigniature bytes;
    -1 "- Reading IHDR: ";
    show ihdr:parseIHDR takechunk nosigniature:dropsigniature bytes;
    -1 "- Parsing all chunks: ";
    show chunks:parsechunk each {not 0x00000000~4#x} dropchunk\ nosigniature;
    chunks}
