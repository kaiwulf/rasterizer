CC = gcc
LIBDIR = -L/usr/include/X11/
CFLAGS = -lX11 -lXt -lm
GCCFLAGS = -g3
DEPS = "x11_random_dots.h"

x11_random_dots : x11_random_dots.o
	$(CC) -o $@ $(LIBDIR) $? $(CFLAGS) $(GCCFLAGS)
