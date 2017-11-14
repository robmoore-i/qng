#include<stdlib.h>
#include<stdio.h>
#include<png.h>

#define KXVER 3
#include "k.h"
#define kthrow(x) R krr(x)

typedef struct png_rob_data {
    png_structp png_ptr;
    png_infop info_ptr;
} png_rob_data;

K version(K x) {
    R kp(PNG_LIBPNG_VER_STRING);
}

FILE* open_if_valid(K x) {
    FILE *fp = fopen(x->s, "rb");
    if (!fp) {
        R NULL;
    }

    V *header = malloc(10);
    size_t sig_size = 8;

    if (fread(header, 1, sig_size, fp) != sig_size) {
        free(header);
        fclose(fp);
        R NULL;
    }

    I is_png = !png_sig_cmp(header, 0, sig_size);
    if (!is_png) {
        free(header);
        fclose(fp);
        R NULL;
    }

    free(header);

    R fp;
}

K checkpng(K x) {
    FILE *fp;
    if (fp = open_if_valid(x)) {
        fclose(fp);
        R kb(1);
    } else {
        R kb(0);
    }
}

K dimensions(K x){
    FILE *fp;
    if (!(fp = open_if_valid(x))) {
        kthrow("png");
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr) {
        kthrow("png_ptr");
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);

    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
        kthrow("info_ptr");
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
        kthrow("setjmp");
    }

    png_init_io(png_ptr, fp);
    size_t sig_size = 8;
    png_set_sig_bytes(png_ptr, sig_size);
    png_read_info(png_ptr, info_ptr);

    int width = 0;
    int height = 0;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, NULL, NULL, NULL, NULL, NULL);

    K dim = ktn(KI, 0);
    ja(&dim, &width);
    ja(&dim, &height);
    R dim;
}