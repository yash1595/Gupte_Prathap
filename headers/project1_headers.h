#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#define BUFF 256
#define MAX  256

struct timeval start_t,end_t;


 

/* Functions */
 void menu();                               // Displays the help menu and assigns string variables.
 uint32_t* allocate();                      // Allocates memory based on number of bytes entered by the user.
 void free_mem(uint32_t* allocated_mem);    // Frees memory by taking the address to be freed from the user.
 void user_input(void);                     // Takes the user input and stored it in a string
 void main_interface(void);                 // Calls functions based on what the user enters.
 void add_data(void);                       // Adds the data in the memory allocated.
 void resizing_freed_array(uint32_t);           // Resizes the array so as to not exhaust the array space.
 void _display(void);                       // Displays the data and corresponding location at which it is stored.
 void freeAll(void);                        // Frees all the allocated memories at a go.
 void invert_data(void);                    // Inverts data in a specified area of memory.
 void _random(void);                        // Generates a random sequence in specified area of memory.
 void defaultMessage(void);                 // Displays the main menu
 void exit_free(void);
 void function_pointer_assignemnt(void);
 void verify(void);
 void display_offset(void);
 void display_options(void);
 long offset_mem(void);
 long input_address_mode(void);
 void summary_mem(void);

 uint32_t*(*fallocate)(void);
 void(*fmenu)(void);
 void(*finvert_data)(void);
 void(*fadd_data)(void);
 void(*ffree_mem)(uint32_t*);
 void(*fuser_input)(void);
 void(*fmain_interface)(void);
 void(*fresizing_freed_array)(uint32_t);
 void(*f_display)(void);
 void(*ffreeAll)(void);
 void(*finvert_data)(void);
 void(*f_random)(void);
 void(*fdefaultMessage)(void);
 void(*fexit_free)(void);
 void (*fverify)(void);
 void (*fdisplay_offset)(void);
 void (*fdisplay_options)(void);
 long (*foffset_mem)(void);
 long (*finput_address_mode)(void);
 void (*fsummary_mem)(void);



