#ifndef _ftp_h_
#define _ftp_h_

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

#define MSG_BODY 248
//TODO check to see if int is 4 bits
#define MSG_SIZE (MSG_BODY+8)

#define PORT 4844
#define SEND 1
#define RECV 2
#define DATA 100
#define END_DATA 101
#define TEST 102
#define END_TEST 103

typedef struct {
   int mtype;
   int msize;
   char mbody[MSG_BODY];
} MSG;

typedef union {
   MSG m;
   char buf[MSG_SIZE];
} MBUF;


extern int errno;

#endif