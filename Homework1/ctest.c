/**
 * @file ctest.c
 * @brief Source code file for WVU CTest testing framework
 * @author Brian Powell
 * @version 1.23
 *
 * Place this file in the same directory as your own source code and add it to your project.
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 *
 * Requires the following linker flags for GCC in Visual Studio:
 * -Wl,--no-as-needed -ldl
 *
 * No linker flags required for Xcode.
 */

// NOLINTBEGIN
// ReSharper disable CppDFAMemoryLeak
// ReSharper disable CppLocalVariableMayBeConst
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppUnusedIncludeDirective
// ReSharper disable CppRedundantElseKeyword
// ReSharper disable CppRedundantElseKeywordInsideCompoundStatement

// Use GNU source code for redirecting output and overwriting functions
#define _GNU_SOURCE // NOLINT(*-reserved-identifier)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ctest.h"
#include <stdbool.h>
#include <regex.h>
#include <errno.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>

// OS-specific includes
#ifdef __APPLE__
	#include <malloc/malloc.h>
#else
	#include <malloc.h>
#endif

// Define file to store capture output - comment out to not capture output
//#define CAPTURE_OUTPUT "captured_output.txt"

char* add_regex_anchors(const char* pattern)
{
	// Determine length of search pattern
	size_t pattern_length = strlen(pattern);
	size_t anchored_pattern_length = pattern_length + 2; // Add 2 for ^ and $

	// Malloc memory for new anchored
	char* anchored_pattern = malloc(anchored_pattern_length + 1); // +1 for null terminator
	if (anchored_pattern == NULL)
	{
		fprintf(stderr, "Could not allocate memory: %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Build anchored pattern
	anchored_pattern[0] = '^';
	strncpy(anchored_pattern + 1, pattern, pattern_length);
	anchored_pattern[anchored_pattern_length - 1] = '$';
	anchored_pattern[anchored_pattern_length] = '\0';

	return anchored_pattern;
}

bool are_equals_regex(const char* pattern, const char* string)
{
	// Add anchors to regex pattern to ensure full match
	char* anchored_pattern = add_regex_anchors(pattern);

	// Call does_string_contain function
	bool does_contain_pattern = does_string_contain(anchored_pattern, string);

	// Free memory
	free(anchored_pattern);
	anchored_pattern = NULL;

	return does_contain_pattern;
}

char* build_path_in_current_directory(const char* filename)
{
	// Get current directory
	char* current_directory = get_directory(__FILE__);

	// Call build_path() to finish building path
	char* path = build_path(current_directory, filename);

	// Free directory
	free(current_directory);
	current_directory = NULL;

	// ReSharper disable once CppDFAMemoryLeak
	return path;
}

char* build_path(const char* directory, const char* filename)
{
	// If directory is NULL, return filename
	if (directory == NULL)
	{
		return duplicate_string(filename);
	}

	// If filename is NULL, return NULL
	if (filename == NULL)
	{
		return NULL;
	}

	// Build path incorporating directory and specified file
	char* path = malloc(strlen(directory) + strlen(filename) + 1);
	if (path == NULL)
	{
		fprintf(stderr, "Could not allocate memory: %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Concatenate directory and path
	strcpy(path, directory);
	strcat(path, filename);

	return path;
}

char* clean_newlines(const char* input)
{
	// Loop to replace \r\n with \n
	char* cleaned_newlines = duplicate_string(input);

	// Return if cleaned_newlines is NULL
	if (cleaned_newlines == NULL)
	{
		return NULL;
	}

	char* newline = strstr(cleaned_newlines, "\r\n");
	while (newline != NULL) {
		// Move rest of string up one position
		memmove(newline, newline + 1, strlen(cleaned_newlines) - (size_t)(newline - cleaned_newlines) + 1 + 1); // Add 1 to include null terminator
		newline = strstr(cleaned_newlines, "\r\n");
	}

	return cleaned_newlines;
}

char* clean_string(const char* input, enum text_matching text_matching_options)
{
	// Return NULL if string is NULL
	if (input == NULL) {
		return NULL;
	}

	// If text_matching is 0, set to flexible matching
	if (text_matching_options == 0) {
		text_matching_options = FLEXIBLE;
	}

	// Always strip whitespace
	char* cleaned = duplicate_string(input);
	char* end = cleaned + strlen(cleaned) - 1;
	while (end > cleaned && isspace((unsigned char)*end)) {
		*end-- = '\0';
	}

	// Always clean up newlines
	cleaned = clean_newlines(cleaned);

	// If flexible matching, add all sub-options
	if (text_matching_options & FLEXIBLE) {
		text_matching_options |= IGNORE_CASE | IGNORE_PUNCTUATION | IGNORE_WHITESPACE | IGNORE_LINE_BREAKS | IGNORE_PERIODS | IGNORE_PUNCTUATION;
	}

	// If ignore case, convert to lower
	if (text_matching_options & IGNORE_CASE) {
		for (int i = 0; cleaned[i]; i++) {
			cleaned[i] = (char)tolower((unsigned char)cleaned[i]);
		}
	}

	// If ignore whitespace, remove spaces
	if (text_matching_options & IGNORE_WHITESPACE) {
		char* src = cleaned;
		char* dst = cleaned;
		while (*src != '\0') {
			if (!isspace((unsigned char)*src)) {
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
	}

	// If ignore line breaks, remove newlines
	if (text_matching_options & IGNORE_LINE_BREAKS) {
		char* src = cleaned;
		char* dst = cleaned;
		while (*src != '\0') {
			if (*src != '\n') {
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
	}

	// If ignore periods, remove periods
	if (text_matching_options & IGNORE_PERIODS) {
		char* src = cleaned;
		char* dst = cleaned;
		while (*src != '\0') {
			if (*src != '.') {
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
	}

	// If ignore punctuation, remove punctuation
	if (text_matching_options & IGNORE_PUNCTUATION) {
		char* src = cleaned;
		char* dst = cleaned;
		while (*src != '\0') {
			if (!ispunct((unsigned char)*src)) {
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
	}

	return cleaned;
}

size_t ctest_get_malloc_size(void* ptr)
{
	// Return 0 if pointer is NULL or not valid
	if (!is_pointer_valid(ptr))
	{
		return 0;
	}

	// Get size
#ifdef __APPLE__ 
	return malloc_size(ptr);
#else 
	return malloc_usable_size(ptr);
#endif 
}

bool does_file_exist(const char* path)
{
	// Attempt to open file
	FILE* filePtr = fopen(path, "r");

	// See if file exists
	if (filePtr != NULL) {
		// File exists

		// Close file
		fclose(filePtr);
		filePtr = NULL;

		return true; // File exists
	}
	else {
		// File does not exist
		return false;
	}
}

char* duplicate_string(const char* string) {
	// Return NULL if string is NULL
	if (string == NULL) {
		return NULL;
	}

	// Allocate memory for the new string
	char* duplicatePtr = malloc(strlen(string) + 1);
	if (duplicatePtr == NULL) {
		// Memory allocation failed
		return NULL;
	}

	// Copy the original string to the new memory location
	strcpy(duplicatePtr, string);

	return duplicatePtr;
}

bool does_file_contain(const char* pattern, const char* path)
{
	// Read file
	char* file_contentsPtr = read_file(path);

	// Check file contents
	bool contains = does_string_contain(pattern, file_contentsPtr);

	// Free memory from file contents
	free(file_contentsPtr);
	file_contentsPtr = NULL;

	return contains;
}

#ifdef CAPTURE_OUTPUT
bool does_captured_output_contain(const char* pattern)
{
	// Get file output
	char* captured_output = get_captured_output();

	// Check file contents
	bool contains = does_string_contain(pattern, captured_output);

	// Free memory from file contents
	free(captured_output);
	captured_output = NULL;

	return contains;
}
#endif

char* get_directory(const char* path)
{
	// String to contain directory path
	char* directory = NULL;

	// Find last slash, using appropriate slash for OS
	#ifdef _WIN32
		// Use backslash for Windows
		const char* last_slash = strrchr(path, '\\');
	#else
		// Use forward slash for Unix-based systems
		const char* last_slash = strrchr(path, '/');
	#endif

	// If slash was found, use it to isolate directory name from path
	if (last_slash != NULL)
	{
		// Allocate memory for directory name
		size_t directoryLength = (size_t)(last_slash - path + 1);
		// ReSharper disable once CppDFAMemoryLeak
		directory = malloc(directoryLength + 1);
		if (directory == NULL)
		{
			printf("Could not malloc memory: %s.\n", strerror(errno));
			exit(1);
		}

		// Isolate directory part of name
		strncpy(directory, path, directoryLength);

		// Null-terminate directory name
		directory[directoryLength] = '\0';
	}
	else
	{
		// Return ./ if there was no full path
		// ReSharper disable once CppDFAMemoryLeak
		directory = malloc(3 * sizeof(char));
		if (directory == NULL)
		{
			printf("Could not malloc memory: %s.\n", strerror(errno));
			exit(1);
		}

		// Copy string
		strcpy(directory, "./");
	}

	return directory;
}

size_t get_file_size(const char* path)
{
	// Attempt to open file.
	FILE* filePtr = fopen(path, "r");
	if (filePtr == NULL) {
		fprintf(stderr, "File %s not found.\n", path);
		return 0;
	}

	// Determine size of file
	fseek(filePtr, 0, SEEK_END);
	size_t file_size = (size_t)ftell(filePtr);

	// Close file
	fclose(filePtr);
	filePtr = NULL;

	return file_size;
}

bool does_string_contain(const char* pattern, const char* string)
{
	// If either string is NULL, return false
	if (pattern == NULL || string == NULL) {
		return false;
	}

	// Compile regex pattern
	regex_t regex;
	int result = regcomp(&regex, pattern, REG_EXTENDED);
	if (result != 0) {
		// An error occurred

		// Build and display error message
		char errorBuffer[100];
		regerror(result, &regex, errorBuffer, sizeof(errorBuffer));
		fprintf(stderr, "Regex compilation error: %s\n", errorBuffer);
		regfree(&regex);

		return false;
	}

	// Attempt to match regex
	result = regexec(&regex, string, 0, NULL, 0);
	regfree(&regex);

	// Determine if pattern matched string
	if (result == 0)
	{
		return true;
	}
	else if (result == REG_NOMATCH)
	{
		return false;
	}
	else
	{
		// Build and display error message
		char errorBuffer[100];
		regerror(result, &regex, errorBuffer, sizeof(errorBuffer));
		fprintf(stderr, "Regex matching error: %s\n", errorBuffer);

		return false;
	}
}

/**
 * @brief Tracks the location of original malloc function
 */
static void* (*real_malloc)(size_t) = NULL;

/**
 * @brief Overridden version of malloc to initialize memory to 0xFFFFFFFFFFFFFFFF
 * @param size Number of bytes requested
 * @return Pointer to allocated memory or NULL if allocation failed
 */
// ReSharper disable once CppParameterNamesMismatch
void* malloc(size_t size)
{
	// Store original malloc function prior to remapping
	if (real_malloc == NULL)
	{
		// Locate original malloc function
		real_malloc = dlsym(RTLD_NEXT, "malloc");

		// Check for errors
		if (real_malloc == NULL)
		{
			fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
		}
	}

	// Pointer to new memory
	void* memoryPtr = NULL;

	// Call original malloc function
	memoryPtr = real_malloc(size);

	// If memory was allocated, set it to 0xFFFFFFFFFFFFFFFF
	if (memoryPtr != NULL)
	{
		memset(memoryPtr, 0xFF, size);
	}

	return memoryPtr;
}

char* read_file(const char* path)
{
	// Exit if path is NULL
	if (path == NULL) {
		fprintf(stderr, "Path is NULL.\n");
		return NULL;
	}

	// Get file size
	size_t file_size = get_file_size(path);

	// Attempt to open file.
	FILE* filePtr = fopen(path, "r");
	if (filePtr == NULL) {
		fprintf(stderr, "File %s not found.\n", path);
		return NULL;
	}

	// Malloc memory for file
	char* buffer = malloc(file_size + 1);
	if (buffer == NULL) {
		fprintf(stderr, "Could not allocate memory: %s.\n", strerror(errno));
		return NULL;
	}

	// Read file contents
	size_t bytes_read = fread(buffer, 1, file_size, filePtr);
	if (bytes_read != file_size) {
		fprintf(stderr,"Error reading file: %s.\n", strerror(errno));
		return NULL;
	}

	// Null terminate string
	buffer[file_size] = '\0';

	// Close file
	fclose(filePtr);
	filePtr = NULL;

	return buffer;
}

char* read_source_code_file(const char* filename)
{
	// Get directory this source code file is in
	char* directory = get_directory(__FILE__);

	// Build path incorporating directory and specified file
	char* path = build_path(directory, filename);

	// Free directory
	free(directory);
	directory = NULL;

	// Read file
	char* source_code = read_file(path);

	// Free path info
	free(path);
	path = NULL;

	// Return file
	// ReSharper disable once CppDFAMemoryLeak
	return source_code;
}

char* write_file(const char* path, const char* contents, const bool overwrite)
{
	// If file exists, check if we should overwrite
	FILE* filePtr = fopen(path, "r");
	char* old_contents = NULL;
	if (filePtr != NULL) {
		fclose(filePtr);

		// Load existing contents of file
		old_contents = read_file(path);

		// If file content exists, and we were not set to overwrite, display error and return
		if (!overwrite) {
			// Print error message
			fprintf(stderr, "File %s already exists. Function was set to not overwrite.\n", path);

			// Free old_contents
			free(old_contents);
			old_contents = NULL;
			
			return NULL;
		}
	}

	// Write contents to file
	filePtr = fopen(path, "w");
	if (filePtr == NULL) {
		// Print error message
		fprintf(stderr, "Error writing to file %s: %s.\n", path, strerror(errno));
		
		exit(EXIT_FAILURE);
	}

	// Write to file
	fputs(contents, filePtr);

	// Close file
	fclose(filePtr);
	filePtr = NULL;

	return old_contents;
}

#ifdef CAPTURE_OUTPUT
int putchar(int c)
{
	// Open file for storing output
	FILE* filePtr = fopen(CAPTURE_OUTPUT, "a");
	if (filePtr == NULL)
	{
		fprintf(stderr, "Error opening file for writing: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Write char to file
	fputc(c, filePtr);

	// Write char to screen
	int fputc_return = fputc(c, stdout);

	// Close captured output file
	fclose(filePtr);
	filePtr = NULL;

	return fputc_return;
}

int printf(const char* __restrict __fmt, ...)
{
	// Open file for storing output
	FILE* filePtr = fopen(CAPTURE_OUTPUT, "a");
	if (filePtr == NULL)
	{
		fprintf(stderr, "Error opening file for writing: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Use variadic arguments to print to file
	va_list args_file;
	va_start(args_file, __fmt);
	vfprintf(filePtr, __fmt, args_file);
	va_end(args_file);

	// Use variadic arguments to print to screen
	va_list args_screen;
	va_start(args_screen, __fmt);
	int printf_return = vprintf(__fmt, args_screen);
	va_end(args_screen);

	// Close captured output file
	fclose(filePtr);
	filePtr = NULL;

	return printf_return;
}

int puts(const char* __s)
{
	return printf("%s\n", __s);
}

/**
 * @brief Tracks the location of original fprintf function
 */
static int (*real_fprintf)(FILE* __stream, const char*, ...) = NULL;

int fprintf(FILE* __restrict __stream, const char* __restrict __fmt, ...)
{
	// Store original malloc function prior to remapping
	if (real_fprintf == NULL)
	{
		// Locate original malloc function
		real_fprintf = dlsym(RTLD_NEXT, "fprintf");

		// Check for errors
		if (real_fprintf == NULL)
		{
			real_fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
		}
	}

	// Use variadic arguments to print to screen
	va_list args_screen;
	va_start(args_screen, __fmt);
	int fprintf_return = vfprintf(__stream, __fmt, args_screen);
	va_end(args_screen);

	// Print to file if target was stdout or stderr
	if (__stream == stdout || __stream == stderr)
	{
		// Open file for storing output
		FILE* filePtr = fopen(CAPTURE_OUTPUT, "a");
		if (filePtr == NULL)
		{
			real_fprintf(stderr, "Error opening file for writing: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		// Use variadic arguments to print to file
		va_list args_file;
		va_start(args_file, __fmt);
		vfprintf(filePtr, __fmt, args_file);
		va_end(args_file);

		// Close captured output file
		fclose(filePtr);
		filePtr = NULL;
	}

	return fprintf_return;
}

char* get_captured_output(void)
{
	#ifndef CAPTURE_OUTPUT
		fprintf(stderr, "Output is not being captured.\n");
		return NULL;
	#else
		// Check to see if file exists
		if (!does_file_exist(CAPTURE_OUTPUT))
		{
			fprintf(stderr, "File %s does not exist.\n", CAPTURE_OUTPUT);
			return NULL;
		}

		// Read file
		char* file_contentsPtr = read_file(CAPTURE_OUTPUT);

		// Return file contents
		return file_contentsPtr;
	#endif
}
#endif

/**
 * @brief Buffer for jumping to in case of a caught signal
 */
static sigjmp_buf jump_buffer;

// ReSharper disable once CppParameterNeverUsed
void sigsegv_handler(int sig)
{
	// Jump to specified location
	siglongjmp(jump_buffer, 1);
}

bool is_pointer_null_or_valid(const void* ptr)
{
	// Return true for NULL pointers
	if (ptr == NULL)
	{
		return true;
	}

	// Do other checks to see if valid
	return is_pointer_valid(ptr);
}

bool is_pointer_valid(const void* ptr)
{
	// Treat NULL pointers as not valid
	if (ptr == NULL)
	{
		return false;
	}

	// Configure signal handler	
	struct sigaction sa;
	sa.sa_handler = sigsegv_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	// Change signal handler, storing old one
	struct sigaction old_sa;
	sigaction(SIGSEGV, &sa, &old_sa);

	// Figure out if signal handler fired
	if (sigsetjmp(jump_buffer, 1) == 0)
	{
		// Either first try, or signal handler did not fire meaning pointer was valid

		// Try to read from pointer, with volatile keyword keeping optimizers from skipping the read operation
		volatile char tmp = *(volatile char*)ptr;

		// Suppress unused variable warning
		(void)tmp;

		// Reset signal handler
		sigaction(SIGSEGV, &old_sa, NULL);
	
		// Pointer is valid, assuming that signal handler did not fire
		return true;
	}
	else
	{
		// Signal handler did fire, so pointer was invalid

		// Reset signal handler
		sigaction(SIGSEGV, &old_sa, NULL);

		// Pointer is invalid
		return false;
	}
}

bool is_pointer_read_only(const void* ptr)
{
	// Configure signal handler	
	struct sigaction sa;
	sa.sa_handler = sigsegv_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	// Change signal handler, storing old one
	struct sigaction old_sa;
	sigaction(SIGSEGV, &sa, &old_sa);

	// Figure out if signal handler fired
	if (sigsetjmp(jump_buffer, 1) == 0)
	{
		// Signal handler did not fire, so pointer was not read only

		// Try to write its current value back to the pointer to see if it's read-only, with volatile keyword keeping optimizers from skipping the operation
		*(volatile char*)ptr = *(volatile char*)ptr;

		// Reset signal handler
		sigaction(SIGSEGV, &old_sa, NULL);

		// Pointer is not read-only
		return false;
	}
	else
	{
		// Signal handler did fire, so pointer was read-only

		// Reset signal handler
		sigaction(SIGSEGV, &old_sa, NULL);

		// Pointer is read-only
		return true;
	}
}

int robust_nanosleep(const int seconds, const long nanoseconds)
{
	// Configure requested time
	struct timespec sleep_time = { .tv_sec = seconds, .tv_nsec = nanoseconds };

	// Structure to hold the remaining time after an interruption.
	struct timespec remaining_time;

	// Track status from calling nanosleep
	int status;

	// Call nanosleep in a loop to handle interruptions from signals
	do
	{
		// Attempt to sleep
		status = nanosleep(&sleep_time, &remaining_time);

		// If status is 0, the sleep completed successfully
		if (status == 0)
		{
			return 0;
		}

		// If status is -1, an error occurred. Check if it was EINTR (signal interruption).
		if (errno == EINTR)
		{
			// A signal interrupted the sleep. Restart sleep with time from remaining_time object.
			sleep_time = remaining_time;
		}
		else
		{
			// A different, unhandled error occurred
			return -1;
		}
	}
	while (status == -1 && errno == EINTR); // Continue loop only if interrupted by EINTR

	return 0; // Should be unreachable given loop logic, but added for completeness
}

bool is_printable(const char* string)
{
	// Check to see if pointer is valid and not NULL
	if (!is_pointer_valid(string))
	{
		return false;
	}

	// Check if string is empty
	if (strlen(string) == 0)
	{
		return false;
	}

	// Loop to look for non-printable characters
	for (size_t i = 0; i < strlen(string); i++)
	{
		// Check if character is not printable
		if (!isprint(string[i]))
		{
			return false;
		}
	}

	return true;
}

char* fix_string_null_termination(const char* string)
{
	// Return NULL if string is NULL or not valid
	if (!is_pointer_valid(string))
	{
		return NULL;
	}

	// Malloc new string
	char* fixedPtr = malloc(strlen(string) + 1);
	if (fixedPtr == NULL)
	{
		return NULL;
	}

	// Initialize to null
	memset(fixedPtr, 0, strlen(string) + 1);

	// Copy string
	strncpy(fixedPtr, string, strlen(string));

	// Get position of last character, using signed type to avoid looping around
	int position = (int) strlen(fixedPtr) - 1;

	// Loop from end of string, moving left
	while (position >= 0 && !isprint(fixedPtr[position]))
	{
		fixedPtr[position] = '\0';
		position--;
	}

	return fixedPtr;
}

// NOLINTEND