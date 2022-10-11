xpick
=====

### Overview

xpick is a simple X11 library written in C that allows an X11 client to select a
window using the cursor. The library switches the cursor to a crosshair to indicate selection to the user.

### Requirements

xpick uses libxcb, but does not carry any requirements aside from that. The demo
application is built using cmake.

### Interface

xpick is contained entirely within two files: `xpick.c` and `xpick.h`. The
interface is defined as follows:

##### xpick_state_t \*`xpick_state_new`(xcb_connection_t \*connection)

Initialize an xpick state using a `connection` that has already been opened.

##### void `xpick_state_free`(xpick_state_t \*s)

Free data associated with an xpick state.

##### bool `xpick_cursor_grab`(xpick_state_t \*s, uint16_t screen_index)

Attempt to grab the cursor and lock it to the screen at `screen_index`.

If `screen_index` is a valid index (screens begin at zero) and the cursor can be
grabbed, the cursor is changed into a crosshair and this returns `true`.
Otherwise, this returns `false`.

##### bool `xpick_cursor_pick_window`(xpick_state_t \*s)

Allow the user to select a window with the left mouse button.

If the grab succeeded and the user selects a window with the left mouse button,
this returns `true`.

If the user presses a mouse button aside from the left mouse button, it is
treated as a cancel, no window is selected and this returns `false`.

If the grab did not succeed, this immediately returns without selecting a
window.

##### void `xpick_cursor_ungrab`(xpick_state_t \*s)

Release the grab on the cursor. If the cursor grab failed, this does nothing.

##### xcb_window_t `xpick_window_get`(xpick_state_t \*s)

If no window has been selected, this returns 0 (`XCB_WINDOW_NONE`). Otherwise,
this will return the window selected by the user.

### Example

```
#include <stdio.h>
#include <stdlib.h>

#include "xpick.h"

int main (int argc, char **argv)
{
    xcb_connection_t *conn = xcb_connect(NULL, NULL);
    xpick_state_t *s = xpick_state_new(conn);
    xcb_window_t window;

    if (xpick_cursor_grab(s, 0) == 0)
        fprintf(stderr, "Error: Failed to grab the cursor.\n");

    xpick_cursor_pick_window(s);
    xpick_cursor_ungrab(s);
    window = xpick_window_get(s);
    printf("0x%.8x\n", window);
    xpick_state_free(s);
    xcb_disconnect(conn);
    return EXIT_SUCCESS;
}
```

This is the demo application of xpick, included here for convenience.

### License

MIT

### Why

I want a focused, minimalist library using xcb that I can drop into other
projects to allow them to select a client using the mouse.
