CC = gcc
LIBDIR = -L/usr/include/X11/
CFLAGS = -lX11 -lXt -lm
GCCFLAGS = -g3
DEPS = "x11_draw_line.h"

x11_draw_line : x11_draw_line.o
	$(CC) -o $@ $(LIBDIR) $? $(CFLAGS) $(GCCFLAGS)
