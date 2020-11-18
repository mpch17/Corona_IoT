#include "camera.h"
#include <stdlib.h>

#define DIM_MIN_SZ 4
#define DIM_MAX_SZ 40

#define RANDOM_CAM_DATA ({ \
    (struct camera_env) {.dimension.x = (rand() % DIM_MAX_SZ) + DIM_MIN_SZ, \
        .dimension.y = (rand() % DIM_MAX_SZ) + DIM_MIN_SZ, \
        .people_count = rand() % 200}; \
})

// Takes picture and parses data into struct camera_env.
void load_camera_data(struct camera_env *restrict camera)
{
    *camera = RANDOM_CAM_DATA;
}
