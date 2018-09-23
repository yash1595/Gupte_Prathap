/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

This version takes the input as "allocate" and "freemem"
This version takes hexadecimal input from user to clear bytes
v4: This version makes the code 32bit-unsigned aligned.
*******************************************************************************
v5:This version takes address from user to free space.
Blocks double freeing.
*******************************************************************************
v6(current): Resolved issue for linux 64bit boundary
    created a make file with run commands.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BUFF 15 
#define MAX  20

 void menu();
 uint32_t* allocate(short int ,short int);
 void free_mem(uint32_t* allocated_mem);
 uint32_t user_input(void);

 uint32_t input=2;
 uint32_t bytes=0,max_bytes=MAX,a_flag=0,mem_alloc_check=0,clear_mem=0,mem_free_count=0;
 uint32_t j=0;
 uint32_t donot_free=0;
 uint32_t* allocated_mem=0;
 uint32_t* array[MAX]={0};
 uint32_t* free_mem_check[MAX];
 uint32_t  already_freed[MAX];
 
 char str[BUFF];
 char alloc[BUFF];
 char freemem[BUFF];

 uint32_t array_mem_check[MAX];
 uint32_t array_count=0;
 int main()
 {
     menu();
     // Call a function for this.
     strcpy(alloc,"allocate\n");
     strcpy(freemem,"freemem\n");
     while(1)
     {
      here:
      input = user_input();
      if(input==0){
            printf("Enter the number of bytes:\t");
            scanf("%d",&bytes);
            //Addition v5:
            //max_bytes=max_bytes-bytes;
            if(bytes>20 || bytes<1) {
                printf("Press 'allocate' to allocate memory and enter a number below 20\n");
                goto here;
            }
            allocated_mem = allocate(bytes,max_bytes);
            }
     
      else {
         input=strcmp(str,freemem);
         if(input == 0) free_mem(allocated_mem);
     }
      
   }
   return 0;
 }
    
 

 void menu()
 {  puts("Welcome! This is the main menu:\n");
    printf("Type in 'allocate' followed by number of bytes(<20) to allocate x bytes of memory\n");
    printf("Type in 'freemem' followed by index number to deallocate allocated bytes of memory\n");
    
 }

 uint32_t* allocate(short int bytes,short int max_bytes)
 {
     if(mem_alloc_check < 20){
     if(array_count > 19 || max_bytes <= 0)
     {
         printf("Memory limit reached\n");
         return 0;
     }
      array[array_count] = (uint32_t*)malloc(bytes*sizeof(char));
      
     if(array[array_count] == NULL){
         printf("Unable to assign memory space!\n");
         //menu();
     }
     
     a_flag=1;
     //printf("array_count %d:\n",array_count);
     //printf("Successfully allocated memory\n");
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
     uint64_t mem_free=0,i=0;
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
                 { 
                    //printf("Content in array[i] %p\n",array[i]);
                    //printf("Content in mem_free %x\n",mem_free);
                    uint32_t temp = array[i];
                    
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
            //free(array[mem_free]);
            
            array[array_count]=NULL;
            //a_flag=0;
            mem_alloc_check=0;
            
            
            //printf("Contents at freed memory at %d\n",array[mem_free]);
            //array_count-=1;
}

uint32_t user_input()
{   uint32_t input=2;
    fgets(str,BUFF,stdin);
    //printf("%s\n",str);
    input=strcmp(str,alloc);
    //printf("%d\n",input); //remove later
    return input;
}
    
     
     
     
     
     