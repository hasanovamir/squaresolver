#include <TXlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define minv 0.000001

//читать аргументы командной строки + make file

struct equation_params
{
    double a;
    double b;
    double c;
};

struct roots
{
    double x1;
    double x2;
};

typedef enum solutionCount 
{
    EMPTYSET = -1,
    ZERO,        
    ONE, 
    TWO, 
    INF
} solutionCount_t;

int read_coeffs      (equation_params* parametrs);
solutionCount_t solve_equation   (equation_params* parametrs, roots* roots);
int check_is_zero     (double value);
int print_solution   (solutionCount_t solutionCount, const equation_params* parametrs, const roots* roots);
bool need_to_continue (void);
int testing_solver   (void);
int need_to_test     (void);
int clean_buffer     (void);
double get_num       (void);
solutionCount_t solve_square (equation_params* parametrs, roots* roots);
solutionCount_t solve_line_equation (roots* roots, double parametr1, double parametr2);

int main (void)
{
    equation_params parametrs = {};
    roots roots = {};

    printf ("This program is disigned to solve square equations\n");

    need_to_test ();     
    
    printf ("Enter 3 float numbers:");

    int answer = 0;
  
    do
    {   read_coeffs(&parametrs);
        print_solution (solve_equation (&parametrs, &roots), &parametrs, &roots);
        answer = need_to_continue ();
    } while (answer != 0);

    printf ("Thanks you for using!!!");
    return 0;
}


int read_coeffs (equation_params* parametrs)
{
    parametrs->a = get_num();
    if (getchar () == '\n')
    {
        printf ("Write next float numbers: ");
    }
    parametrs->b = get_num();
    if (getchar () == '\n')
    {
        printf ("Write next float numbers: ");
    }
    parametrs->c = get_num ();
    return 0;
}


solutionCount_t solve_equation ( equation_params* parametrs, roots* roots)
{   
    assert(parametrs != NULL);
    assert(roots != NULL);
    if (check_is_zero (parametrs->a))
    {
        return solve_line_equation (roots, parametrs->b, parametrs->c);
    }
    else if (check_is_zero (parametrs->c))
    {
        return solve_line_equation (roots, parametrs->a, parametrs->b);
    }
    else 
    {
        return solve_square (parametrs, roots);
    }
}


int check_is_zero (double value)
{
        return fabs (value) < minv;
}
 


int print_solution (solutionCount_t solutionCount, const equation_params* parametrs, const roots* roots)
{
    printf ("Your equation: %.3lf X^2 + %.3lf X + %.3lf = 0\n",
        parametrs->a, parametrs->b, parametrs->c);
    switch (solutionCount) 
    {
        case EMPTYSET:
            printf ("Empty set");
            break;
        case INF:
            printf ("There are too many solution\n");
            break;
        case ZERO:
            printf ("There`s no solution\n");
            break;
        case ONE:
            printf ("There`s one solution: x = %.3lf\n", roots->x1);
            break;
        case TWO:
            printf ("There are 2 solution: x_1 = %.3lf, x_2 = %.3lf\n", roots->x1, roots->x2);
        default:
            ;
    }
    return 0;
}


bool need_to_continue (void)
{
    printf ("Woude you continue?\n");
    printf ("Print \"Y\" to continue or \"N\" to break: ");


    clean_buffer ();

    do
    {
        int answer = getchar ();

        if (answer == '\n')
        {
            printf ("write Y or N!!!\nAnswer:");
            continue;
        }

        clean_buffer ();

        if (tolower (answer) == 'y')
        {
            printf ("Enter next parametrs: ");
            return true;           // True False bool
        }

        if (tolower (answer) == 'n')
        {
            return false;
        }

        printf ("write Y or N!!!\nAnswer:");

    } while (true);        // True
}


int need_to_test (void)
{
    int status = 0;

    printf ("Woude you start testing program?\n");
    printf ("Print \"Y\" to start testing program\n");
    printf ("Print \"N\" to use equation solver: ");

    do
    {
        int answer = getchar ();

        if (answer == '\n')
        {
            printf ("write Y or N!!!\nAnswer:");
            continue;
        }

        clean_buffer ();

        if (tolower (answer) == 'y')
        {
            status = 1;
        }
        else if (tolower (answer) == 'n')
        {
            status = -1;
        }
        else
        {
            printf ("write Y or N!!!\nAnswer:");
        }

    } while (status == 0);
    if (status == 1)
    {
        testing_solver ();
    }
    return 0;
}


int testing_solver (void)
{

    equation_params test_parametrs[5] = { { 0,  0,  0},
                                                 { 0,  2, -4},
                                                 { 1,  4,  4},
                                                 { 1, -5,  6},
                                                 { 1,  1,  5} };


    roots cor_roots[5] = {  { 0, 0},
                            { 2, 0},
                            {-2, 0},
                            { 3, 2},
                            { 0, 0}  };

    for (int i = 0; i < 5; i++)
    {
        roots test_roots = {};
        solve_equation (&test_parametrs[i], &test_roots);

        if (!check_is_zero (cor_roots[i].x1 - test_roots.x1) || !check_is_zero (cor_roots[i].x2 - test_roots.x2) )
        {    
            printf (RED "Test failed\n" RESET);
        }
        else
        {
            printf (GREEN "Test was complited successfully\n" RESET);
        }
    }
    return 0;
;}


int clean_buffer (void)
{
    int trash = 0;
    while ( (trash = getchar () ) != '\n')
    {
        if (trash == EOF)
            return EOF;
    }
    return 0;
}
double get_num (void)
{
    double read_value = 0;
    while (true)
    {
        if (scanf ("%lf", &read_value) == 1)
        {
                return read_value;
        }
        else
        {
            clean_buffer ();
            printf (RED "ERROR: " RESET);
            printf ("try to ender again: ");
        }
    }
}


solutionCount_t solve_line_equation (roots* roots, double parametr1, double parametr2)
{
        if (check_is_zero (parametr1))
        {
            if (check_is_zero (parametr2))
                return INF;
            else
                return EMPTYSET;
        }
        else
        {
            roots->x1 = - parametr2 / parametr1;
            return ONE;
        }    
}


solutionCount_t solve_square (equation_params* parametrs, roots* roots)
{
    double disc = 0, sqrtd = 0;

    disc = parametrs->b * parametrs->b - 4 * parametrs->a * parametrs->c;

    if (check_is_zero (disc))
    {
        roots->x1 = - parametrs->b / 2 / parametrs->a;
        return ONE;
    }
    else if (disc > minv)
    {
        sqrtd = sqrt (disc);
        roots->x1 = (- parametrs->b + sqrtd) / 2 / parametrs->a;
        roots->x2 = (- parametrs->b - sqrtd) / 2 / parametrs->a;
        return TWO;
    }
    else
    {
        return ZERO;
    }
}