#ifndef MATHS_DEF
#define MATHS_DEF

#include <assert.h>
#include <errno.h>

#define ASSERTIF(cond, desc, val) {                                                                                                  \
    assert((cond) && desc);                                                                                                          \
    if (!(cond)) {                                                                                                                   \
        printf("ERROR in %s with '%s' in line %d in function %s in file %s", #cond, #desc, __LINE__, __PRETTY_FUNCTION__, __FILE__); \
        errno = -1;                                                                                                                  \
        return val;                                                                                                                  \
    }                                                                                                                                \
}

const int STEP = 100;

namespace maths {
    int iszero(long double val);
}

#endif