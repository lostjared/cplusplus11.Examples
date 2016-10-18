/* Adapted from "the Linux Programming Interface"
 	Chapter 44
 */

#ifndef __FIFO__H__
#define __FIFO__H__
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>

static const char *SERVER_NAME = "/tmp/seqnum_server";
static const char *FIFO_NAME_TEMPLATE = "/tmp/seqnum_cl";
static const unsigned int FIFO_NAME_LEN = sizeof(FIFO_NAME_TEMPLATE)+25;

struct Request {
    pid_t id;
    int len;
};

struct Response {
    int len;
};

#endif
