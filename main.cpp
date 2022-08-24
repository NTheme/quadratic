#include <stdio.h>
#include <stdlib.h>
#include "quadratic.h"
#include "test.h"

inline void clearbuffer() {
	while (getchar() != '\n');
}

int main(int argc, const char *argv[]) {
	printf("# Program for solving quadratic equations a * x^2 + b * x + c = 0\n");
	printf("# By NThemeDEV (c) 2022 ver. 0.1\n");

	testing::testquadratic("tests.txt");

	quadratic::Equation **equations = NULL;
	int numequations = quadratic::terminalinput(&equations, argc, argv);

	int inputmore = 1;
	if (argc > 1) {		
		printf("%d equations read from the terminal arguments (also file). Do you want to input manually (0 == no, 1 == yes)? ", numequations);
		while (scanf("%d", &inputmore) != 1 || inputmore < 0 || inputmore > 1) {
			printf("Wrong input! Try again: ");
			clearbuffer();
		}
	}

	if (inputmore) {
		int add = 0;
		printf("Input number of equations: ");
		while (scanf("%d", &add) != 1 || add < 0) {
			printf("Wrong input! Try again: ");
			clearbuffer();
		}

		equations = quadratic::reallocequations(equations, numequations + add);
		for (int i = 0; i < add; i++) {
			printf("Input a, b, c of %d your extra equation divided by space: ", i + 1);
			if (streaminput(&equations[numequations + i]) != 1) {
				printf("Wrong input! Try again. ");
				clearbuffer();
				i--;
			}
		}
		numequations += add;
	}

	for (int i = 0; i < numequations; i++) {
		printf("Equation %d with a = %Lf, b = %Lf and c = %Lf ", i + 1, equations[i]->a, equations[i]->b, equations[i]->c);

		if ((equations[i]->numroots = quadratic::solveequation(equations[i])) == quadratic::QE_QUAD_ERROR) {
			printf("is unable to be solved!\n");
		} else {
			printf("has ");
			printroots(equations[i]);
		}
	}

	freeequations(equations, numequations);
	return 0;
}
