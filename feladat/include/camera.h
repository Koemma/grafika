#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "scene.h"

#include <stdbool.h>

struct Scene;
typedef struct Scene Scene;
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
    bool is_preview_visible;
} Camera;

void init_camera(Camera* camera);
void update_camera(Camera* camera, double time, const Scene* scene);
void set_view(const Camera* camera);
void rotate_camera(Camera* camera, double horizontal, double vertical);
void set_camera_speed(Camera* camera, double speed);
void set_camera_side_speed(Camera* camera, double speed);
void set_camera_topview(Camera *camera);
void set_camera_sideview(Camera *camera);
void set_camera_frontview(Camera *camera);
void reset_camera_view(Camera *camera);

#endif
