#include<stdlib.h>
#include<stdio.h>
#include<png.h>

#define KXVER 3
#include "k.h"
#define kthrow(x) R krr(x)

K libpngversion(K x) {
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
        fclose(fp);
        kthrow("png_ptr");
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);

    if (!info_ptr) {
        fclose(fp);
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
    fclose(fp);
    K dim = ktn(KI, 0);
    ja(&dim, &width);
    ja(&dim, &height);
    R dim;
}

K pixels(K x){
    FILE *fp;
    if (!(fp = open_if_valid(x))) {
        kthrow("png");
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr) {
        fclose(fp);
        kthrow("png_ptr");
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);

    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
        fclose(fp);
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

    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);

    png_bytep row_pointers[height];

    for (int row = 0; row < height; row++) {
        row_pointers[row] = NULL;
    }

    for (int row = 0; row < height; row++) {
        row_pointers[row] = png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));
    }

    png_read_image(png_ptr, row_pointers);
    png_read_end(png_ptr, info_ptr);

    K red = ktn(KG, 0);
    K green = ktn(KG, 0);
    K blue = ktn(KG, 0);
    K alpha = ktn(KG, 0);
    for (int y = 0;y < height; y++) {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);
            ja(&red, &px[0]);
            ja(&green, &px[1]);
            ja(&blue, &px[2]);
            ja(&alpha, &px[3]);
        }
    }
    fclose(fp);
    R knk(4, red, green, blue, alpha);
}
