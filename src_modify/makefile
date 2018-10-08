objects = project1_latest2.o a.out project1_headers.h testing 

edit	:	$(objects)
project1_latest.o : project1_latest2.c	project1_headers.h
					cc -c project1_latest2.c
		    gcc project1_latest2.c -w	
																
a.out		: project1_latest2.o project1_headers.h
		gcc project1_latest2.c -w
		sudo ./a.out	
project1_headers.h	: project1_latest2.c
testing:																	   
			sudo ./a.out < input.txt > output.txt
clean: 
		rm edit $(objects)

