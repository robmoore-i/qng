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

K dimensions(K x) {
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

K readpng(K x) {
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

    K red = ktn(KG, width*height);
    K green = ktn(KG, width*height);
    K blue = ktn(KG, width*height);
    for (int y = 0;y < height; y++) {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);
            red  ->G0[x+y*width] = px[0];
            green->G0[x+y*width] = px[1];
            blue ->G0[x+y*width] = px[2];
        }
    }
    fclose(fp);
    R knk(3, red, green, blue);
}

K writepng(K fn, K w, K h, K redbuf, K greenbuf, K bluebuf) {
	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;

	char* filename = fn->s;
	int width = w->i;
	int height = h->i;
	short *rbuffer = kH(redbuf);
	short *gbuffer = kH(greenbuf);
	short *bbuffer = kH(bluebuf);

	// Open file for writing (binary mode)
	fp = fopen(filename, "wb");
	if (fp == NULL) {
	    kthrow(filename);
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
	    fclose(fp);
	    kthrow("png_ptr");
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
	    fclose(fp);
	    png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
	    kthrow("info_ptr");
	}

	// Setup Exception handling
	if (setjmp(png_jmpbuf(png_ptr))) {
	    fclose(fp);
	    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	    png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
	    kthrow("setjmp");
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	png_write_info(png_ptr, info_ptr);

	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep) malloc(3 * width * sizeof(png_byte));

	// Write image data
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			row[0 + x * 3] = rbuffer[x + y * width];
			row[1 + x * 3] = gbuffer[x + y * width];
			row[2 + x * 3] = bbuffer[x + y * width];
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);

	fclose(fp);
	png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
	png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	free(row);

	R kb(1);
}
