#ifndef __IO_H_
# define __IO_H_

# define SEND_BUF_SIZ 4096
# define RECV_BUF_SIZ 4096

int printmsg(const char *format, ...);
int printmsgln(const char *format, ...);
int scanmsg(const char *format, ...);

#endif  /* __IO_H_ */
