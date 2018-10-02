/******************************************************************************
Project Partners: 1.Lekshmi Prathap
                  2.Yash Gupte
Current version created on: 09-25-2018
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
v11: 1. free_all function
-------------------------------------------------------------------------------
v12: 1. invert logic
              2. Default menu
              3. Valid address check in add_data.
-------------------------------------------------------------------------------
v13(current): 1. Access locations in between addresses.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#define BUFF 15 
#define MAX  20
/* structure*/


struct timeval start_t,end_t;

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
 void defaultMessage(void);
 void invert_data(void);
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
 uint32_t validMemInAddData=0;
 uint32_t num_of_loc=0;
 uint32_t xor=0xFFFF;
 
 long temp=0;
 long mem_to_invert=0;
 long mem_free=0;
 long mem_to_store=0;
 long store=0;
 long* mem_store=NULL;

 uint32_t elapsed = 0;

 uint32_t* array[MAX]={0};
 uint32_t pointer_to_array[MAX]={0};
 
 char str[BUFF];
 char alloc[BUFF];
 char freemem[BUFF];
 char help[BUFF];
 char quit[BUFF];
 char addData[BUFF];
 char display[BUFF];
 char free_all[BUFF];
 char invertData[BUFF];
 
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
    strcpy(invertData,"invert_data\n");
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
      else if(strcmp(str,invertData) == 0) invert_data();
      else if(strcmp(str,"\n")!=0) defaultMessage();        
 }

 
 uint32_t* allocate()
 {   
     printf("Enter the number of bytes:\t");
            scanf("%d",&bytes);
            if(bytes>BUFF || bytes<1)
            {
                printf("Press 'allocate' to allocate memory and enter a number below 20\n");
                return NULL;
            }
     
     if(mem_alloc_check < BUFF){
     if(array_count > (BUFF-1) || max_bytes <= 0)
     {
         printf("Memory limit reached\n");
         return 0;
     }
      array[array_count] = (uint32_t*)malloc(bytes*sizeof(uint32_t));
      pointer_to_array[array_count]=bytes;
      
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
    //temp
    //long* p=mem_to_store;
    mem_store=mem_to_store;
    for(i=0 ; i<array_count ; i+=1)        
    {   store=(long)array[i];
        if(mem_to_store >= store && mem_to_store <= (store + pointer_to_array[i]*sizeof(uint32_t)))
        {
            if((mem_to_store-store)%(sizeof(uint32_t)) == 0)
            {
                printf("Valid address, enter data\n");
                scanf("%x",&data_to_store);
                *mem_store=data_to_store;
                printf("Data: %04x stored at Address %04lx\n",data_to_store,mem_to_store);
                //validMemInAddData=1;
                return;
            }
        }
    }
    printf("Invalid Address\n");
}

    
    
    //validMemInAddData=0;
    //if (data_to_store ==0) printf("Invalid Data\n");


void resizing_freed_array()
{
    for(i=location_to_free+1; i<array_count; i+=1)
    {
        array[i-1]=array[i];
        pointer_to_array[i-1]=pointer_to_array[i];
    }
    array[array_count-1]=NULL;
    pointer_to_array[array_count-1]=0;
    array_count-=1;
}

void _display()
{   
    
    if(array_count == 0)printf("No memory to free\n");
    for(i=0;i<array_count;i+=1)
    {   store=(long)array[i];
        for(j=0;j<pointer_to_array[i]; j+=1)
        {
            printf("Address:%04lx\t Data:%04x\n",store+sizeof(uint32_t)*j,*(array[i]+1*j));
        }
        //printf("Address: %p Content: %x\n",array[i],*array[i]);
        //printf("Content at pointer_to_array: %d\n",pointer_to_array[i]);
    } 
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
void invert_data(void)
{
    if(array_count == 0)
    {
        printf("Allocate Memory First\n");
        return;
    }
    printf("Enter the starting address to invert the data\n");
    scanf("%lx",&mem_to_invert);
    printf("Enter number of locations to invert\n");
    scanf("%d",&num_of_loc);
    gettimeofday(&start_t,NULL);
    printf("start %lds:\n start %ldus:\n",start_t.tv_sec,start_t.tv_usec);
    mem_store=&mem_to_invert;
    for(i=0 ; i<array_count ; i+=1)        
    {   store=(long)array[i];
        if(mem_to_invert >= store && ((mem_to_invert + (num_of_loc)*sizeof(uint32_t)) <= (store + pointer_to_array[i]*sizeof(uint32_t))))
        {
            if((mem_to_invert-store)%(sizeof(uint32_t)) == 0)
            {
                *mem_store^=xor;//check
                printf("Data: %04lx stored at Address %04lx\n",*mem_store,mem_to_invert);
                gettimeofday(&end_t,NULL);
                printf("end %ld s:\n end %ld us:\n",end_t.tv_sec,end_t.tv_usec);
                elapsed=(start_t.tv_sec-end_t.tv_sec)+(start_t.tv_usec- end_t.tv_usec)*0.000001;
                printf("Time taken for execution of XOR: %ld s %ld us \n",(end_t.tv_sec-start_t.tv_sec), (end_t.tv_usec- start_t.tv_usec));
                return;
            }
        }
    }
    printf("Invalid Address\n");
}
    
    

void defaultMessage(void)
{
    printf("Please enter a valid input.\nType 'help' for main menu\n");
}