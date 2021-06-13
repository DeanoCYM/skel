/* This file is part of @PROJECT
   Copyright (C) @DATE @AUTHOR <@EMAIL>
   See COPYING file for licence details */

/* skel_app.h - skel application class deceleration */

#ifndef _SKEL_APP_H
#define _SKEL_APP_H

#include <gtk/gtk.h>

#define SKEL_APP_TYPE (skel_app_get_type())
G_DECLARE_FINAL_TYPE(SkelApp, skel_app, SKEL, APP, GtkApplication)

/* skel_app_new(): returns a poiner to a new skell application. */
SkelApp * skel_app_new(void);

#endif /* _SKEL_APP_H */
