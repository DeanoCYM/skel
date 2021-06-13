/* This file is part of @PROJECT
   Copyright (C) @DATE @AUTHOR <@EMAIL>
   See COPYING file for licence details */

/* skel_appwin.h - skel application window class deceleration */

#ifndef _SKEL_APPWIN_H
#define _SKEL_APPWIN_H

#include <gtk/gtk.h>

#include "skel_app.h"

#define SKEL_APP_WINDOW_TYPE (skel_app_window_get_type())
G_DECLARE_FINAL_TYPE(SkelAppWindow, skel_app_window, SKEL, APP_WINDOW, GtkApplicationWindow)

/* skel_app_window_new(): returns a poiner to a new skell window application. */
SkelAppWindow *skel_app_window_new(SkelApp *app);
/* skel_app_window_open(): interface for opening a window with a file. */
void skel_app_window_open(SkelAppWindow *win, GFile *file);

#endif /* _SKEL_APPWIN_H */
