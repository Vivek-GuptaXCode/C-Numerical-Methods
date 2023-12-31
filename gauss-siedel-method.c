#include <stdio.h>
#include <math.h>
#define N_EQ 3

void readEquation (double coeff[N_EQ + 1]);
void printEquation (double coeff[N_EQ + 1]);
void makeDiagonallyDominant(double eqn[N_EQ][N_EQ + 1]);
void gaussSeidel(double eqn[N_EQ][N_EQ + 1], double x[N_EQ], int maxIterations, double tolerance);

int main (void)
{
    double eqn[N_EQ][N_EQ + 1];
    double x[N_EQ]; // x is inital guess, and will be the solution
    int i = 0;

    printf("*** Gauss Seidel Method ***\n");
    printf("The general format is ax + by + cz = d\n");
    printf("Enter the values of a, b, c, d (space-seperated) for each equation\n");
    for (i = 0; i < N_EQ; i++)
    {
        printf("Equation %d: ", i+1);
        readEquation(eqn[i]);
    }
    printf("The equations are:\n");
    for (i = 0; i < N_EQ; i++)
    {
        printf("Equation %d: ", i+1);
        printEquation(eqn[i]);
    }

    // Make the equations diagonally dominant
    makeDiagonallyDominant(eqn);

    // Solve the equations using Gauss Seidel method

    // x is the initial guess
    // max iterations = 100, tolerance = 0.0001
    gaussSeidel(eqn, x, 100, 0.0001);

    // Print the solution
    printf("The solution is: x = %.4lf, y = %.4lf, z = %.4lf\n", x[0], x[1], x[2]);

    return 0;
}

void readEquation (double coeff[N_EQ + 1])
{
    scanf("%lf %lf %lf %lf", &coeff[0], &coeff[1], &coeff[2], &coeff[3]);
}

void printEquation (double coeff[N_EQ + 1])
{
    // print the equation with the given coefficients, in the format ax + by + cz = d
    printf("(%.2lf)x + (%.2lf)y + (%.2lf)z = (%.2lf)\n", coeff[0], coeff[1], coeff[2], coeff[3]);
}

void makeDiagonallyDominant(double eqn[N_EQ][N_EQ + 1])
{
    int i, j, maxIndex;
    double maxVal, temp;

    for (i = 0; i < N_EQ; i++)
    {
        maxIndex = i;
        maxVal = fabs(eqn[i][i]);

        // Find row with max value in current column
        for (j = i + 1; j < N_EQ; j++)
        {
            if (fabs(eqn[j][i]) > maxVal)
            {
                maxVal = fabs(eqn[j][i]);
                maxIndex = j;
            }
        }

        // Swap rows if necessary
        if (maxIndex != i)
        {
            for (j = 0; j <= N_EQ; j++)
            {
                temp = eqn[i][j];
                eqn[i][j] = eqn[maxIndex][j];
                eqn[maxIndex][j] = temp;
            }
        }
    }
}

void gaussSeidel(double eqn[N_EQ][N_EQ + 1], double x[N_EQ], int maxIterations, double tolerance)
{
    int i, j, k;
    double sum, error, old;

    // Initialize solutions
    // initial guess is 0
    for (i = 0; i < N_EQ; i++)
        x[i] = 0;

    // Iterate until max iterations or until error is less than tolerance
    for (k = 0; k < maxIterations; k++)
    {
        error = 0;

        // Go through each equation
        for (i = 0; i < N_EQ; i++)
        {
            sum = eqn[i][N_EQ]; // The constant term in the equation

            // Calculate the sum of the other terms
            for (j = 0; j < N_EQ; j++)
            {
                if (j != i)
                    sum -= eqn[i][j] * x[j];
            }

            // Calculate the new value for this variable
            old = x[i];
            x[i] = sum / eqn[i][i];

            // Calculate the absolute error
            error = fmax(error, fabs(old - x[i]));
        }

        // If the error is less than the tolerance, stop iterating
        if (error < tolerance)
            break;
    }
}
