#include <stdio.h>
#include <stdlib.h>
#include <X11/Intrinsic.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

void event_loop();
const char *event_name(int e_type);
void create_window();
void event_notification();