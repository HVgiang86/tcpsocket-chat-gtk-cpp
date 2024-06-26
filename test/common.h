#ifndef _COMMON_H
#define _COMMON_H
#include <gtk/gtk.h>
#include <iostream>

#define BUF_SIZE 128
#define SERVER_PORT 32000
#define SERVER_IP   "127.0.0.1"

GtkBuilder *builder;
GtkBuilder *mainwindow;
GtkWidget *window;
GtkWidget *usernameEntry;
GtkWidget *passwordEntry;
GtkWidget *button;
GtkWidget *label;
GtkWidget *eventBox;

GtkWidget *table;
GtkWidget *image;

GtkWidget *textview1;
GtkWidget *textview2;
GtkTextBuffer *textbuffer;

int socket_fd,connect_fd;
typedef struct ChatMsg{
	int who;
	int Flag;
	char Msg[50];
} ChatMsg;

typedef struct LoginPack{
	int flag;
	char username[20];
	char password[20];
} LoginPack;

typedef struct SocketPacket{

} SocketPacket;

char buf[BUF_SIZE];
char u[5];
gchar *chatmsg;

#endif
