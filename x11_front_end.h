#include <stdio.h>
#include <X11/Intrinsic.h>
#include <X11/Xlib.h>

void event_loop();
const char *event_name(int e_type);
void create_window();
void event_notification();