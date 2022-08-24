﻿#ifndef QUADR_DEF
#define QUADR_DEF

/**
@brief This namespace includes tools to process and solve quadratic equation.
@details
*/
namespace quadratic {
    /**
    @brief   A struct with coefficients and roots of quadratic equation
    @details Includes all information about equation, whole processing is made with Equation's values.
    @param a        - Coefficient of x ^ 2
    @param b        - Coefficient of x
    @param c        - Free coefficient
    @param numroots - Number of equation's roots.
    @param x1       - First equation's root.
    @param x2       - Second equation's root.
    */
    typedef struct {
        long double a, b, c;
        long double x1, x2;
        int num_roots;
    } Equation;

    /**
    @brief Enumerated type of data consists of all different quantities of quadratic equation's roots.
    @details Type RM_DEFAULT is not a quantity. It is used for initialization.
    @param RM_DEFAULT - Not initialized
    @param RM_ZERO    - Zero roots
    @param RM_ONE     - One root
    @param RM_TWO     - Two roots
    @param RM_INF     - Infinity of roots
    */
    typedef enum {
        RN_DEFAULT,
        RN_ZERO,
        RN_ONE,
        RN_TWO,
        RN_INF
    } ROOT_NUMBER;

    /**
    @brief Enumerated type of data with errors.
    @details
    @param QE_QUAD_ERROR - Error during initialization od Equation.
    */
    enum QUADRATIC_ERROR {
        QE_QUAD_ERROR = -1
    };

    /**
    @brief Makes an Equation using it's elements as arguments.
    @details
    @param [in] a        - Coefficient of x ^ 2
    @param [in] b        - Coefficient of x
    @param [in] c        - Free coefficient
    @param [in] numroots - Number of equation's roots.
    @param [in] x1       - First equation's root.
    @param [in] x2       - Second equation's root.
    @return A pointer to an equation was made
    */
    Equation *make_equation(long double a, long double b, long double c, int numroots = RN_DEFAULT, long double x1 = 0, long double x2 = 0);

    /**
    @brief Reallocates memory for an array of pointers to Equation and returns new pointer.
    @details Allocates memory dynamically.
    @param [in] **equation - A pointer to the first element of array
    @param [in] size       - New array's size (how much Quadratic* will be allocated, not in bytes)
    @return A new pointer to array, already with size elements
    */
    Equation **realloc_equations(Equation **equations, int size);

    /**
    @brief Function frees dynamic memory which was allocated for array of pointers to Quadratic.
    @details
    @param [in] equation - A pointer to the first element
    @param [in] size     - Array's size (how much Quadratic* was allocated, not in bytes)
    @return void
    */
    void free_equations(Equation **equation, int size); 

    /**
    @brief Function reads an Equation from *stream.
    @details By default *stream is equal to stdin, but you can change it by giving this function secaon argument. First must have type Equation ** because stream_input dynamically
    allocates memory for equation and writes a pointer to result into first argument. Reads 3 long double numbers from stream and makes an Equation. 
    @param [out] **equation - A pointer to pointer to equation. &equation will have a pointer to read equation
    @param [in] *stream     - A pointer to FILE. It is a pointer to stream with input data
    @return 1 if equation was read successfully ant 0 otherwise (in case of any errors)
    */
    int stream_input (Equation **equations, FILE *stream = stdin);

    /**
    @brief Function reads a plenty of Equation from *stream.
    @details By default *stream is equal to stdin, but you can change it by giving this function secaon argument. First must have type Equation *** because full_stream_input dynamically
    allocates memory for array of Equation and writes a pointer to result into first argument. Function reads data from stream, each by 3 long double numbers in a row while new 3 numbers exists, 
    last < 3 it throws away (it's not important how numbers located on lines): a, b and c. Parses by each 3 elements and uses stream_input to make an Equation
    @param [out] ***equation - A pointer to pointer to pointer to equation. &equation will have a pointer to an array of read equations
    @param [in] *stream      - A pointer to FILE. It is a pointer to stream with input data
    @return number of equations that was read successfully
    */
    int full_stream_input(Equation *** equations, FILE *stream = stdin);

    /**
    @brief Function reads a plenty of Equation from command line arguments (it can be a file)
    @details First must have type Equation *** because full_stream_input dynamically allocates memory for array of Equation and writes a pointer to result into first argument. 
    Function reads data from terminal arguments that was given to program. If second element of argv is a flag -f, terminal_input tries to get plenty of Equation from file which name is 
    in third element of argv using full_stream_input. If it is not possible, function reads data from argv, each by 3 long double numbers in a row, one element from one element of argv, while new 
    3 numbers exists, last < 3 it throws away (it's not important how numbers located on lines): a, b and c. Starts from argv[1]. Parses by each 3 and makes an Equation.
    @param [out] ***equation - A pointer to pointer to pointer to equation. &equation will have a pointer to an array of read equations
    @param [in] argc         - Number of terminal arguments
    @param [in] **argv       - Pointer to array with strings of terminal arguments
    @return number of equations that was read successfully
    */
    int terminal_input (Equation *** equations, int argc, const char **argv);

    /**
    @brief Solves a quadratic equation.
    @details Writes long double roots to x1 and x2 (if they exists, otherwise 0), members of equation which pointer was given as first 
    argument.
    @param [in] [out] *equation - A pointer to equation.
    @return number of roots to num_roots (look ROOT_NUMBER), you must make equation->num_roots equal to this value
    */
    int solve_equation(Equation *equation);

    /**
    @brief Prints roots of Equation
    @details writes to stdout number of roots, then roots if they exists. Examples: infinity of roots, zero roots, one root: 'x1', two roots: 'x1', 'x2'
    @param [in] *equation - A pointer to equation.
    @return 0 if equation was written successfully ant 0 otherwise (in case of any errors)
    */
    int print_roots(const Equation *equation);
}

#endif
