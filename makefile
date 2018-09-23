objects = project1_latest.o

edit	:	$(objects)
project1_latest.o : project1_latest.c
					cc -c project1_latest.c
		gcc project1_latest.c -o project1_latest.o -w
		sudo ./project1_latest.o

clean:
		rm edit $(objects)

