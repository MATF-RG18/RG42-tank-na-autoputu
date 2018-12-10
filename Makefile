PROGRAM = crush_them
CC      = gcc
CFLAGS  = -g -std=c99 -Wall -Wextra -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL

$(PROGRAM): crush_them.o drawFunctions.o callbackFunctions.o lightingFunctions.o image.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) crush_them.o drawFunctions.o callbackFunctions.o lightingFunctions.o image.o $(LDLIBS) 

drawFunctions.o: drawFunctions.c
	$(CC) $(CFLAGS) -c $(LDFLAGS) drawFunctions.c $(LDLIBS)

callbackFunctions.o: callbackFunctions.c
	$(CC) $(CFLAGS) -c $(LDFLAGS) callbackFunctions.c $(LDLIBS)

lightingFunctions.o: lightingFunctions.c
	$(CC) $(CFLAGS) -c $(LDFLAGS) lightingFunctions.c $(LDLIBS)

image.o: image.c
	$(CC) $(CFLAGS) -c $(LDFLAGS) image.c $(LDLIBS)

crush_them.o: crush_them.c
	$(CC) $(CFLAGS) -c $(LDFLAGS) crush_them.c $(LDLIBS)
	
.PHONY: beauty clean dist

beauty:
	-indent -kr -nut $(PROGRAM).c
	-rm *~ *BAK

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
