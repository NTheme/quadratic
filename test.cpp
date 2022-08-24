#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "quadratic.h"
#include "test.h"

namespace testing {
    int inittests(const char *filename, quadratic::Equation ***tests) {
        ASSERTIF(tests    != NULL, "error in equation", 0);
        ASSERTIF(filename != NULL, "error in filename", 0);
        
        FILE *input = fopen(filename, "r");
        if (input == NULL) {
            return 0;
        }

        long double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
        int numroots = 0, read = 0;
        for (; fscanf(input, "%Lf %Lf %Lf %d %Lf %Lf", &a, &b, &c, &numroots, &x1, &x2) == 6; ++read) {
            if (read % STEP == 0) {
                *tests = quadratic::reallocequations(*tests, read + STEP);
            }
            (*tests)[read] = quadratic::makeequation(a, b, c, numroots, x1, x2);
        }

        return read;
    }

    int isequalroots(int ax1, int ax2, int bx1, int bx2) {
        return (maths::iszero(ax1 - bx1) && maths::iszero(ax2 - bx2)) ||
               (maths::iszero(ax1 - bx2) && maths::iszero(ax2 - bx1));
    }

    int testquadratic(const char *filename) {
        ASSERTIF(filename != NULL, "error in filename", 0);
        
        printf("\n# Testing proram...\n");

        quadratic::Equation **tests = NULL;
        int numtests = inittests(filename, &tests);

        printf("\nNumber of tests: %3d\n", numtests);

        for (int curtest = 0; curtest < numtests; ++curtest) {
            printf("Test %d...", curtest + 1);

            quadratic::Equation* curequation = tests[curtest];
            curequation->numroots = quadratic::solveequation(curequation);


            if (isequalroots(curequation->x1, curequation->x2, tests[curtest]->x1, tests[curtest]->x2)) {
                printf("OK!\n");
            } else {
                printf("FAILED!\n" "  EQUATION: a = %Lf, b = %Lf, c = %Lf\n" "  program answer: ", tests[curtest]->a, tests[curtest]->b, tests[curtest]->c);
                quadratic::printroots(curequation);
                printf("  correct answer: ");
                quadratic::printroots(tests[curtest]);
            }
        }
        printf("\n");
        return 0;
    }
}