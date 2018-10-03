++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ECEN 5813 : Principles of Embedded Software 
Lekshmi Prathap & Yash Gupte
This program allows a user to dynamically allocate blocks of memory and offers functions to manipulate the allocated memory.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
menu     : Displays the help menu which includes the list of commands and descriptions. 
allocate : Allocates a memory block of the specified size upto 256 memory locations (ie 1024 bytes). Uses malloc().
add	     : Allows the user to input data to a specified memory location in a memory block. The memory location may be specified through the complete address or offset. 
display  : Displays either the entire memory or a user specified area of memory.
invert	 : Inverts the contents of a specified area of memory. The area of memory may be specified through complete starting address or offset along with the number of locations to invert. 
random   : Generates a pseudo random sequence in a specified area of memory. Uses Linear congruential generator, with a = 1, b = 3, M = 20 and a user defined seed value. 
verify   : Generates a pseudo random sequence and compares it with the data in a specified area of memory and lists the locations in which there is discrepancy. 
free     : Frees a specified block of memory, using free().
release  : Frees all the allocated blocks of memory.
exit     : Frees all the allocated blocks of memory and exits the program.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++