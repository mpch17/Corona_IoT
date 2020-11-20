#ifndef CAMERA_SIM_H
#define CAMERA_SIM_H

#include <stdint.h>

struct camera_env
{
    struct dim
    {
        uint32_t x, y;  // centimeters.
    } dimension;

    struct loc
    {
        float longitude, latitude;
    } location;

    uint32_t people_count;
    uint64_t id;
    uint64_t edge_end1, edge_end2;
};

void load_camera_data(struct camera_env *restrict camera);
char *camera_env_to_json(struct camera_env ce);

#endif
