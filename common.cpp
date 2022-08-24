#include <stdio.h>
#include <math.h>

#include "common.h"

namespace common {
    int is_zero(long double val) {
        return fabsl(val) < EPS;
    }

    void clearbuffer() {
	    while (getchar() != '\n');
    }
}
