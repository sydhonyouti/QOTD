#pragma once
// qotd.h    Header file for QOTD project
#include <winsock2.h>

const int  MAX_PORT = 128;
const int  MAX_RECV_BUF = 2048;
const int  MAX_SEND_BUF = 2048;
const int  WAIT_TIME = 10;

int    wait(SOCKET, int, int);
SOCKET connectsock(char*, char*, char*);
int UDP_recv(SOCKET, char*, int, char*, char*);
int UDP_send(SOCKET, char*, int, char*, char*);

