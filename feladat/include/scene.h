#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <model.h>
#include <stdbool.h>
typedef struct BoundingBox {
    float min_x, max_x;
    float min_y, max_y;
    float min_z, max_z;
} BoundingBox;

typedef struct Scene
{
    Model stage;
    Model screen;
    Model platform;
    Material material;
    GLuint stage_texture_id;
    GLuint screen_texture_id;
    GLuint platform_texture_id;
    BoundingBox screen_box;
    float platform_scale_z;
    int texture_index; 
    float spot_red;
    float spot_green;
    float spot_blue;
    bool screen_lighting;
} Scene;

void init_scene(Scene* scene);
BoundingBox calculate_bounding_box(const Model* model);
BoundingBox scene_get_bounding_box(const Scene* scene);
bool is_inside_box(const BoundingBox *box, const vec3 position);
void set_lighting();
void set_spotlight(float px, float py, float pz, float dx, float dy, float dz, float r, float g, float b);
void set_screen_lighting(const Scene *scene, float px, float py, float pz);
void set_material(const Material* material);
void update_scene(Scene* scene);
void render_scene(const Scene* scene);
void draw_cube(float size);
void drawFloor();
void drawLights();

#endif
