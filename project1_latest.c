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
v8(current): 1.Added the exit function.
             2.Added function to store data in a 
             memory location which has been allocated.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BUFF 15 
#define MAX  20

 void menu();
 uint32_t* allocate();
 void free_mem(uint32_t* allocated_mem);
 void user_input(void);
 void main_interface(void);
 void add_data(void);


 uint32_t input=2;
 uint32_t bytes=0,max_bytes=MAX,a_flag=0,mem_alloc_check=0,clear_mem=0,mem_free_count=0;
 uint32_t j=0,i=0;
 uint32_t mem_free=0;
 uint32_t donot_free=0;
 uint32_t data_to_store = 0;
 uint32_t mem_to_store = 0;
 uint32_t temp=0;
 uint32_t* allocated_mem=0;
 uint32_t* array[MAX]={0};
 uint32_t* free_mem_check[MAX];
 uint32_t  already_freed[MAX];
 uint32_t array_mem_check[MAX];
 
 
 char str[BUFF];
 char alloc[BUFF];
 char freemem[BUFF];
 char help[BUFF];
 char _exit[BUFF];
 char addData[BUFF];
 

 
 uint32_t array_count=0;

 int main()
 {
     menu();
     while(1)
     {
      user_input();
      main_interface();
     }
        //exit_func();
        return 0;
}
 
    
 void main_interface()
 {
      
      if(strcmp(str,alloc) == 0) allocated_mem = allocate();
      else if(strcmp(str,freemem) == 0) free_mem(allocated_mem);
      else if(strcmp(str,help) == 0) menu();
      else if(strcmp(str,_exit) == 0) exit(0);
      else if(strcmp(str,addData) == 0) add_data();
        
 }

 void menu()
 {  puts("Welcome! This is the main menu:\n");
    printf("Type in 'allocate' followed by number of bytes(<20) to allocate x bytes of memory\n");
    printf("Type in 'freemem' followed by index number to deallocate allocated bytes of memory\n");
    printf("Type in 'help' for the list of functions\n");
    printf("Type in 'exit' to exit the program\n");
    printf("Type in 'add_data' to add data in the program\n");
    strcpy(alloc,"allocate\n");
    strcpy(freemem,"freemem\n");
    strcpy(help,"help\n");
    strcpy(_exit,"exit\n");
    strcpy(addData,"add_data\n");
    
 }

 uint32_t* allocate()
 {   
     printf("Enter the number of bytes:\t");
            scanf("%d",&bytes);
            if(bytes>20 || bytes<1)
            {
                printf("Press 'allocate' to allocate memory and enter a number below 20\n");
                return;
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
            scanf("%x",&mem_free);
            //temp[0]=mem_free;
                 for(i=0; i<=array_count ; i++)
                 {  //printf("%ld\n",sizeof(array[i]));
                    uint32_t temp = (uint32_t)array[i];
                    
                    if(temp == mem_free) 
                        {   for(j=0; j<=mem_free_count; j++)    //very important '<='
                            {
                                if(already_freed[j] == mem_free)
                                {
                                    //printf("Already Freed.\n");
                                    donot_free=1;
                                }
                                else
                                {
                                    already_freed[j]=mem_free;
                                }
                            }
                            if(donot_free == 0)
                            {
                                printf("Valid Address\n");
                                free(array[i]);
                                //version v5:
                                //printf("%d\t",sizeof(mem_free));
                                printf("Successfully freed memory at %p\n",array[i]);
                                clear_mem=1;
                                mem_free_count+=1;          //Depends on the maximum you can free which is 20.
                                break;
                            }
                            else 
                            {   printf("Already Freed.\n");
                                donot_free=0;
                                break;
                            }
                        }
                }
                if(clear_mem == 0) printf("Enter a valid address or allocate memory first\n");
            array[array_count]=NULL;
            mem_alloc_check=0;

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
    scanf("%x",&mem_to_store);
    printf("Address entered: %d\n",mem_to_store);
    
    for(i=0 ; i<array_count ; i+=1)
    {   temp = array[i];
        if(temp == mem_to_store)
        {
            printf("Valid address, enter data\n");
            scanf("%d",&data_to_store);
            *array[i]=data_to_store;
            printf("Data: %d stored at Address %p\n",data_to_store, temp);
        }
    }
    if (data_to_store ==0) printf("Invalid Data\n");
}

