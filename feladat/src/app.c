#include "app.h"
#include <stdio.h>
#include <texture.h>

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
    // init_textures();

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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
            case SDL_SCANCODE_UP:
                /*app->scene.platform_scale_z += 0.1f;
                if (app->scene.platform_scale_z > 1.0f)
                {
                    app->scene.platform_scale_z = 1.0f;
                    printf("Z scale UP: %.2f\n", app->scene.platform_scale_z);
                }*/
                break;
            case SDL_SCANCODE_DOWN:
                /*app->scene.platform_scale_z -= 0.1f;
                if (app->scene.platform_scale_z < 0.05f) {
                    app->scene.platform_scale_z = 0.05f;
                    printf("Z scale down: %.2f\n", app->scene.platform_scale_z);
                }*/
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

    //printf("x = %f, y = %f\n", x, y);

    if (x >= 0.005f && x <= 0.185f && y >= 0.9f && y <= 0.95f)
    {
        //printf("Gomb\n");
        cycle_texture(scene);
    }
}

void update_app(App *app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
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
    draw_panel();

    if (app->camera.is_preview_visible)
    {
        // show_texture_preview();
    }

    SDL_GL_SwapWindow(app->window);
}

void draw_panel()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glColor3f(1.0, 0.6, 0.8);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.2f, 1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    draw_button(0.005f, 0.95f, 0.185f, 0.05f, 1.0f, 0.8f, 0.9f);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void draw_button(float x, float y, float w, float h, float r, float g, float b)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(w, 0);
    glVertex2f(w, -h);
    glVertex2f(0, -h);
    glEnd();
    glPopMatrix();
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

    SDL_Quit();
}