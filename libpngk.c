#include<stdlib.h>
#include<stdio.h>
#include<png.h>

#define KXVER 3
#include "k.h"

K version(K x) {
    return kp(PNG_LIBPNG_VER_STRING);
}

FILE* open_if_valid(K x) {
    FILE *fp = fopen(x->s, "rb");
    if (!fp) {
        return NULL;
    }

    void *header = malloc(10);
    size_t sig_size = 8;

    if (fread(header, 1, sig_size, fp) != sig_size) {
        free(header);
        fclose(fp);
        return NULL;
    }

    int is_png = !png_sig_cmp(header, 0, sig_size);
    if (!is_png) {
        free(header);
        fclose(fp);
        return NULL;
    }

    free(header);

    return fp;
}

K checkpng(K x) {
    FILE *fp;
    if (fp = open_if_valid(x)) {
        fclose(fp);
        return kb(1);
    } else {
        return kb(0);
    }
}

//K pnginfo(K x){
//    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//
//    if (!png_ptr) {
//        return krr("png_ptr");
//    }
//
//    png_infop info_ptr = png_create_info_struct(png_ptr);
//
//    if (!info_ptr) {
//        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
//        return krr("info_ptr");
//    }
//
//    if (setjmp(png_jmpbuf(png_ptr))) {
//        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
//        fclose(fp);
//        return krr("setjmp");
//    }
//}