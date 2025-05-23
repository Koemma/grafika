#include "camera.h"
#include "scene.h"
#include <GL/gl.h>
#include <math.h>

void init_camera(Camera *camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    camera->is_preview_visible = false;
}

void update_camera(Camera *camera, double time, const Scene *scene)
{
    double angle;
    double side_angle;
    vec3 new_position = camera->position;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    new_position.x += cos(angle) * camera->speed.y * time;
    new_position.y += sin(angle) * camera->speed.y * time;
    new_position.x += cos(side_angle) * camera->speed.x * time;
    new_position.y += sin(side_angle) * camera->speed.x * time;

    BoundingBox box = scene_get_bounding_box(scene);
    if (is_inside_box(&box, new_position))
    {
        
    }
    else
    {
        camera->position = new_position;
    }
}

void set_view(const Camera *camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera *camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0)
    {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0)
    {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0)
    {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0)
    {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera *camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera *camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_topview(Camera *camera)
{
    camera->position.x = 0.0f;
    camera->position.y = 5.0f;
    camera->position.z = 0.0f;
    camera->rotation.x = 90.0f;
    camera->rotation.y = 0.0f;
    camera->rotation.z = 0.0f;
}

void set_camera_sideview(Camera *camera)
{
    camera->position.x = 5.0f;
    camera->position.y = 0.0f;
    camera->position.z = 0.1f;
    camera->rotation.x = 0.0f;
    camera->rotation.y = 90.0f;
    camera->rotation.z = 0.0f;
}

void set_camera_frontview(Camera *camera)
{
    camera->position.x = 0.0f;
    camera->position.y = 0.0f;
    camera->position.z = 10.0f;
    camera->rotation.x = 0.0f;
    camera->rotation.y = 0.0f;
    camera->rotation.z = 90.0f;
}

void reset_camera_view(Camera *camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
