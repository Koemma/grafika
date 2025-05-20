#include "app.h"
#include <stdio.h>
#include <texture.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void init_app(App *app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Stage",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL)
    {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0)
    {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL)
    {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.05, 0.1, 0.3, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10);
}

void handle_app_events(App *app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1);
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_Z:
                set_camera_topview(&(app->camera));
                break;
            case SDL_SCANCODE_X:
                set_camera_sideview(&(app->camera));
                break;
            case SDL_SCANCODE_Y:
                set_camera_frontview(&(app->camera));
                break;
            case SDL_SCANCODE_R:
                reset_camera_view(&(app->camera));
                break;
            case SDL_SCANCODE_F1:
                app->scene.show_help = !(app->scene.show_help);
                break;
            case SDL_SCANCODE_UP:
                app->scene.platform_scale_z += 0.1f;
                if (app->scene.platform_scale_z > 1.0f)
                {
                    app->scene.platform_scale_z = 1.0f;
                    printf("Z scale UP: %.2f\n", app->scene.platform_scale_z);
                }
                break;
            case SDL_SCANCODE_DOWN:
                app->scene.platform_scale_z -= 0.1f;
                if (app->scene.platform_scale_z < 0.05f)
                {
                    app->scene.platform_scale_z = 0.05f;
                    printf("Z scale down: %.2f\n", app->scene.platform_scale_z);
                }
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            handle_button_clicks(&app->scene, mouse_x, mouse_y);
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down)
            {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void handle_button_clicks(Scene *scene, int mouse_x, int mouse_y)
{
    int window_w, window_h;
    SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &window_w, &window_h);

    float x = (float)mouse_x / window_w;
    float y = 1.0f - (float)mouse_y / window_h;

    if (x >= 0.005f && x <= 0.0525f && y >= 0.9f && y <= 0.95f)
    {
        if (scene->texture_index == 0)
        {
            cycle_texture(scene, 9);
        }
        else
        {
            cycle_texture(scene, -1);
        }
    }
    else if (x >= 0.1475f && x <= 0.195f && y >= 0.9f && y <= 0.95f)
    {
        cycle_texture(scene, 1);
    }

    if (x >= 0.005f && x <= 0.19f && y >= 0.8f && y <= 0.85f)
    {
        scene->screen_lighting = !(scene->screen_lighting);
    }

    if (x >= 0.005f && x <= 0.0525f && y >= 0.7f && y <= 0.75f)
    {
        scene->spot_red += 0.25;
        if (scene->spot_red >= 2.0)
        {
            scene->spot_red = 0.0;
        }
    }
    else if (x >= 0.0525f && x <= 0.1f && y >= 0.7f && y <= 0.75f)
    {
        scene->spot_green += 0.25;
        if (scene->spot_green >= 2.0)
        {
            scene->spot_green = 0.0;
        }
    }
    else if (x >= 0.1f && x <= 0.1475f && y >= 0.7f && y <= 0.75f)
    {
        scene->spot_blue += 0.25;
        if (scene->spot_blue >= 2.0)
        {
            scene->spot_blue = 0.0;
        }
    }
    else if (x >= 0.1475f && x <= 0.195f && y >= 0.7f && y <= 0.75f)
    {
        scene->spot_red = -0.1;
        scene->spot_green = -0.1;
        scene->spot_blue = -0.1;
    }
}

void update_app(App *app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time, &(app->scene));
    update_scene(&(app->scene));
}

void render_app(App *app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();
    glPushMatrix();

    if (app->camera.is_preview_visible)
    {
        show_texture_preview();
    }

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if(!(app->scene.show_help)){
        draw_point(&(app->camera));
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

    SDL_GL_SwapWindow(app->window);
}

void draw_point(const Camera *camera)
{
    float norm_x = camera->position.x / 18 + 0.5;
    float norm_y = camera->position.y / 9 + 0.4;

    float marker_x = 0.8f + norm_x * 0.2f;
    float marker_y = 0.7f + norm_y * 0.3f;

    float size = 0.004f;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glColor3f(1.0f, 0.0f, 0.4f);

    glBegin(GL_QUADS);
    if (marker_x > 1.0)
    {
        marker_x = 1.0;
    }
    else if (marker_x < 0.8)
    {
        marker_x = 0.8;
    }
    else if (marker_y > 1.0)
    {
        marker_y = 1.0;
    }
    else if (marker_y < 0.7)
    {
        marker_y = 0.7;
    }
    glVertex2f(marker_x - size, marker_y - size);
    glVertex2f(marker_x + size, marker_y - size);
    glVertex2f(marker_x + size, marker_y + size);
    glVertex2f(marker_x - size, marker_y + size);

    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);
}

void destroy_app(App *app)
{
    if (app->gl_context != NULL)
    {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL)
    {
        SDL_DestroyWindow(app->window);
    }

    IMG_Quit();
    SDL_Quit();
}