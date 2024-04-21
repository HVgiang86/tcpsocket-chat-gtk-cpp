#ifndef _LOGIN_H
#define _LOGIN_H

#include <iostream>
//#include <string.h>
//#include <stdlib.h>
//#include <sys/socket.h>
#include <sys/types.h>
//#include <arpa/inet.h>

#include "common.h"
#include "mainWindow.h"

void login_window_init();
void login_connect(const char *uname,const char *pword);
void get_login_info(GtkWidget *widget,gpointer data);


#endif
