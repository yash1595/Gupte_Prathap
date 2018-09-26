/******************************************************************************
Project Partners: 1.Lekshmi Prathap
                  2.Yash Gupte
Current version created on: 09-24-2018
Version Specifications:
-------------------------------------------------------------------------------
This version takes the input as "allocate" and "freemem"
This version takes hexadecimal input from user to clear bytes
v4: This version makes the code 32bit-unsigned aligned.
-------------------------------------------------------------------------------
v5:This version takes address from user to free space.
Blocks double freeing.
-------------------------------------------------------------------------------
v6: Resolved issue for linux 64bit boundary
    created a make file with run commands.
-------------------------------------------------------------------------------
v7: Removed goto and inserted a function call instead.
-------------------------------------------------------------------------------
v8: 1.Added the exit function.
             2.Added function to store data in a 
             memory location which has been allocated.
-------------------------------------------------------------------------------
v9: 1. Resolved the allocate->free->allocate-> issue
             2. Removed the already_freed[] for the above issue.
-------------------------------------------------------------------------------
v10: 1. Array shift for resizing the array[]
              2. Display data.
-------------------------------------------------------------------------------
v11(current): 1. free_all function
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BUFF 15 
#define MAX  20

/* Functions */
 void menu();                               // Displays the help menu and assigns string variables.
 uint32_t* allocate();                      // Allocates memory based on number of bytes entered by the user.
 void free_mem(uint32_t* allocated_mem);    // Frees memory by taking the address to be freed from the user.
 void user_input(void);                     // Takes the user input and stored it in a string
 void main_interface(void);                 // Calls functions based on what the user enters.
 void add_data(void);                       // Adds the data in the memory allocated.
 void resizing_freed_array(void);           // Resizes the array so as to not exhaust the array space.
 void _display(void);                       // Displays the data and corresponding location at which it is stored.
 void freeAll(void);                        // This function frees all the allocated memories at a go.

/* Variables */
 uint32_t input=2;
 uint32_t bytes=0;
 uint32_t max_bytes=MAX;
 uint32_t a_flag=0;
 uint32_t mem_alloc_check=0;
 uint32_t mem_free_count=0;
 uint32_t j=0,i=0;
 uint32_t free_all_input=0;
 uint32_t donot_free=0;
 uint32_t data_to_store = 0;
 uint32_t* allocated_mem=0;
 uint32_t location_to_free=0;
 uint32_t invalid_mem=1;
 uint32_t array_count=0;
 long temp=0;
 long mem_free=0;
 long mem_to_store=0;

 uint32_t* array[MAX]={0};
 
 char str[BUFF];
 char alloc[BUFF];
 char freemem[BUFF];
 char help[BUFF];
 char quit[BUFF];
 char addData[BUFF];
 char display[BUFF];
 char free_all[BUFF];
 
 /* Main Function */

 int main()
 {
     menu();
     while(1)
     {
      user_input();
      main_interface();
     }
        return 0;
}
 
 void menu()
 {  puts("Welcome! This is the main menu:\n");
    printf("Type in 'allocate' followed by number of bytes(<20) to allocate x bytes of memory\n");
    printf("Type in 'freemem' followed by index number to deallocate allocated bytes of memory\n");
    printf("Type in 'help' for the list of functions\n");
    printf("Type in 'exit' to exit the program\n");
    printf("Type in 'add_data' to add data in the program\n");
    printf("Type in 'display' to display data in the program\n");
    printf("Type in 'free_all' to free all data in the program\n");
    strcpy(alloc,"allocate\n");
    strcpy(freemem,"freemem\n");
    strcpy(help,"help\n");
    strcpy(quit,"exit\n");
    strcpy(addData,"add_data\n");
    strcpy(display,"display\n");
    strcpy(free_all,"free_all\n");
 }

 void main_interface()
 {
      
      if(strcmp(str,alloc) == 0) allocated_mem = allocate();
      else if(strcmp(str,freemem) == 0) free_mem(allocated_mem);
      else if(strcmp(str,help) == 0) menu();
      else if(strcmp(str,quit) == 0) exit(0);
      else if(strcmp(str,addData) == 0) add_data();
      else if(strcmp(str,display) == 0) _display();
      else if(strcmp(str,free_all) == 0) freeAll();
        
 }

 
 uint32_t* allocate()
 {   
     printf("Enter the number of bytes:\t");
            scanf("%d",&bytes);
            if(bytes>20 || bytes<1)
            {
                printf("Press 'allocate' to allocate memory and enter a number below 20\n");
                return NULL;
            }
     
     if(mem_alloc_check < 20){
     if(array_count > 19 || max_bytes <= 0)
     {
         printf("Memory limit reached\n");
         return 0;
     }
      array[array_count] = (uint32_t*)malloc(bytes*sizeof(char));
      
     if(array[array_count] == NULL)
     {
         printf("Unable to assign memory space!\n");
         //menu();
     }
     
     a_flag=1;
     printf("Successfully allocated memory at %p\n",array[array_count]);
     array_count+=1;
     mem_alloc_check+=1;
     return array[array_count];
     }
     else{
         printf("Clear earlier memory first!\n");
         return 0;
     }
 }
 void free_mem(uint32_t* allocated_mem)
 {
     uint32_t i=0;
     //version v5
     if(a_flag==0) 
     {
         printf("Allocate memory first!\n");
         return;
     }
        printf("Enter location to free\n");
            scanf("%lx",&mem_free);
                 for(i=0; i<=array_count ; i++)
                 {
                    temp = (long)array[i];

                    //Version9:
                    if(temp == mem_free) 
                            {   
                                invalid_mem=0;
                                printf("Valid Address\n");
                                free(array[i]);
                                printf("Successfully freed memory at %p\n",array[i]);
                                array[i]=NULL;
                                mem_free_count+=1; 
                                location_to_free=i;  
                                resizing_freed_array(); 
                                
                            }

                    }


                if(invalid_mem == 1) printf("Enter a valid address or allocate memory first\n");
                  

                array[array_count]=NULL;
                mem_alloc_check=0;
                invalid_mem=1;

}
void user_input()
{   uint32_t input=2;
    fgets(str,BUFF,stdin);
}

void add_data()
{
    if(array_count == 0)
    {
        printf("Allocate Memory First\n");
        return;
    }
    printf("Enter address to store the data\n");
    scanf("%lx",&mem_to_store);
    for(i=0 ; i<array_count ; i+=1)
    {   temp = (long)array[i];
        if(temp == mem_to_store)
        {
            printf("Valid address, enter data\n");
            scanf("%d",&data_to_store);
            *array[i]=data_to_store;
            printf("Data: %d stored at Address %p\n",data_to_store, array[i]);
        }
    }
    if (data_to_store ==0) printf("Invalid Data\n");
}

void resizing_freed_array()
{
    for(i=location_to_free+1; i<array_count; i+=1)
    {
        array[i-1]=array[i];
    }
    array[array_count-1]=NULL;
    array_count-=1;
}

void _display()
{   if(array_count == 0)printf("No memory to free\n");
    for(i=0;i<array_count;i+=1) printf("Address: %p Content: %d\n",array[i],*array[i]);
}

void freeAll()
{ 
    if(array_count==0) 
    {
        printf("Allocate Memory First.\n");
        return;
    }
    printf("This will erase all allocated memory.\n");
    printf("Use 'freemem' to free memory by address.\n");
    printf("To Continue type '1'\n");
    scanf("%d",&free_all_input);
    if(free_all_input==1)
    {
        for(i=0; i<array_count; i+=1) 
        {   
            free(array[i]);
            array[i]=NULL;
        }
        array_count=0;
        printf("Successfully freed memory\n");
    }
    
}