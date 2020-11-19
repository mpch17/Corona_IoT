#ifndef COMMUNICATE_H
#define COMMUNICATE

#include <sys/types.h>

#ifdef __cplusplus
#define RESTRICT
#else
#define RESTRICT restrict
#endif

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

#ifdef __cplusplus
extern "C"
{
#endif

// Server-only prototype.
conn conn_listen(conn server_conn);

// Initialisor for both client and server.
conn endpoint_init(char *ip, unsigned short port, short endpoint_type);

// Generic prototypes.
ssize_t conn_write(conn connection, const void *buffer, size_t len);
ssize_t conn_read(conn connection, void *buffer, size_t len);
void conn_close(conn *RESTRICT connection);

#ifdef __cplusplus
}
#endif

#endif
