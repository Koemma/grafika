#include "scene.h"
#include "texture.h"

#include <load.h>
#include <draw.h>

void init_scene(Scene *scene)
{

    load_model(&(scene->stage), "assets/models/stage.obj");
    load_model(&(scene->screen), "assets/models/screen.obj");
    load_model(&(scene->platform), "assets/models/platform.obj");

    scene->platform_scale_z = 1.0f;
    scene->texture_index = 0;
    scene->screen_texture_id = load_texture("assets/textures/screen_lover.png");
    scene->stage_texture_id = load_texture("assets/textures/stage_lover.png");
    scene->platform_texture_id = load_texture("assets/textures/platform_lover.png");

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

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
    ;

    /*glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);*/
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

void update_scene(Scene* scene)
{
    (void)scene;
}

void render_scene(const Scene *scene)
{
    set_material(&(scene->material));
    set_lighting();
    glDisable(GL_LIGHTING);
    // drawLights();
    drawFloor();
    glEnable(GL_LIGHTING);
    draw_model(&(scene->stage), scene->stage_texture_id);
    draw_model(&(scene->screen), scene->screen_texture_id);
    glPushMatrix();
    for (int i = 0; i < 8; i++)
    {
        glTranslatef(0.2f, 0.0f, 0.0f);
        glScalef(1.0f, 1.0f, scene->platform_scale_z);
        draw_model(&(scene->platform), scene->platform_texture_id);
    }
    glPopMatrix();
}

void drawFloor()
{
    glBegin(GL_QUADS);

    glColor3f(0.3, 0.25, 0.25);
    glVertex3f(10.0, 10.0, 0.0);
    glVertex3f(-10.0, 10.0, 0.0);
    glVertex3f(-10.0, -10.0, 0.0);
    glVertex3f(10.0, -10.0, 0.0);

    glEnd();
}

void drawLights()
{
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    glColor3f(1, 0, 0);

    glVertex3f(2.0, 3.8, 0.4);
    glVertex3f(2.0, 2.8, 0.4);

    glVertex3f(2.0, 2.8, 0.4);
    glVertex3f(1.2, 2.6, 0.4);

    glVertex3f(1.2, 2.6, 0.4);
    glVertex3f(0.4, 2.6, 0.4);

    glVertex3f(0.4, 2.6, 0.4);
    glVertex3f(0.4, 2.0, 0.25);

    glVertex3f(0.4, 2.0, 0.25);
    glVertex3f(0.4, 1.0, 0.25);

    glVertex3f(0.4, 1.0, 0.25);
    glVertex3f(1.2, 0.0, 0.25);

    glVertex3f(1.2, 0.0, 0.25);
    glVertex3f(0.4, -1.0, 0.25);

    glVertex3f(0.4, -1.0, 0.25);
    glVertex3f(0.4, -2.6, 0.25);

    glVertex3f(0.4, -2.6, 0.25);
    glVertex3f(1.0, -2.6, 0.25);

    glVertex3f(1.0, -2.6, 0.25);
    glVertex3f(1.0, -3.4, 0.25);

    glVertex3f(1.0, -3.4, 0.25);
    glVertex3f(-1.0, -3.4, 0.25);

    glVertex3f(-1.0, -3.4, 0.25);
    glVertex3f(-1.0, -2.6, 0.25);

    glVertex3f(-1.0, -2.6, 0.25);
    glVertex3f(-0.4, -2.6, 0.25);

    glVertex3f(-0.4, -2.6, 0.25);
    glVertex3f(-0.4, -1.0, 0.25);

    glVertex3f(-0.4, -1.0, 0.25);
    glVertex3f(-1.2, 0.0, 0.25);

    glVertex3f(-1.2, 0.0, 0.25);
    glVertex3f(-0.4, 1.0, 0.25);

    glVertex3f(-0.4, 1.0, 0.25);
    glVertex3f(-0.4, 2.0, 0.25);

    glVertex3f(-0.4, 2.0, 0.25);
    glVertex3f(-0.4, 2.6, 0.4);

    glVertex3f(-0.4, 2.6, 0.4);
    glVertex3f(-1.2, 2.6, 0.4);

    glVertex3f(-1.2, 2.6, 0.4);
    glVertex3f(-2.0, 2.8, 0.4);

    glVertex3f(-2.0, 2.8, 0.4);
    glVertex3f(-2.0, 3.8, 0.4);

    glEnd();
}