#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <communicate.h>
#include "camera.h"

#define TRANSMIT_FREQ 10
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 48555

int main()
{
    struct camera_env image;
    conn server = endpoint_init(SERVER_IP, SERVER_PORT, CLIENT);

    while (1)
    {
        load_camera_data(&image);

        char *image_json = camera_env_to_json(image);
        conn_write(server, image_json, strlen(image_json));
        free(image_json);

        sleep(TRANSMIT_FREQ);
    }

    return 0;
}
