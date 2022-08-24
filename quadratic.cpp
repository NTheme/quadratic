#include <stdio.h>
#include <math.h>
#include "common.h"/////////sn case
#include "quadratic.h"

namespace quadratic {
    inline int equationvalid(const Equation *equation) {
        if (equation == NULL || !isfinite(equation->a) || !isfinite(equation->b) || !isfinite(equation->c) || !isfinite(equation->x1) || !isfinite(equation->x2))
            return QE_QUAD_ERROR;
        return 0;
    }

    Equation *makeequation(long double a, long double b, long double c, int numroots, long double x1, long double x2) {
        Equation *equation = (Equation *)calloc(1, sizeof(Equation));
        ASSERTIF(!equationvalid(equation), "unable to alloc", NULL);
        
        equation->a = a, equation->b = b, equation->c = c, equation->numroots = numroots, equation->x1 = x1, equation->x2 = x2;
        return equation;
    }

    Equation **reallocequations(Equation **equations, int size) {
        Equation **newequations = (Equation **)realloc(equations, size * sizeof(Equation *));
        ASSERTIF(newequations != NULL, "nullptr in equations", NULL);
        
        return newequations;
    }

    void freeequations(Equation **equations, int quantity) {
        for (int i = 0; i < quantity; i++) {
            free(equations[i]);
        }
        free(equations);
    }

    int streaminput(Equation **equation, FILE *stream) {
        ASSERTIF(stream   != NULL, "nullptr in stream",   0);
        ASSERTIF(equation != NULL, "nullptr in equation", 0);

        long double a = 0, b = 0, c = 0;
        if (fscanf(stream, "%Lf %Lf %Lf", &a, &b, &c) != 3) {
            return 0;
        }

        *equation = makeequation(a, b, c);
        return 1;
    }

    int fullstreaminput(Equation ***equations, FILE *stream) {
        ASSERTIF(stream    != NULL, "nullptr in stream",    0);
        ASSERTIF(equations != NULL, "nullptr in equations", 0);

        Equation *equation = NULL;
        int read = 0;
        for (; streaminput(&equation, stream) == 1; ++read) {
            if (read % STEP == 0) {
                *equations = reallocequations(*equations, read + STEP);
            }
            (*equations)[read] = equation;
        }

        return read;
    }

    int terminalinput(Equation ***equations, int argc, const char *argv[]) {
        ASSERTIF(argv      != NULL, "nullptr in argv",      0);
        ASSERTIF(equations != NULL, "nullptr in equations", 0);

        if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'f') {
            FILE *input = fopen(argv[2], "r");
            if (input == NULL) {
                return 0;
            }
            return fullstreaminput(equations, input);
        }

        long double a = 0, b = 0, c = 0;
        int read = 0, numequations = (argc - 1) / 3;
        for (; read < numequations && (sscanf(argv[read + 1], "%Lf", &a) + sscanf(argv[read + 2], "%Lf", &b) + sscanf(argv[read + 3], "%Lf", &c) == 3); ++read) {
            if (read % STEP == 0) {
                *equations = reallocequations(*equations, read + STEP);
            }
            (*equations)[read] = makeequation(a, b, c);
        }
        return read;
    }

    int printroots(const Equation *equation) {
        ASSERTIF(!equationvalid(equation), "QUAD_ERROR in equation", QE_QUAD_ERROR);

        switch (equation->numroots) {
        case RN_INF:
            printf("infinity of roots\n");
            break;
        case RN_ZERO:
            printf("zero roots\n");
            break;
        case RN_ONE:
            printf("one root: %Lf\n", equation->x1);
            break;
        case RN_TWO:
            printf("two roots: %Lf, %Lf\n", equation->x1, equation->x2);
            break;
        case RN_DEFAULT:
            printf("uninitialized\n");
            break;
        default:
            return 1;
        }

        return 0;
    }

    int solvelinear(long double b, long double c, long double *x1) {
        ASSERTIF(x1 != NULL, "nullptr in x1", 1);

        if (b == 0) {
            return (c == 0) ? RN_INF : RN_ZERO;
        }

        *x1 = -c / b;
        return RN_ONE;
    }

    int solveequation(Equation *equation) {
        ASSERTIF(!equationvalid(equation), "QUAD_ERROR in equation", QE_QUAD_ERROR);

        long double a = equation->a, b = equation->b, c = equation->c;

        if (a == 0)
            return solvelinear(b, c, &equation->x1);

        long double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return RN_ZERO;

        if (iszero(discriminant)) {
            equation->x1 = -b / (2 * a);
            return RN_ONE;
        }

        discriminant = sqrtl(discriminant);
        equation->x1 = (-b + discriminant) / (2 * a);
        equation->x2 = (-b - discriminant) / (2 * a);
        return RN_TWO;
    }
}
