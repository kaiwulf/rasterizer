CC = gcc
LIBDIR = -L/usr/include/X11/
CFLAGS = -lX11 -lXt -lm
DEPS = "x11_front_end.h"

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $(LIBDIR) $? $(CFLAGS)
	# $(CC) -c -o $@ $< $(CFLAGS) $? $(LIBDIR)

make: x11_front_end.o
	$(CC) x11_front_end.o -o x11_front_end