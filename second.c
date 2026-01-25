#include <stdio.h>

// Function prototype
double divide(double* sum, double denom);

/**
 * @brief This will loop 5 times asking the user for 5 distinct values then call the divide function to then print the ouput.
 * @return this return 1 to indicate a sucessful function termination
*/


int main()
{
    double num = 0.0;
    double denom = 5;
    for (int i = 1; i < 6; i++)
    {
        printf("Enter a number(%i): ", i);
        scanf("%lf", &num);
        num += num; // Summation
    }   
    printf("Total: %f", num); // pass by value because printf doesnt modify the value
    return 0;
 }

/**
 * @brief Takes in the summed value of each iteration of num and divides it by a constant of 5
 * @param double function wtih a pointer to a double variable
 * @return void function with no return
*/
double divide(double* sum, double denom)
{
    return *sum = *sum / denom;
}