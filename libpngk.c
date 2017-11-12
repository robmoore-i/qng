#include "k.h"
#include<stdlib.h>
#include<png.h>

K version(K x) {
    return kp(PNG_LIBPNG_VER_STRING);
}