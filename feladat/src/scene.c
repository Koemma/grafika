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

    scene->material.shininess = 100.0;

    scene->spot_red = -0.1;
    scene->spot_green = -0.1;
    scene->spot_blue = -0.1;

    scene->screen_box = calculate_bounding_box(&(scene->screen));
}

BoundingBox calculate_bounding_box(const Model *model)
{
    BoundingBox box;

    if (model->n_vertices == 0)
    {
        box.min_x = box.min_y = box.min_z = 0.0f;
        box.max_x = box.max_y = box.max_z = 0.0f;
        return box;
    }

    box.min_x = box.max_x = model->vertices[1].x;
    box.min_y = box.max_y = model->vertices[1].y;
    box.min_z = box.max_z = model->vertices[1].z;

    for (int i = 2; i <= model->n_vertices; i++)
    {
        float x = model->vertices[i].x;
        float y = model->vertices[i].y;
        float z = model->vertices[i].z;

        if (x < box.min_x)
            box.min_x = x;
        if (x > box.max_x)
            box.max_x = x;
        if (y < box.min_y)
            box.min_y = y;
        if (y > box.max_y)
            box.max_y = y;
        if (z < box.min_z)
            box.min_z = z;
        if (z > box.max_z)
            box.max_z = z;
    }

    return box;
}

bool is_inside_box(const BoundingBox *box, const vec3 position)
{
    return position.x >= box->min_x && position.x <= box->max_x &&
           position.y >= box->min_y && position.y <= box->max_y &&
           position.z >= box->min_z && position.z <= box->max_z;
}

BoundingBox scene_get_bounding_box(const Scene *scene)
{
    return scene->screen_box;
}

void set_lighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float ambient_light[] = {0.8f, 0.8f, 0.7f, 1.0f};
    float diffuse_light[] = {1.0f, 1.0f, 0.9f, 1.0f};
    float specular_light[] = {1.0f, 1.0f, 0.9f, 1.0f};
    float position[] = {0.0f, -0.5f, 10.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_spotlight(float px, float py, float pz, float dx, float dy, float dz, float r, float g, float b)
{

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);

    float light_pos[] = {px, py, pz, 1.0f};
    float light_dir[] = {dx, dy, dz};

    float ambient[] = {0.3f, 0.3f, 0.2f, 1.0f};
    float diffuse[] = {r, g, b, 1.0f};
    float specular[] = {r, g, b, 1.0f};

    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

    if (r == -0.1 || g == -0.1 || b == -0.1)
    {
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0f);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.0f);
        set_lighting();

    }
    else
    {
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0f);
    }

    float emission[] = {1.0f, 1.0f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);

    glPushMatrix();
    glTranslatef(px, py, pz);
    glColor3f(1.0f, 1.0f, 0.8f);
    draw_cube(0.05f);
    glPopMatrix();

    float no_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
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
    (void)scene;
}

void render_scene(const Scene *scene)
{
    set_material(&(scene->material));
    set_lighting();
    set_spotlight(0.0f, 3.75f, 1.575f, 0.0f, -0.7f, -1.0f, scene->spot_red, scene->spot_green, scene->spot_blue);
    set_spotlight(1.0f, 3.75f, 1.575f, -0.5f, -0.7f, -1.0f, scene->spot_red, scene->spot_green, scene->spot_blue);
    set_spotlight(-1.0f, 3.75f, 1.575f, 0.5f, -0.7f, -1.0f, scene->spot_red, scene->spot_green, scene->spot_blue);
    drawFloor();
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

void draw_cube(float size)
{
    float half = size / 2.0f;

    glBegin(GL_QUADS);
    glVertex3f(-half, -half, half);
    glVertex3f(half, -half, half);
    glVertex3f(half, half, half);
    glVertex3f(-half, half, half);

    glVertex3f(-half, -half, -half);
    glVertex3f(-half, half, -half);
    glVertex3f(half, half, -half);
    glVertex3f(half, -half, -half);

    glVertex3f(-half, -half, -half);
    glVertex3f(-half, -half, half);
    glVertex3f(-half, half, half);
    glVertex3f(-half, half, -half);

    glVertex3f(half, -half, -half);
    glVertex3f(half, half, -half);
    glVertex3f(half, half, half);
    glVertex3f(half, -half, half);

    glVertex3f(-half, half, -half);
    glVertex3f(-half, half, half);
    glVertex3f(half, half, half);
    glVertex3f(half, half, -half);

    glVertex3f(-half, -half, -half);
    glVertex3f(half, -half, -half);
    glVertex3f(half, -half, half);
    glVertex3f(-half, -half, half);
    glEnd();
}

void drawFloor()
{
    glBegin(GL_QUADS);

    glColor3f(0.3, 0.25, 0.25);
    glVertex3f(10.0, 10.0, -0.001);
    glVertex3f(-10.0, 10.0, -0.001);
    glVertex3f(-10.0, -10.0, -0.001);
    glVertex3f(10.0, -10.0, -0.001);

    glEnd();
}

void drawLights()
{
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);

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