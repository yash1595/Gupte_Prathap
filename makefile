objects = project1_latest.o

edit	:	$(objects)
project1_latest.o : project1_latest.c	
					cc -c project1_latest.c
		    gcc project1_latest.c -w	
																
a.out		:	$(objects)
		

clean:
		rm edit $(objects)

