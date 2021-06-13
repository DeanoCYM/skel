/* This file is part of @PROJECT
   Copyright (C) @DATE @AUTHOR <@EMAIL>
   See COPYING file for licence details */

/* skel_app.c - Skel application class definition */

#include <gtk/gtk.h>

#include "skel_app.h"
#include "skel_appwin.h"

/*
   SkelApp: skel application class definition
*/
struct _SkelApp {
    GtkApplication parent;

    /* instance members */
};

G_DEFINE_TYPE(SkelApp, skel_app, GTK_TYPE_APPLICATION);

/* Interface */
SkelApp *skel_app_new(void);
/* Constructors */
static void skel_app_class_init(SkelAppClass *class);
static void skel_app_init(SkelApp *self);
/* Signals */
static void skel_app_startup(GApplication *app);
static void skel_app_shutdown(GApplication *app);
static void skel_app_activate(GApplication *app);
static void skel_app_open(GApplication *app, GFile **files, int n_files, const char *hint);
/* Actions */
static void preferences_activated(GSimpleAction *action, GVariant *parameter, gpointer app);
static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app);

/* skel_app_new(): interface for application creation, returns a
   pointer to a new skel application. */
SkelApp * 
skel_app_new(void)
{
    return g_object_new(SKEL_APP_TYPE,
			"application-id", "ert.gtk.skel",
			"flags", G_APPLICATION_HANDLES_OPEN,
			NULL);
}

/* skel_app_class_init(): class constructor, will be executed only
   once before the first instance is constructed. Any shared data and
   signals should be set up here. */
static void
skel_app_class_init(SkelAppClass *class)
{
    /* override parent class' functions called in response to
       signals */
    G_APPLICATION_CLASS(class)->startup  = skel_app_startup;
    G_APPLICATION_CLASS(class)->shutdown = skel_app_shutdown;
    G_APPLICATION_CLASS(class)->activate = skel_app_activate;
    G_APPLICATION_CLASS(class)->open     = skel_app_open;
}

/* skel_app_init(): object constructor, initialises a new skel
   application instance in self. */
static void
skel_app_init(SkelApp *self)
{
    return;
}

/* skel_app_startup(): sets up the application when it first starts
   and receives the startup signal */
static void
skel_app_startup(GApplication *app)
{
    GtkBuilder *builder;
    GMenuModel *app_menu;
    static GActionEntry app_entries[] =	{
	{ "preferences", preferences_activated, NULL, NULL, NULL },
	{ "quit",        quit_activated,        NULL, NULL, NULL }
    };
    const char *quit_accels[2] = { "<Ctrl>Q", NULL };

    /* chaining up required so that signals propagate */
    G_APPLICATION_CLASS(skel_app_parent_class)->startup(app);

    /* load the application menu ui file and associate the resulting
       menu model with the menu button that we’ve added to the
       headerbar. */
    g_action_map_add_action_entries(G_ACTION_MAP(app),
				    app_entries, G_N_ELEMENTS(app_entries),
				    app);

    /* register keybinds for window */
    gtk_application_set_accels_for_action(GTK_APPLICATION(app),
					  "app.quit", quit_accels);
}

/* skel_app_shutdown(): perform any shutdown tasks before the
   application is closed */
static void
skel_app_shutdown(GApplication *app)
{
    /* chaining up required */
    G_APPLICATION_CLASS(skel_app_parent_class)->shutdown(app);
}

/* skel_app_activate(): when the application receives an activate
   signal this is called to show the default first window of the skel
   application. This corresponds to when it is launched from an
   application menu. */
static void
skel_app_activate(GApplication *app)
{
    SkelAppWindow *win;

    win = skel_app_window_new(SKEL_APP(app));
    gtk_window_present(GTK_WINDOW(win));
}

/* skel_app_open(): when the application receives an open signal,
   called to open the file(s) provided in a new skel application
   window. This corresponds to when it is launched by with command
   line arguments or from selecting a skel file in a file browser. */
static void skel_app_open(GApplication  *app,
			  GFile        **files,
			  int            n_files,
			  const char    *hint)
{
    GList *windows;
    SkelAppWindow *win;
    int i;

    windows = gtk_application_get_windows (GTK_APPLICATION (app));
    if (windows)
	win = SKEL_APP_WINDOW (windows->data);
    else
	win = skel_app_window_new (SKEL_APP (app));

    for (i = 0; i < n_files; i++)
	skel_app_window_open (win, files[i]);

    gtk_window_present (GTK_WINDOW (win));    
}

static void
preferences_activated(GSimpleAction *action,
		      GVariant      *parameter,
		      gpointer      app)
{
}

static void
quit_activated (GSimpleAction *action,
		GVariant      *parameter,
		gpointer       app)
{
    g_application_quit(G_APPLICATION(app));
}
