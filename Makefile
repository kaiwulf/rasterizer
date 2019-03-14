CC = gcc
LIBDIR = -L/usr/include/X11/
CFLAGS = -lX11 -lXt -lm
GCCFLAGS = -g3
DEPS = "x11_front_end.h"

x11_front_end : x11_front_end.o
	$(CC) -o $@ $(LIBDIR) $? $(CFLAGS) $(GCCFLAGS)

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $(LIBDIR) $(CFLAGS)
	# $(CC) -o $@ $< $(CFLAGS) $? $(LIBDIR)

# make: x11_front_end.o
# 	$(CC) x11_front_end.o -o x11_front_end