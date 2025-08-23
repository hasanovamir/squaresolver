#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

struct equation_params
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
};

typedef enum solutionCount 
  {
    ZERO, ONE, TWO, INF
} solutionCount_t;

int read_coeffs      (struct equation_params* parametrs1);
int solve_equation   (struct equation_params* parametrs2);
int chek_is_zero     (double value);
int print_solution   (solutionCount_t solutionCount, struct equation_params* parametrs3);
int need_to_continue (void);
int testing_solver   (void);
int need_to_test     (void);


int main (void)
{
    struct equation_params parametrs;
    parametrs.a  = 0.0;
    parametrs.b  = 0.0;
    parametrs.c  = 0.0;
    parametrs.x1 = 0.0;
    parametrs.x2 = 0.0;

    printf ("This program is disigned to solve square equations\n");

    need_to_test();
 
    double n_solutions = 0;
    int n_input = 0;
    int answer = 1;
    
    printf ("Enter 3 float numbers:");
  
    do
    {   if ( (n_input = read_coeffs(&parametrs)) == 0)
        {   
            n_solutions = solve_equation (&parametrs);
            print_solution (n_solutions, &parametrs);
        }
        else
        {
            printf ("Plese, write 3 float numbers ><\n");
            printf ("parametrs:");
            continue;
        }
        answer = need_to_continue();
    } while (answer != 0);

    printf ("Thanks you for using!!!");
    return 0;
}


int read_coeffs (struct equation_params* parametrs1)
{
    char trash = '0';

    if (scanf ("%lg%lg%lg", &parametrs1->a, &parametrs1->b, &parametrs1->c )!= 3)
    {

        while ( (trash = getchar()) != '\n')
        {
            continue;
        }

        return -1;
    }

    else
    {
        return 0;
    }
}


int solve_equation (struct equation_params* parametrs2)
{   
    double disc = 0, sqrtd = 0;
    const double minv = 0.000001;

    parametrs2->x1 = 0;
    parametrs2->x2 = 0;

    if (chek_is_zero (parametrs2->a)) 
    {

       if (chek_is_zero (parametrs2->b)) 
       {

            if (chek_is_zero (parametrs2->c))
            {
                return INF;
            }

       }

       parametrs2->x1 = -parametrs2->c / parametrs2->b;

       return ONE;
    }

    disc = parametrs2->b * parametrs2->b - 4 * parametrs2->a * parametrs2->c;

    if (disc < -minv)
    {
        return ZERO;
    }
    else
    {
        sqrtd = sqrt (disc);

        if (chek_is_zero(disc))
        {
            parametrs2->x1 = -parametrs2->b / (2 * parametrs2->a);
            return ONE;
        }

        if (disc > minv)
        {
            parametrs2->x1 = (-parametrs2->b + sqrtd) / (2 * parametrs2->a);
            parametrs2->x2 = (-parametrs2->b - sqrtd) / (2 * parametrs2->a);
            return TWO;
        }

    }
    return 0;
}


int chek_is_zero (double value)
{
    const double minv = 0.000001;

    if ( fabs(value) < minv)
    {
        return 1;
    }

    return 0;
}


int print_solution (solutionCount_t solutionCount, struct equation_params* parametrs3)
{
    switch(solutionCount)
    {
        case INF:
            printf ("There are too many solution\n");
            break;
        case ZERO:
            printf ("There`s no solution\n");
            break;
        case ONE:
            printf ("There`s one solution: x = %.3lf\n", parametrs3->x1);
            break;
        case TWO:
            printf ("There are 2 solution: x_1 = %.3lf, x_2 = %.3lf\n", parametrs3->x1, parametrs3->x2);
    }
    return 0;
}


int need_to_continue (void)
{
    char answer = 0, skipconst = 0;

    printf ("Woude you continue?\n");
    printf ("Print \"Y\" to continue or \"N\" to break: ");

    getchar();

    do
    {
        answer = getchar();

        if (answer == '\n')
        {
            printf ("write Y or N!!!\nAnswer:");
            continue;
        }

        while ( (skipconst = getchar() ) != '\n')
        {
           continue;
        }

        if (tolower(answer) == 'y')
        {
            printf ("Enter next parametrs: ");
            return 1;
        }

        if (tolower(answer) == 'n')
        {
            return 0;
        }

        printf ("write Y or N!!!\nAnswer:");

    } while (1);
}


int need_to_test (void)
{
    char answer = 0, skipconst = 0, status = 0;

    printf ("Woude you start testing program?\n");
    printf ("Print \"Y\" to start testing program\n");
    printf ("Print \"N\" to use equation solver: ");

    do
    {
        answer = getchar();

        if (answer == '\n')
        {
            printf ("write Y or N!!!\nAnswer:");
            continue;
        }

        while ( (skipconst = getchar() ) != '\n')
        {
           continue;
        }

        if (tolower(answer) == 'y')
        {
            status = 1;
        }

        if (tolower(answer) == 'n')
        {
            status = -1;
        }
        if (status == 0)
        {
            printf ("write Y or N!!!\nAnswer:");
        }

    } while (status == 0);
    if (status == 1)
    {
        testing_solver();
    }
}


int testing_solver(void)
{
    int i = 0, j = 0;

    struct equation_params test_parametrs[5] = { { 0,  0,  0,  0,  0},
                                                 { 0,  2, -4,  2,  0},
                                                 { 1,  4,  4, -2,  0},
                                                 { 1, -5,  6,  3,  2},
                                                 { 1,  1,  5,  0,  0} };

    for (i = 0; i < 5; i++)
    { 
        struct equation_params test_eq;

        test_eq.a = test_parametrs[i].a;
        test_eq.b = test_parametrs[i].b;
        test_eq.c = test_parametrs[i].c;

        solve_equation(&test_eq);

        if (!chek_is_zero(test_parametrs[i].x1 - test_eq.x1) || !chek_is_zero(test_parametrs[i].x2 - test_eq.x2) )
        {    
            printf("Test failed in %d iteration\n", i+1);
            j++;
        }
    }
    if (!j)
    {
        printf("Test was complited successfully\n");
    }
}