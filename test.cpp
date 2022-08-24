#include <stdio.h>

#include "common.h"
#include "quadratic.h"
#include "test.h"

namespace testing {
    int init_tests(const char *filename, quadratic::Equation ***tests) {
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
                *tests = quadratic::realloc_equations(*tests, read + STEP);
            }
            (*tests)[read] = quadratic::make_equation(a, b, c, numroots, x1, x2);
        }

        return read;
    }

    int is_equal_roots(const quadratic::Equation *a, const quadratic::Equation* b) {
        ASSERTIF(a != NULL, "nullptr in a", -1);
        ASSERTIF(b != NULL, "nullptr in b", -1);

        if (a->num_roots != b->num_roots) {
            return 0;
        }
        if (a->num_roots == 1 && !common::is_zero(a->x1 - b->x1)) {
            return 0;
        }

        return (common::is_zero(a->x1 - b->x1) && common::is_zero(a->x2 - b->x2)) ||
               (common::is_zero(a->x1 - b->x2) && common::is_zero(a->x2 - b->x1));
    }

    int test_quadratic(const char *filename) {
        ASSERTIF(filename != NULL, "error in filename", 0);
        
        printf("\n# Testing proram...\n");

        quadratic::Equation **tests = NULL;
        int numtests = init_tests(filename, &tests);

        printf("\nNumber of tests: %3d\n", numtests);

        for (int curtest = 0; curtest < numtests; ++curtest) {
            printf("Test %d...", curtest + 1);

            quadratic::Equation cur_equation = *tests[curtest];
            cur_equation.num_roots = quadratic::solve_equation(&cur_equation);

            switch (is_equal_roots(&cur_equation, tests[curtest])) {
            case -1:
                return 0;
            case 0:
                printf("FAILED!\n" "  EQUATION: a = %+-10.5Lg b = %+-10.5Lg c = %+-10.5Lg\n" "  program answer: ", tests[curtest]->a, tests[curtest]->b, tests[curtest]->c);
                quadratic::print_roots(&cur_equation);
                printf("  correct answer: ");
                quadratic::print_roots(tests[curtest]);
                break;
            case 1:
                printf("OK!\n");
                break;
            default:
                return 0;
            }
        }

        free_equations(tests, numtests);
        printf("\n");
        return 0;
    }
}
