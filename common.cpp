#include <math.h>
#include "common.h"

namespace maths {
    int iszero(long double val) {
        const double DIV = 1e-7;
        return fabsl(val) < DIV;
    }
}