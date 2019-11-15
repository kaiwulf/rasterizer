#include "x11_random_dots.h"

const static int screen_xsize = 320;
const static int screen_ysize = 200;

Visual *vis;            // X11: Visual (visual info about X server)
Display *dpy;           // X11: Display (connection to X server)
Window w;               // X11: Window
XImage *ximg;
int depth, bytespp, scanline_pad;
unsigned char *screen;

void event_loop() {
    XEvent event;
    char ch;
    KeySym keysym;
    XComposeStatus xcompstat;

    int mouse_x, mouse_y;
    while(1) {
    if (XCheckWindowEvent(dpy, w, KeyPressMask, &event)) {
        XLookupString(&event.xkey, &ch, 1, &keysym, &xcompstat);
        switch(ch) {
            case 'q': exit(0);
      }
    }

    //sbegin random_dots
    int i,j,k;
    unsigned char *c;
    c = screen;
    for(i=0; i<screen_xsize; i++) {
        for(j=0; j<screen_ysize; j++) {
            for(k=0; k<bytespp; k++) {
                *c++ = rand() % 255;
            }
        }
    }

    XPutImage(dpy, w, DefaultGC(dpy,0), ximg,
              0,0,0,0,  /* source x,y; destination x,y */
              screen_xsize, screen_ysize);
    //send random_dots
  }
}

const char *event_name(int e_type) {
    static char text[80];

    switch (e_type) {

        //- event types from X11.h

        case KeyPress : sprintf(text, "KeyPress"); break;
        case KeyRelease : sprintf(text, "KeyRelease"); break;
        case ButtonPress : sprintf(text, "ButtonPress"); break;
        case ButtonRelease : sprintf(text, "ButtonRelease"); break;
        case MotionNotify : sprintf(text, "MotionNotify"); break;
        case EnterNotify : sprintf(text, "EnterNotify"); break;
        case LeaveNotify : sprintf(text, "LeaveNotify"); break;
        case FocusIn : sprintf(text, "FocusIn"); break;
        case FocusOut : sprintf(text, "FocusOut"); break;
        case KeymapNotify : sprintf(text, "KeymapNotify"); break;
        case Expose : sprintf(text, "Expose"); break;
        case GraphicsExpose : sprintf(text, "GraphicsExpose"); break;
        case NoExpose : sprintf(text, "NoExpose"); break;
        case VisibilityNotify : sprintf(text, "VisibilityNotify"); break;
        case CreateNotify : sprintf(text, "CreateNotify"); break;
        case DestroyNotify : sprintf(text, "DestroyNotify"); break;
        case UnmapNotify : sprintf(text, "UnmapNotify"); break;
        case MapNotify : sprintf(text, "MapNotify"); break;
        case MapRequest : sprintf(text, "MapRequest"); break;
        case ReparentNotify : sprintf(text, "ReparentNotify"); break;
        case ConfigureNotify : sprintf(text, "ConfigureNotify"); break;
        case ConfigureRequest : sprintf(text, "ConfigureRequest"); break;
        case GravityNotify : sprintf(text, "GravityNotify"); break;
        case ResizeRequest : sprintf(text, "ResizeRequest"); break;
        case CirculateNotify : sprintf(text, "CirculateNotify"); break;
        case CirculateRequest : sprintf(text, "CirculateRequest"); break;
        case PropertyNotify : sprintf(text, "PropertyNotify"); break;
        case SelectionClear : sprintf(text, "SelectionClear"); break;
        case SelectionRequest : sprintf(text, "SelectionRequest"); break;
        case SelectionNotify : sprintf(text, "SelectionNotify"); break;
        case ColormapNotify : sprintf(text, "ColormapNotify"); break;
        case ClientMessage : sprintf(text, "ClientMessage"); break;
        case MappingNotify : sprintf(text, "MappingNotify"); break;
        case LASTEvent : sprintf(text, "LASTEvent"); break;
    }

    return text;
}

void create_window() {
    XPixmapFormatValues *pixmap_formats;
    int i, count;
    const int bits_per_byte = 8;

    //- establish connection to X server

    dpy = XOpenDisplay(NULL);


    // find out the supported depths of this server and take the default depth
    int* depths, numdepths;
    depths = XListDepths(dpy, DefaultScreen(dpy), &numdepths);
    depth = depths[0];

    for(i=0;i<numdepths;i++) {
        printf("got X depth %d\n", depths[i]);
    }

    XFree(depths);

    // get pixmap information about this depth
    pixmap_formats = XListPixmapFormats(dpy, &count);
    for(i=0; i<count; i++) {
        printf("getting depth %d\n",pixmap_formats[i].depth);
        if(pixmap_formats[i].depth == depth) {
            bytespp      = pixmap_formats[i].bits_per_pixel / 8; // 8 bits per byte
            scanline_pad = pixmap_formats[i].scanline_pad;
            break;
        }
    }
    XFree(pixmap_formats);


    printf("default depth of display %d\n", depth);
    printf("bytes per pixel: %d\n", bytespp);

    //- print out some information about the visual

    vis = DefaultVisual(dpy,0);
    switch(vis->class) {
        case PseudoColor: printf("Vis is pseudocolor\n");break;
        case StaticColor: printf("Vis is StaticColor\n");break;
        case GrayScale: printf("Vis is GrayScale\n");break;
        case StaticGray: printf("Vis is StaticGray\n");break;
        case DirectColor: printf("Vis is DirectColor\n");break;
        case TrueColor: printf("Vis is TrueColor\n");break;
  }

  //- create and map the window using max. possible depth

    w = XCreateWindow(dpy, DefaultRootWindow(dpy), 100, 100,
                    screen_xsize, screen_ysize,
                    0, // border
                    depth, CopyFromParent, vis, // depth, class, visual
                    0, NULL); // valuemask, attributes
    XStoreName(dpy, w,"random_dots");
    XMapWindow(dpy, w);

    //- create XImage and offscreen buffer

    //sbegin create_screen
    // screen = new char[screen_xsize*screen_ysize*bytespp]
    screen = malloc(screen_xsize*screen_ysize*bytespp);
    //send create_screen

    if (ImageByteOrder(dpy) == LSBFirst ) {
        printf("lsb first\n");
    } else {
        printf("msb first\n");
    }

  //sbegin create_ximage
    ximg = XCreateImage(dpy, vis, depth,
                      ZPixmap,   // format
                      0,  // offset from beg. of scanline
                      screen,
                      screen_xsize, screen_ysize,
                      scanline_pad,
                      0); // bytes_per_line: 0 = autocompute
  //send create_ximage

    XSetForeground(dpy, DefaultGC(dpy, 0), ~0);
    XSetBackground(dpy, DefaultGC(dpy, 0), 0);
}

void event_notification() {
    XSelectInput(dpy, w, 0x00FFFFFF ^ PointerMotionHintMask);
}

int main() {
    create_window();
    event_notification();
    event_loop();
    free(screen);
    return 0;
}
