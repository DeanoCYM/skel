/* This file is part of @PROJECT
   Copyright (C) @DATE @AUTHOR <@EMAIL>
   See COPYING file for licence details */

/* main.c - start gtk4 event loop  */

#include <gtk/gtk.h>

#include "skel_app.h"

int
main(int argc, char **argv)
{
    /* Start the application event loop by providing an instance of
       the custom application class */
    return g_application_run(G_APPLICATION(skel_app_new()), argc, argv);
}


