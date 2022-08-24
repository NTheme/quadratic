#ifndef QUADR_DEF
#define QUADR_DEF

/**
@brief Пространство имен для обработки квадратного уравнения.
@details Данное пространство имен содержит в себе все необходимые функции и члены для решения квадратного уравнения и удобного форматированного вывода.
*/
namespace quadratic {
    /**
    @brief Структура с информацией о квадратном уравнении
    @details 
    @param a        - Коэффициент при x^2
    @param b        - Коэффициент при x
    @param c        - Свободный коэффициент
    @param numroots - Количество корней уравнения
    @param x1       - Первый корень уравнения
    @param x2 - Второй корень уравнения
    */
    typedef struct {
        long double a, b, c;
        long double x1, x2;
        int numroots;
    } Equation;

    /**
    @brief Перечисляемый тип для хранения имен всевозможных количеств корней квадратного уравнения
    @detailed
    @param RM_DEFAULT - не инициализированно
    @param RM_ZERO    - ноль корней
    @param RM_ONE     - один корень
    @param RM_TWO     - два коорня
    @param RM_INF     - бесконечное количество корней
    */
    typedef enum {
        RN_DEFAULT,
        RN_ZERO,
        RN_ONE,
        RN_TWO,
        RN_INF
    } ROOT_NUMBER;

    /**
    @brief Перечисляемый тип для хранения имен ошибок
    @details
    @param QE_QUAD_ERROR - ошибка при инициализации структуры Quadratic
    */
    enum QUADRATIC_ERROR {
        QE_QUAD_ERROR = -1
    };

    Equation *makeequation(long double a, long double b, long double c, int numroots = RN_DEFAULT, long double x1 = 0, long double x2 = 0);
    Equation **reallocequations(Equation **equations, int size);

    /**
    @brief Функция для освобождения динамически выделенной памяти под массив указателей на Quadratic
    @details
    @return void
    @param [in] equation - массив указателей на указателей на Quadratic
    @param [in] size     - размер массива
    */
    void freeequations(Equation **equation, int size); 

    int streaminput    (Equation **,  FILE *stream = stdin);
    int fullstreaminput(Equation ***, FILE *stream = stdin);
    int terminalinput  (Equation ***, int, const char **);

    int solveequation(Equation *);
    int printroots(const Equation *);
}

#endif
