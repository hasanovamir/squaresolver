#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

struct coeffs
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
};

int read_coeffs    (struct coeffs* parametrs1);
int solve_equation (struct coeffs* parametrs2);
int chek_to_zero   (double value);
int print_solution (int count, struct coeffs* parametrs3);
int need_to_continue   (void);

int main (void)
{
    struct coeffs parametrs;
    parametrs.a  = 0.0;
    parametrs.b  = 0.0;
    parametrs.c  = 0.0;
    parametrs.x1 = 0.0;
    parametrs.x2 = 0.0;
    printf ("This program is disigned to solve square equations\n");
 
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

    printf ("Thanks you for using");
    return 0;
}


int solve_equation (struct coeffs* parametrs2)
{   
    double disc = 0, sqrtd = 0;

    parametrs2->x1 = 0;
    parametrs2->x2 = 0;

    if (chek_to_zero (parametrs2->a)) 
    {

       if (chek_to_zero (parametrs2->b)) 
       {

            if (chek_to_zero (parametrs2->c))
            {
                return -1;
            }

       }

       parametrs2->x1 = -parametrs2->c / parametrs2->b;

       return 1;
    }

    disc = parametrs2->b * parametrs2->b - 4 * parametrs2->a * parametrs2->c;

    if (disc < 0)
    {
        return 0;
    }
    else
    {
        sqrtd = sqrt (disc);

        if (disc == 0)
        {
            parametrs2->x1 = -parametrs2->b / (2 * parametrs2->a);
            return 1;
        }

        if (disc > 0)
        {
            parametrs2->x1 = (-parametrs2->b + sqrtd) / (2 * parametrs2->a);
            parametrs2->x2 = (-parametrs2->b - sqrtd) / (2 * parametrs2->a);
            return 2;
        }

    }
    return 0;
}


int print_solution (int count, struct coeffs* parametrs3)
{
    switch(count)
    {
        case -1:
            printf ("There are too many solution\n");
            break;
        case 0:
            printf ("There`s no solution\n");
            break;
        case 1:
            printf ("There`s one solution: x = %.3lf\n", parametrs3->x1);
            break;
        case 2:
            printf ("There are 2 solution: x_1 = %.3lf, x_2 = %.3lf\n", parametrs3->x1, parametrs3->x2);
    }
    return 0;
}


int read_coeffs (struct coeffs* parametrs1)
{
    char tresh;

    if (scanf ("%lg%lg%lg", &parametrs1->a, &parametrs1->b, &parametrs1->c )!= 3)
    {

        while ( (tresh = getchar()) != '\n')
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
int chek_to_zero (double value)
{
    const double minv = 0.000001;

    if ( fabs(value) < minv)
    {
        return 1;
    }

    return 0;
}