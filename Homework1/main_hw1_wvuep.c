/**
 * @file main_hw1_wvuep.c
 * @brief File with main function for CS 350 Homework #1: WVU Enrollment Problem
 * @author Brian Powell
 * @version 4.1
 * 
 * Place this file in the same directory as your own source code and add it to your project.
 * 
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 */

// ReSharper disable CppUnusedIncludeDirective

// Include header files
#include "hw1_wvuep.h"
#include "test_hw1_wvuep.h"
#include <stdio.h>

/**
 * @brief Program entry point
 * @return Status code
*/
int main(void)
{
	// Run tests
	run_tests();

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