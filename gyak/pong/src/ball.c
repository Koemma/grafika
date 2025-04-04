#include "ball.h"

#include <GL/gl.h>

#include <math.h>
#define M_PI 3.14159265358979323846

void init_ball(Ball *ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 200;
    ball->speed_y = 200;
    ball->rotation = 0.0;
    ball->rotation_speed = 60;
}

void update_ball(Ball *ball, double time, int width)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
    ball->rotation += ball->rotation_speed * time;
}

void render_ball(Ball *ball)
{
    double angle;
    double x;
    double y;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glRotatef(ball->rotation, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1)
    {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.8;
    }
    glEnd();
    glPopMatrix();
}
