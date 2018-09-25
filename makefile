objects = project1_latest.o

edit	:	$(objects)
project1_latest.o : project1_latest.c	
					cc -c project1_latest.c
		    gcc project1_latest.c -o $(objects) -w
		
																
		#gcc -Wl,--oformat=a.out-i386-linux project1_latest.c -o proj.out
		sudo ./$(objects)

clean:
		rm edit $(objects)

