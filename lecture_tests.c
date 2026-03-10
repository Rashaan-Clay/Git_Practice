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
 * VARTYPES: 
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
 * POINTER: 
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
 *       You dereference pointers to change the value in memory. THIS IS THE DEREFERENCING OPERATOR *
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
 *                   In these cases, if the called function changes value, calling function sees the new variable since it's pointing to a memory location.
 *   Variable Lifetime:
 *       Automatic lifetime is when a varaible is created within a block and then destory when exited from that block of code. A good example are loops, once you declare the iterator and it exists that blo
 *       Static lifetime is when the variable is created, used, then destroyed. Think about making a global varaible and a function variable, one is only avaiable within its function and the other is avaiable all throughout the program.
 *       Dynamic lifetime is allocated and deallocated memory. malloc() and free(): (PROGRAMMER MUST FREE MEMORY BEFORE TERMINATION)  
 *           
 * POINTERS:
 *    First thing covered are void poitners. These are NOT defined pointers that do not have a specified type, usually when you are unsure of what type of value it will store.
 *    This is a method of dynamically allocating memory and is called by: void*
 *    Void pointers can be a bit tricky to use and you shoudl only use them when necessary. Pointer arithmetic is not supported with these and you the type must be casted BEFORE you can dereference them
 *    Once the pointer has been casted, you can them use it as if it were a regular pointer.
 *    You either need to create the array outside of the function and pass it to the function as an argument, or create the array inside the function using malloc and then return it as an int*.
 *    
 *    Dynamic Mememory: There are methods of dynamically allocating chunks of memory at once. But C can be a bit dangerous as it does not automatically free allocated memory when pointers are destroy. That job is left to to programmers; and must be doneto avoid memory leaks. Memory is automatically freed on termination
 *    
 *    You request memory by using: malloc(), found in <stdlib.h> to request a specific number of bytes of memory. malloc() returns a void pointer to the allocated memory, to ensure that you are not OVER allocating memory, you can use sizeof() to find how many bytes of memory you require
 *    use malloc whenever you dont know how much memory you will need in advance; espescially in DS
 *    If malloc returns NULL then it was unable to allocate memory and it is a good time to end your program. The exit() will do as such no matter which function you're currently in.
 * 
 *    Because strings in C are char-based, we face an issue of lifetime when trying to return a string from a function. So instead we should use malloc to allocate memory for the string an return it as a char*
 *    
 *    Freeing memory is deallocating any dynamically allocated memory. Anything that you do not manually free will be freed AT TERMINATION
 *    free(*memoryPtr), Pointer to memory to be deallocated and Returns void.
 *    The free function does not change the value of the pointer passed to it. It is good practice for the programmer manually to set the pointer to NULL after calling free on it to make it clear the pointer is no longer valid.
 * 
 *    If you have allocated too much memory, you can realloc the amount that was originally freed. realloc() will return a pointer to the RESIZED memory block which may be in a different location than before.
 *    Do not reuse the same pointer that was used to alloc memory to then realloc, you will lose access to the original memory block.
 *    Generally you shoild create a tempPtr = NULL, to ensure that you dont lose access to the original block of memory.
 * 
 *    realloc(*memoryPtr, size); Pointer to currently allocated memory and the number of bytes after resizinig. returns void pointers
 *    
 *    You should avoid dynamically allocating memory WHENEVER possible, only used when you do not know the size requirements in advanced. Even in such cases, its much safer to just allocated a large fixed amount.
 * 
 * 
 * 
 *    STRUCTS:
 *  
 *    Commonly used for data structures like linked lists or organizing data read from/written files
 *    structs are used to contain sets of related data; typically for organizing data read from/written to files.
 *    Difference between classes and structs:
 *       
 *    structs cannot contain functions/methods
 *       Everything is public
 *       cannot be inherited from.
 * 
 *    You add structs to the top of your file, below preprocessor derictives.
 * 
 *    Without initializing a struct:
 *       Elements within local scope will maintain the values that were alreadying stored in memory.
 *       
 *       In file-scope, pointers will be set to NULL, variables are 0, and an array will be set to all 0's.
 * 
 *  
 *    Using typedef is an alias keyword, and seems to only save typing and initializing for struct type. If used, you may not need to create a tag for your struct.
 *    
 *    When inside a struct, C cannot infer the size of an array simply off its initializer, thus does not allocate memory. So you could used a FIXED size array within a struct,
 *    but dynamically, arrary must be initilized last within the struct and contain braces, and use sizeof to determine the amount of memory needed for the struct but you must find the memory needed
 *    for the array on your own.
 *    
 *    Same thing applies for array initialized with pointers.
 * 
 *    To create another copy of your struct simply, initialize your struct to another variable. EX: struct employee bmp2 = bmp;
 *    
 *    You can pass structs byh value & reference:
 *       by value: a copy of the struct is created when passed in function, so changed made in the function call dont change calling functions
 *                unless using a pointer to do so.
 * 
 *       By reference: The address of the struct is provided to the call, and the reference in the call:
 *       EX: pass_by_ref(struct employee*); --> pass_by_ref(&bmp);
 * 
 *    lastly, sizeof can be used to measure the size of your struct in bytes. Make sure to use size_t and %zu when printing size.
 *                
 */

 int main()
 {
    printf("Just the lecture slides biddawg!");
    return 0;
 }


