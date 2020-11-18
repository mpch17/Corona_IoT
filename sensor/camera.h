#ifndef CAMERA_SIM_H
#define CAMERA_SIM_H

#include <stdint.h>

struct camera_env
{
    struct dim
    {
        uint32_t x, y;  // centimeters.
    } dimension;

    uint32_t people_count;
};

void load_camera_data(struct camera_env *restrict camera);

#endif
