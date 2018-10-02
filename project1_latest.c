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
v13:          1. Resolved pointer incompatibility
              2. Resolved invert_data for all memory
-------------------------------------------------------------------------------
v14:          1. Exit with free_all
              2. Header File included
-------------------------------------------------------------------------------
v15(current): 1. Random data
*******************************************************************************/
#include </home/ubuntu/Documents/Gupte_Prathap/project1_headers.h>
 
 // Variables 
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
 uint32_t exit_free_flag=0;
 
 long temp=0;
 //long mem_to_invert=0;
 long mem_free=0;
 //long mem_to_store=0;
 long store=0;
 long add_aft_offset=0;
 uint32_t* mem_store=NULL;

 uint32_t elapsed = 0;

 uint32_t* array[MAX]={0};
 uint32_t pointer_to_array[MAX]={0};
 uint32_t* random_sequence[20]={0};
 
 char str[BUFF];
 char alloc[BUFF];
 char freemem[BUFF];
 char help[BUFF];
 char quit[BUFF];
 char addData[BUFF];
 char display[BUFF];
 char free_all[BUFF];
 char invertData[BUFF];
 char pseudo[BUFF];
 char verify_pattern[BUFF];
 char offset[BUFF];
 
 /* Main Function */


 int main()
 {  //typedef void (*f_ptr) (void);
     function_pointer_assignemnt();
     //f_ptr f_add_data = add_data;
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
    printf("Type in 'invert_data' to invert data in the program\n");
    printf("Type in 'random' to generate a random sequence\n");
    printf("Type in 'verify' to check a random sequence\n");
    strcpy(alloc,"allocate\n");
    strcpy(freemem,"freemem\n");
    strcpy(help,"help\n");
    strcpy(quit,"exit\n");
    strcpy(addData,"add_data\n");
    strcpy(display,"display\n");
    strcpy(free_all,"free_all\n");
    strcpy(invertData,"invert_data\n");
    strcpy(pseudo,"random\n");
    strcpy(verify_pattern,"verify\n");
    strcpy(offset,"offset\n");
 }

 void main_interface()
 {
      
      if(strcmp(str,alloc) == 0) allocated_mem = allocate();
      else if(strcmp(str,freemem) == 0) free_mem(allocated_mem);
      else if(strcmp(str,help) == 0) menu();
      else if(strcmp(str,quit) == 0) exit_free();
      else if(strcmp(str,addData) == 0) add_data();
      else if(strcmp(str,display) == 0) _display();
      else if(strcmp(str,free_all) == 0) freeAll();
      else if(strcmp(str,invertData) == 0) invert_data();
      else if(strcmp(str,pseudo) == 0) _random();       
      else if(strcmp(str,verify_pattern)==0) verify();    
      else if(strcmp(str,offset)==0) offset_mem();
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
    long mem_to_store=0;
    if(array_count == 0)
    {
        printf("Allocate Memory First\n");
        return;
    }
    printf("Enter address to store the data\n");
    scanf("%lx",&mem_to_store);
    mem_store=(uint32_t*)mem_to_store;
    for(i=0 ; i<array_count ; i+=1)        
    {   store=(long)array[i];
        if(mem_to_store >= store && mem_to_store <= (store + pointer_to_array[i]*sizeof(uint32_t)))
        {
            if((mem_to_store-store)%(sizeof(uint32_t)) == 0)
            {
                printf("Valid address, enter data\n");
                scanf("%x",&data_to_store);
                *mem_store=data_to_store;
                printf("Data: %04x stored at Address %04lx\n",*mem_store,mem_to_store);
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
    if(array_count==0 && exit_free_flag==0) 
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
        exit_free_flag=0;
    }
    
}
void invert_data(void)
{
    long mem_to_invert=0;
    uint32_t* invert_sequence[BUFF]={0};
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
    //mem_store=(long*)mem_to_invert;
    invert_sequence[0]=(uint32_t*)mem_to_invert;
    for(i=0 ; i<array_count ; i+=1)        
    {   store=(long)array[i];
        if(mem_to_invert >= store && ((mem_to_invert + (num_of_loc)*sizeof(uint32_t)) <= (store + pointer_to_array[i]*sizeof(uint32_t))))
        {
            if((mem_to_invert-store)%(sizeof(uint32_t)) == 0)
            {   for(i=0;i<num_of_loc;i+=1)
              {
                *invert_sequence[i]^=xor;
                 invert_sequence[i+1]=(uint32_t*)(mem_to_invert+(i+1)*(sizeof(uint32_t)));
                 printf("Data: %x stored at Address %ls\n",*invert_sequence[i],invert_sequence[i]);

              }
                //*mem_store^=xor;//check
                
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
    
void _random(void)
{
  uint32_t seed=0;
  long mem_to_random=0;
  //uint32_t* random_sequence[20]={0};
  uint32_t a=1,b=3,M=10;
  //int*x[20]={0};
    //long mem_to_invert=0;
    if(array_count == 0)
    {
        printf("Allocate Memory First\n");
        return;
    }
    printf("Enter the starting address for the seed\n");
    scanf("%lx",&mem_to_random);
    printf("Enter number of sequences\n");
    scanf("%d",&num_of_loc);
    printf("Enter the seed value\n");
    scanf("%d",&seed);
    gettimeofday(&start_t,NULL);
   
    random_sequence[0]=(uint32_t*)mem_to_random;
    *random_sequence[0]=seed;

    for(i=0 ; i<array_count ; i+=1)        
    {   store=(long)array[i];
        if(mem_to_random >= store && ((mem_to_random + (num_of_loc)*sizeof(uint32_t)) <= (store + pointer_to_array[i]*sizeof(uint32_t))))
        {
            if((mem_to_random-store)%(sizeof(uint32_t)) == 0)
            {   gettimeofday(&start_t,NULL);
                printf("start %lds:\n start %ldus:\n",start_t.tv_sec,start_t.tv_usec);
                //*mem_store = seed;
                for(i=1 ;i<num_of_loc; i+=1)
                {
                    random_sequence[i]=(uint32_t*)(mem_to_random+i*sizeof(uint32_t));
                    *random_sequence[i]=(a*(*random_sequence[i-1]+b))%M;
                  //(mem_store+1)= (a*(*mem_store)+b)%M;
                    //mem_store = mem_store+1;
                    printf("Content at mem_store:%04x address of mem_store:%ls\n",*random_sequence[i],random_sequence[i]);
                }
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

void verify()
{
  long seed=0;
  long mem_to_random=0;
  uint32_t* random_sequence_verify[BUFF]={0};
  uint32_t num_of_loc_verify=0;
  uint32_t a=1,b=3,M=10;
  uint32_t* first_seed_val=0;
  //int*x[20]={0};
    //long mem_to_invert=0;
    if(array_count == 0)
    {
        printf("Allocate Memory First\n");
        return;
    }
    printf("Enter the starting address for the seed\n");
    scanf("%lx",&mem_to_random);
    printf("Enter number of sequences\n");
    scanf("%d",&num_of_loc_verify);
    printf("Enter the seed value\n");
    scanf("%ld",&seed);
    gettimeofday(&start_t,NULL);
   
    random_sequence_verify[0]=(uint32_t*)mem_to_random;
    //first_seed_val = (uint32_t*)mem_to_random;
 /*   if(num_of_loc_verify>num_of_loc)
    {
      printf("Patterns don't match")
    }*/

    for(i=0 ; i<array_count ; i+=1)        
    {   store=(long)array[i];
        if(mem_to_random >= store && ((mem_to_random + (num_of_loc)*sizeof(uint32_t)) <= (store + pointer_to_array[i]*sizeof(uint32_t))))
        {
            if((mem_to_random-store)%(sizeof(uint32_t)) == 0)
            {   gettimeofday(&start_t,NULL);
                printf("start %lds:\n start %ldus:\n",start_t.tv_sec,start_t.tv_usec);
                //*mem_store = seed;
                if((uint32_t)*random_sequence_verify[0]!=(uint32_t)seed)
                {
                  printf("Discrepancy at %lx value is %x should be %ld\n",(long)random_sequence_verify[0],*random_sequence_verify[0],seed);
                }
                for(i=1 ;i<num_of_loc_verify; i+=1)
                {
                    random_sequence_verify[i]=(uint32_t*)(mem_to_random+i*sizeof(uint32_t));
                    if(*random_sequence_verify[i]!=(a*(seed+b))%M)

                    {
                      printf("Discrepancy at %lx value is %x should be %ld\n",(long)random_sequence_verify[i],*random_sequence_verify[i],(a*(seed+b))%M);
                    }
                    seed=(a*(seed+b)%M);
                   
                  //(mem_store+1)= (a*(*mem_store)+b)%M;
                    //mem_store = mem_store+1;
                    //printf("Content at mem_store:%04x address of mem_store:%ls\n",*random_sequence[i],random_sequence[i]);
                }
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

void function_pointer_assignemnt(void)
{    
  /*   ffree_mem = free_mem;
     fmenu=menu;
     fadd_data = add_data;
     fresizing_freed_array = resizing_freed_array;
     f_display = _display;
     ffreeAll = freeAll;
     ffinvert_data = invert_data;
     f_random = _random;
     fdefaultMessage = defaultMessage;
     fexit_free =exit_free;
     fuser_input = user_input;
     printf("here\n");*/
}
void offset_mem(void)
{ long block_index=0;
  long offset_index=0;
  long add_bef_offset=0;
  printf("Enter the block of memory starting from 0\n");
  scanf("%ld",&block_index);
  if(array_count < block_index) 
  {
    printf("Block not assigned\n");
    return;
  }
  else 
  {
      //offset_index=array[block_index];
      printf("Enter the offset\n");
      scanf("%ld",&offset_index);
      if(offset_index > pointer_to_array[block_index])
      {
            printf("Out of Bounds\n");
            return;
      }
      else
      { 
          add_bef_offset =(long)array[block_index];
          add_aft_offset=add_bef_offset+offset_index*sizeof(uint32_t);
          printf("0x%lx\n",add_aft_offset);
      }
  }
}
void exit_free(void)
{ exit_free_flag=1;
  freeAll();
  exit(0);
}

void defaultMessage(void)
{
    printf("Please enter a valid input.\nType 'help' for main menu\n");
}