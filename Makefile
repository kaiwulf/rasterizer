CC = gcc
CFLAGS = -L/usr/X11R6/lib -lX11 -lXt -lm
# DEPS = "x11_front_end.h"

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: x11_front_end.o
	$(CC) x11_front_end.o -o x11_front_end