#ifndef COMMUNICATE_H
#define COMMUNICATE

#include <sys/types.h>

#define CLIENT 1
#define SERVER 2

typedef struct
{
    short error;
    char *error_msg;
    int fd;
    unsigned long max_bytes;
    unsigned short port;
    char *ip;
} conn;

// Server-only prototype.
conn conn_listen(conn server_conn);

// Initialisor for both client and server.
conn endpoint_init(char *ip, unsigned short port, short endpoint_type);

// Generic prototypes.
ssize_t conn_write(conn connection, const void *buffer, size_t len);
ssize_t conn_read(conn connection, void *buffer, size_t len);
void conn_close(conn *restrict connection);

#endif
