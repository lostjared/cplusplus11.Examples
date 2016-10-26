/* Adapted from "the Linux Programming Interface"
 	Chapter 64

 
*/

#ifndef __TERMINAL__H__
#define __TERMINAL__H__


#include<iostream>
#include<termios.h>
#include<sys/ioctl.h>
#include<cstring>
#include<cstdlib>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>

void error(const std::string &text, bool err = true);
int pty_MasterOpen(char *name, size_t len);
pid_t pty_Fork(int *m_fd, char *name, size_t len, const termios *st, winsize *s_size);
int tty_SetRaw(int fd, termios *prev);




#endif

