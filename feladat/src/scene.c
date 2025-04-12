#include "scene.h"

#include <load.h>
#include <draw.h>

void init_scene(Scene *scene)
{
    load_model(&(scene->stage), "assets/models/stage.obj");
    load_model(&(scene->screen), "assets/models/screen.obj");
    load_model(&(scene->platform), "assets/models/platform.obj");

    //scene->stage_texture_id = load_texture("assets/textures/lover_stage.png");
    //scene->screen_texture_id = load_texture("assets/textures/lover_screen.png");
    //scene->platform_texture_id = load_texture("assets/textures/lover_screen.png");

    scene->material.ambient.red = 0.6;
    scene->material.ambient.green = 0.6;
    scene->material.ambient.blue = 0.6;

    scene->material.diffuse.red = 0.6;
    scene->material.diffuse.green = 0.6;
    scene->material.diffuse.blue = 0.6;

    scene->material.specular.red = 0.6;
    scene->material.specular.green = 0.6;
    scene->material.specular.blue = 0.6;

    scene->material.shininess = 0.0;
}

void set_lighting()
{
    float ambient_light[] = {1.0f, 1.0f, 1.0, 1.0f};
    float diffuse_light[] = {1.0f, 1.0f, 1.0, 1.0f};
    float specular_light[] = {1.0f, 1.0f, 1.0, 1.0f};
    float position[] = {0.0f, 0.0f, 10.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene)
{
}

void render_scene(const Scene *scene)
{
    set_material(&(scene->material));
    set_lighting();
    // draw_origin();
    draw_model(&(scene->stage), scene->stage_texture_id);
    draw_model(&(scene->screen), scene->screen_texture_id);
    glPushMatrix();
    for (int i = 0; i < 8; i++)
    {
        glTranslatef(0.2f, 0.0f, 0.0f);
        draw_model(&(scene->platform), scene->platform_texture_id);
    }
    glPopMatrix();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}