/**
 * @file test_hw1_wvuep.h
 * @brief Tests header file for CS 350 Homework #1: WVU Enrollment Problem
 * @author Brian Powell
 * @version 4.6
 *
 * Place this file in the same directory as your own source code and add it to your project.
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 */

#pragma once

/**
 * @brief Return value if int-returning function is unimplemented
 */
#define UNIMPLEMENTED_RETURN_INT (-999)

/**
 * @brief Return value if double-returning function is unimplemented
 */
#define UNIMPLEMENTED_RETURN_DOUBLE (-999.0)

/**
 * @brief Return value if unsigned int-returning function is unimplemented
 */
#define UNIMPLEMENTED_RETURN_UNSIGNED_INT 0

/**
 * @brief Return value if pointer-returning function is unimplemented
 */
#define UNIMPLEMENTED_RETURN_POINTER NULL

/**
 * @brief Run unit tests
*/
void run_tests(void);

/**
 * @brief Test Step 2a: file Doxygen comment
 */
void test_2a_file_doxygen(void);

/**
 * @brief Test Step 2b: include hw3_rnp.h
 */
void test_2b_include_hw1_wvuep_h(void);

/**
 * @brief Tests get_programmer_name function
*/
void test_2c_get_programmer_name(void);

/**
 * @brief Tests prompt_target_enrollment function prompt
*/
void test_2d_prompt_target_enrollment_prompt(void);

/**
 * @brief Tests prompt_target_enrollment function with alphabetic input
*/
void test_2d_prompt_target_enrollment_nonnumeric(void);

/**
 * @brief Tests prompt_target_enrollment function with zero input
*/
void test_2d_prompt_target_enrollment_zero(void);

/**
 * @brief Tests prompt_target_enrollment function with negative input
*/
void test_2d_prompt_target_enrollment_negative(void);

/**
 * @brief Tests prompt_target_enrollment function with positive input
*/
void test_2d_prompt_target_enrollment_positive(void);

/**
 * @brief Tests calculate_growth_rate function with zero-growth target enrollment
*/
void test_2e_calculate_growth_rate_zero(void);

/**
 * @brief Tests calculate_growth_rate function with positive-growth target enrollment
*/
void test_2e_calculate_growth_rate_positive(void);

/**
 * @brief Tests calculate_growth_rate function with negative-growth target enrollment
*/
void test_2e_calculate_growth_rate_negative(void);

/**
 * @brief Tests get_growth_rate_description function with negative growth rate percentage
*/
void test_2f_get_growth_rate_description_negative(void);

/**
 * @brief Tests get_growth_rate_description function with reasonable growth rate percentage
*/
void test_2f_get_growth_rate_description_reasonable(void);

/**
 * @brief Tests get_growth_rate_description function with ambitious growth rate percentage
*/
void test_2f_get_growth_rate_description_ambitious(void);

/**
 * @brief Tests get_growth_rate_description function with high growth rate percentage
*/
void test_2f_get_growth_rate_description_high(void);

/**
 * @brief Tests get_growth_rate_description function with unreasonable growth rate percentage
*/
void test_2f_get_growth_rate_description_unreasonable(void);

/**
 * @brief Tests print_growth_rate function
*/
void test_2g_print_growth_rate(void);

/**
 * @brief Tests calculate_enrollment_estimate function
*/
void test_2h_calculate_enrollment_estimate(void);

/**
 * @brief Tests first line of output from print_enrollment_estimates function
*/
void test_2i_print_enrollment_estimates_first(void);

/**
 * @brief Tests last line of output from print_enrollment_estimates function
*/
void test_2i_print_enrollment_estimates_last(void);

/**
 * @brief Function to get the name of the programmer
 * @return String with the name of the programmer
 */
const char* helper_get_programmer_name(void);

/**
 * @brief Prompts the user to enter their enrollment target for the specified year
 * @param target_year Year to prompt for target enrollment
 * @return User-specified value
 */
int helper_prompt_target_enrollment(int target_year);

/**
 * @brief Calculate annual growth rate using the formula ((target_enrollment/initial_enrollment)^(1/years) - 1)
 * @param initial_enrollment Enrollment in initial_year
 * @param target_enrollment Target enrollment for end_year
 * @param initial_year Year for initial enrollment
 * @param target_year Year for target enrollment
 * @return Growth rate
 */
double helper_calculate_growth_rate(int initial_enrollment, int target_enrollment, int initial_year, int target_year);

/**
 * @brief Get description of growth rate likelihood of occurring.
 * @param growth_rate Required annual growth rate
 * @return String describing the growth rate
*/
const char* helper_get_growth_rate_description(double growth_rate);

/**
 * @brief Print growth rate and a description of the rate
 * @param growth_rate Required growth rate
 */
void helper_print_growth_rate(double growth_rate);

/**
 * @brief Calculate the estimated enrollment in estimate_year
 * @param initial_enrollment Enrollment in initial_year
 * @param growth_rate Required annual growth rate
 * @param initial_year Year for initial enrollment
 * @param estimate_year Year for which to calculate enrollment estimate
 */
int helper_calculate_enrollment_estimate(int initial_enrollment, double growth_rate, int initial_year, int estimate_year);

/**
 * @brief Print the estimated enrollment for each year between initial_year and end_year
 * @param initial_enrollment Enrollment in initial_year
 * @param growth_rate Required annual growth rate
 * @param initial_year Year for initial enrollment
 * @param end_year Last year for printing enrollment
 */
void helper_print_enrollment_estimates(int initial_enrollment, double growth_rate, int initial_year, int end_year);

/**
 * @brief Trims leading and trailing whitespace
 * @param string Strim to trim (modified in place)
 * @return New dynamically allocating string containing trimmed version of input string, or NULL if it cannot be allocated
*/
char* test_support_trim(const char* string);
