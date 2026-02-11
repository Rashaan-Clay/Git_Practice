#include <stdio.h>

/**
 * The compilation Process is as follows: 
 *      (1): Source codes goes into plain text files
 *      (2): Once completed, the compiler is called
 *      (3): The compiler calls the preprocessor which handles all the preprocessor directives
 *      (4): Once that is finished, the code is ready to compile; it is then changed into machine or object code.
 *      (5): A linker takes the code and literally links it with any external libraries that are included within the files. So the standard C library is one. The linker also produces an executable file for the corresponding OS and CPU arch.
 *      (6): Now the code is ready to run and the CPU can then execute the program once loaded into memory.
 * 
 * Variable Types: 
 *      Integer | int | 4 bytes | range is from +-2million
 *      Unsigned | unsigned int| 4 bytes and from 0 to 4mil
 *      Long | long | 4 or 8 bytes depending on windows arch| and varies by size
 *      Long Long | long long | 8 bytes | 9*10^+-18
 *      Short Int | short | 2 bytes | -+32,000
 *      Single Precision | float | 4 byte | 1.2*10^-38 to 3.4*10^38
 *      Double Precision | double | 8 bytes | unnecessary
 *      Character | char | 1 byte | 0 - 255, normally ASCII range
 *      Boolean | bool | 1 byte | 0 - 1
 * 
 * Pointers: 
 *       Pointers are variables that store memeory adresses
 *       They metaphorically point at memory locations you'd want to acess and modify
 *       You declare a point by putting a * before the name of each pointer, and must have the same variable type as they're pointing to
 *       If a variable already exists, you can reference its adress by using the & operator.
 *       You're usually not worried about the pointer itself, just the value that it points to. 
 *          
 *          Ex: int a = 5;
 *              int* aPtr = &a;
 *              int b = *aPtr + 3;
 * 
 *       * The last line of code will dereference aPtr and gives us the value that it was once pointing at and completing the opeartion given.
 * 
 *       You dereference pointers to change the value in memory
 *       There is such thing as pointing at nothing or NULL. If you have not already allocated memory and need to initialize a pointer; you can declare it as a NULL value: int* ptr = NULL;
 *       But you cannot dereference a null pointer. 
 *       
 *       There are two ways to pass arguments to a function: Pass-by-value & Pass-by-reference
 * 
 *       Pass-by-value:
 *                   void change_value(int a, int b) <-- copy of variable's value is made and provided to called function
 * 
 *                   void change_value(int* aPtr, int* bPtr) <-- Passing through memory address of variables in the calling function.
 *               
 *             In these cases, if the called function changes value, calling function sees the new variable since it's pointing to a memory location.
 *             
 *         
 */

 int main()
 {
    printf("Just the lecture slides biddawg!");
    return 0;
 }