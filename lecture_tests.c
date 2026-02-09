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
 * 
 *  
 */

 int main()
 {
    printf("Just the lecture slides biddawg!");
    return 0;
 }