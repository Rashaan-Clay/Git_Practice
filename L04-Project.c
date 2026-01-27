#include <stdio.h>

// Function prototype
double divide(double sum, double denom);

/**
 * @brief This will loop 5 times asking the user for 5 distinct values then call the divide function to then print the ouput.
 * @return this return 1 to indicate a sucessful function termination
*/


int main()
{
    double num;
    double sum = 0.0; // removes garabage values
    for (int i = 1; i < 6; i++)
    {
        printf("Enter a number(%i): ", i);
        scanf("%lf", &num);
        sum += num; // Summation
    }
    double result = divide(sum, 5);
    printf("Results of divide function: %.1f", result);
    return 0;
 }

/**
 * @brief Takes in the summed value of each iteration of num and divides it by a constant of 5
 * @param double function wtih a pointer to a double variable
 * @return void function with no return
*/
double divide(double sum, double denom) 
{
    return sum / denom; // No pointers needed because we're only returning the value created by the divide function. 
                        // No updating the value of sum is necessary
}