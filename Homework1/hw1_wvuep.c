/**
 * @author Rashaan Clay
 * 
 * @file hw1_wvuep.c
 * 
 * @brief This program will return a growth rate, and estimated enrollment from user input start_year to a fixed end_year
 * 
 * @details 
 * After being prompt with a target enrollment, the program will compute a growth rate, 
 * and a characteristic of that growth_rate depeding on the range in which it falls.
 * Following that, a loop will begin starting from a initial_year to an end_year, 
 * it will calculate each incrementing year's estimate enrollment.
 * 
 * For example: 2024: 40000 -> 2025: 41000 and so on...
 * 
 * 
 * 
 */
#include "hw1_wvuep.h"
#include "test_hw1_wvuep.h"
#include <stdio.h>
#include <ctype.h>
#include <math.h>
int main(void)
{
   // Copied from main to ensure that values were correct
   // Initial enrollment
   const int initial_enrollment = 25994;
   // Year of initial enrollment
   const int initial_year = 2024;
   // Year for target enrollment
   const int target_year = 2040;
   // Last year for enrollment estimates
   const int end_year = 2070;
   // Print name of programmer
   printf("Code written by %s\n", get_programmer_name());
   // Prompt user for target enrollment
   int target_enrollment = prompt_target_enrollment(target_year);
   // Calculate target growth rate
   double growth_rate = calculate_growth_rate(initial_enrollment, target_enrollment, initial_year, target_year);
   // Print growth rate and description
   print_growth_rate(growth_rate);
   // Print enrollment estimates for years initial_year through end_year
   print_enrollment_estimates(initial_enrollment, growth_rate, initial_year, end_year);
   return 0;
}
const char* get_programmer_name(void)
{
   return "Rashaan\n";
}
int prompt_target_enrollment(int target_year)
{
   do
{
   printf("Enter the enrollment target for the year target_year: "); // Reprompting for negative integers
   scanf("%d", &target_year);

}while (target_year < 0);

   return target_year;
}
double calculate_growth_rate(int initial_enrollment, int target_enrollment, int initial_year, int target_year)
{
   double growth_rate = pow(((double)target_enrollment / (double)initial_enrollment), (1.0/(target_year - initial_year))) - 1;
   // Must cast both target_enrollment and initial_enrollment for this calculation because of integer division. 
   // Which will yield 1, and raising it to the first power as well; then subtracting by 1, which results in 0. 
   
   return growth_rate;
}

const char* get_growth_rate_description(double growth_rate)
{
   // Could have converted to percentage for easier calculation
   if (growth_rate < 0)
   {
      return "negative\n";
   }

   else if (growth_rate >= 0.0 && growth_rate < 0.01) // remaining in decimal form
   {
      return "reasonable\n";
   }

   else if (growth_rate >= 0.01 && growth_rate < 0.02)
   {
      return "ambitious\n";
   }

   else if (growth_rate >= 0.02 && growth_rate < 0.04)
   {
      return "high\n";
   }

   else // 
   {
      return "unreasonable\n";
   }
}
void print_growth_rate(double growth_rate)
{
   printf("The required annual rate of growth, %.1f%%, is %s\n", growth_rate *100 ,get_growth_rate_description(growth_rate));
}

int calculate_enrollment_estimate(int initial_enrollment, double growth_rate, int initial_year, int estimate_year)
{
   int estimate_enrollment = round(initial_enrollment * pow(1+growth_rate, estimate_year - initial_year));
   return estimate_enrollment;
}

void print_enrollment_estimates(int initial_enrollment, double growth_rate, int initial_year, int end_year)
{
   for (int i = initial_year; i <= end_year; i++)
   {
      printf("%d enrollment estimate: %d\n", i, calculate_enrollment_estimate(initial_enrollment, growth_rate, initial_year, i));
      // i replaces estimate_year as it will calculate that specific years enrollment_estimate via the function call.
   }
}