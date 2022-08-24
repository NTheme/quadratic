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
const double DIV = 1e-7;

/**
@brief   This namespace includes non-standart math functions that was used in quadratic equarions solver.
@details 
*/
namespace common {
    /**
    @brief   This function chechs if argument val is equal to zero.
    @details As double has no definite value I must to check if absolute distance between 0 and val is less than DIV (it's about 1e7).
    @param [in] val - vaue to check
    @return 1 If distance is less than DIV and 0 otherwise
    */
    int is_zero(long double val);
}

#endif
