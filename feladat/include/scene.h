#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <model.h>

typedef struct Scene
{
    Model stage;
    Model screen;
    Model platform;
    Material material;
    GLuint stage_texture_id;
    GLuint screen_texture_id;
    GLuint platform_texture_id;
    float platform_scale_z;
    int texture_index; 
} Scene;

void init_scene(Scene* scene);
void set_lighting();
void set_material(const Material* material);
void update_scene(Scene* scene);
void render_scene(const Scene* scene);
void drawFloor();
void drawLights();

#endif
