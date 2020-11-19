#include "communicate.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define ERR_MSG_LEN 50

// Returns error conn instance with error message.
#define ERR_CONN(msg, len) ({ \
    conn c = {.error = 1, .error_msg = malloc(len)}; \
    sprintf(c.error_msg, "%s\0", msg); \
    c; \
})

// Listens for client trying to connect.
// Only for the server.
conn conn_listen(conn server_conn)
{
#ifdef DEBUG
    printf("Waiting for connection on port %d...\n", server_conn.port);
#endif

    struct sockaddr_in addr;
    size_t addr_len = sizeof(addr);
    int opt = 1;
    conn connection;

    else if (listen(server_conn.fd, 10) < 0)
        return ERR_CONN("Failed listening", ERR_MSG_LEN);

    else if ((connection.fd = accept(server_conn.fd, (struct sockaddr *) &addr, (socklen_t *) &addr_len)) < 0)
        return ERR_CONN("Failed accepting client", ERR_MSG_LEN);

    return connection;  // TODO: Add client info, such as its address.
}

// Initialises endpoint as client or server. Argument ip should be NULL is used for server.
conn endpoint_init(char *ip, unsigned short port, short endpoint_type)
{
    struct sockaddr_in address;
    conn connection = {.port = port};

    if (endpoint_type == CLIENT && ip != NULL)
    {
        connection.ip = malloc(strlen(ip) + 1);
        strcpy(connection.ip, ip);
    }

    if ((connection.fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return ERR_CONN("Failed init socket", ERR_MSG_LEN);

    if (endpoint_type == SERVER && setsockopt(connection.fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        return ERR_CONN("Failed setting socket option", ERR_MSG_LEN);

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (endpoint_type == SERVER)
    {
        address.sin_addr.s_addr = INADDR_ANY;

        if (bind(connection.fd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
            return ERR_CONN("Failed binding", ERR_MSG_LEN);
    }

    else
    {
        if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0)
            return ERR_CONN("Failed converting IP to binary\nIP might be invalid", ERR_MSG_LEN);

        else if (connect(connection.fd, (struct sockaddr *) &address, sizeof(address)) < 0)
            return ERR_CONN("Connecting failed", ERR_MSG_LEN);
    }

    return connection;
}

// Writes message to file descriptor.
ssize_t conn_write(conn connection, const void *buffer, size_t len)
{
#ifdef DEBUG
    printf("Writing to %d...\n", connection.fd);
#endif

    return send(connection.fd, buffer, len, 0);
}

// Reads message from file descriptor.
ssize_t conn_read(conn connection, void *buffer, size_t len)
{
#ifdef DEBUG
    printf("Reading from %d...\n", connection.fd);
#endif

    return read(connection.fd, buffer, len);
}

// Closes connection.
void conn_close(conn *restrict connection)
{
#ifdef DEBUG
    printf("Closing %d...\n", connection->fd);
#endif

    close(connection->fd);
    *connection = ERR_CONN("Connection closed.", ERR_MSG_LEN);
}
