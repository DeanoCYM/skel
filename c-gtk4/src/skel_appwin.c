/* This file is part of @PROJECT
   Copyright (C) @DATE @AUTHOR <@EMAIL>
   See COPYING file for licence details */

/* skel_appwin.c - Skel application window class definition */

#include <gtk/gtk.h>

#include "skel_app.h"
#include "skel_appwin.h"

/* SkelAppWindow: skell application window class definition */
struct _SkelAppWindow {
    GtkApplicationWindow parent;

    /* instance members */
    GtkWidget *stack;
};

G_DEFINE_TYPE(SkelAppWindow, skel_app_window, GTK_TYPE_APPLICATION_WINDOW);

/* interface */
SkelAppWindow *skel_app_window_new(SkelApp *app);
void skel_app_window_open (SkelAppWindow *win, GFile *file);
/* Constructors */
static void skel_app_window_class_init(SkelAppWindowClass *class);
static void skel_app_window_init(SkelAppWindow *self);

/* skel_app_window_new(): interface for skel application window
   creation, returns a pointer to a new skel application window. */
SkelAppWindow *
skel_app_window_new(SkelApp *app)
{
    return g_object_new(SKEL_APP_WINDOW_TYPE,
			"application", app,
			NULL);
}

/* skel_app_window_open(): interface for opening a window with a
   file. */
void
skel_app_window_open(SkelAppWindow *win, GFile *file)
{
    /*
      UNDERSTAND AND THEN GET RID OF ME
     */
    char *basename;
    GtkWidget *scrolled, *view;
    char *contents;
    gsize length;

    basename = g_file_get_basename (file);

    scrolled = gtk_scrolled_window_new();
    gtk_widget_set_hexpand (scrolled, TRUE);
    gtk_widget_set_vexpand (scrolled, TRUE);
    view = gtk_text_view_new();
    gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
    gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scrolled), view);
    gtk_stack_add_titled (GTK_STACK (win->stack), scrolled, basename, basename);

    if (g_file_load_contents (file, NULL, &contents, &length, NULL, NULL))
	{
	    GtkTextBuffer *buffer;

	    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
	    gtk_text_buffer_set_text (buffer, contents, length);
	    g_free (contents);
	}

    g_free (basename);
}

/* skel_app_window_class_init(): class constructor, will be executed
   only once before the first instance is constructed. Any shared data
   and signals should be set up here. */
static void
skel_app_window_class_init(SkelAppWindowClass *class)
{
    /* specify the xml file used to extend the window user interface */
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class), "/cymru/ert/skel/data/ui/window.ui");

    /* point widgets in xml templates to appropriate class members */
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), SkelAppWindow, stack);
}

/* skel_app_window_init(): object constructor, initialises a new skel
   application window instance in self. */
static void 
skel_app_window_init(SkelAppWindow *self)
{
    /* Instantiate child widgets defined in templates. */
    gtk_widget_init_template(GTK_WIDGET(self));

    return;
}
