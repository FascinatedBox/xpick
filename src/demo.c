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
