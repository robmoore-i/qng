#include "k.h"
#include<stdlib.h>
#include<png.h>

K version(K x) {
    return kp(PNG_LIBPNG_VER_STRING);
}

//K checkpng(K x) {
//    C* fn = kC(x);
//
//    FILE *fp = fopen(fn, "rb");
//    if (!fp) {
//       return kp("File not found");
//    }
//
//    void *header;
//    size_t sig_size = 8;
//
//    if (fread(header, 1, sig_size, fp) != sig_size) {
//       return kp("No PNG signature");
//    }
//
//    int is_png = !png_sig_cmp(header, 0, sig_size);
//    if (!is_png) {
//       return kp("PNG signature incorrect");
//    }
//
//    return kp("Success!");
//}