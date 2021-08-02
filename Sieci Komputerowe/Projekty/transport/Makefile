CFLAGS = -std=gnu99 -Wall -Wextra

all : transport

transport : main.o transport.o window.o

main.o : main.c transport.h

transport.o : transport.c transport.h

window.o : window.c transport.h

clean : 
	rm -f main.o transport.o window.o

distclean : 
	rm -f transport main.o transport.o window.o