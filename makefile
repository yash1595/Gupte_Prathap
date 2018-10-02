objects = project1_latest.o a.out project1_headers.h

edit	:	$(objects)
project1_latest.o : project1_latest.c	project1_headers.h
					cc -c project1_latest.c
		    gcc project1_latest.c -w	
																
a.out		: project1_latest.o project1_headers.h
		gcc project1_latest.c -w
		sudo ./a.out	
project1_headers.h	: project1_latest.c


clean:
		rm edit $(objects)

