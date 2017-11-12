#include<stdlib.h>
#include<stdio.h>
#include<png.h>

#define KXVER 3
#include "k.h"

K version(K x) {
    return kp(PNG_LIBPNG_VER_STRING);
}

K checkpng(K x) {
    FILE *fp = fopen(x->s, "rb");
    if (!fp) {
        return krr(x->s);
    }

    void *header = malloc(10);
    size_t sig_size = 8;

    if (fread(header, 1, sig_size, fp) != sig_size) {
        free(header);
        fclose(fp);
        return krr("png");
    }

    int is_png = !png_sig_cmp(header, 0, sig_size);
    if (!is_png) {
        free(header);
        fclose(fp);
        return krr("png");
    }

    fclose(fp);
    free(header);

    return kb(1);
}