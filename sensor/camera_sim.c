#include "camera.h"
#include <stdlib.h>
#include <stdio.h>

#define DIM_MIN_SZ 4
#define DIM_MAX_SZ 40

#define RANDOM_CAM_DATA ({ \
    (struct camera_env) {.dimension.x = (rand() % DIM_MAX_SZ) + DIM_MIN_SZ, \
        .dimension.y = (rand() % DIM_MAX_SZ) + DIM_MIN_SZ, \
        .people_count = rand() % 200, .id = rand()}; \
})

// Takes picture and parses data into struct camera_env.
void load_camera_data(struct camera_env *restrict camera)
{
    *camera = RANDOM_CAM_DATA;
}

// Represents struct in JSON.
char *camera_env_to_json(struct camera_env ce)
{
    char *json = malloc(70);
    sprintf(json, "{node_type: camera, id: %d, people_count: %d, x: %d, y: %d}", ce.id, ce.people_count, ce.dimension.x, ce.dimension.y);

    return json;
}
