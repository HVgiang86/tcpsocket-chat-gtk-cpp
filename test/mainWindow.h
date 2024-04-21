#ifndef _MAINWINDOW_H
#define _MAINwINDOW_H

#include <gtk/gtk.h>
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include "common.h"
#include "chatWindow.h"

GdkColor color;
gint label_event(GtkWidget *widget, GdkEventButton *event, gpointer func_data);

void mainWindow();
void setUsername();


#endif
