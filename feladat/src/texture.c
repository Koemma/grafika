#include "texture.h"
#include "scene.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

GLuint current_texture;

void cycle_texture(Scene* scene)
{
    static const char* texture_files_screen[] = {
        "assets/textures/screen_lover.png",
        "assets/textures/screen_fearless.png",
        "assets/textures/screen_red.png",
        "assets/textures/screen_speaknow.png",
        "assets/textures/screen_reputation.png",
        "assets/textures/screen_folklore.png",
        "assets/textures/screen_evermore.png",
        "assets/textures/screen_1989.png",
        "assets/textures/screen_ttpd.png",
        "assets/textures/screen_midnights.png"
    };

    static const char* texture_files_stage[] = {
        "assets/textures/stage_lover.png",
        "assets/textures/stage_fearless.png",
        "assets/textures/stage_red.png",
        "assets/textures/stage_speaknow.png",
        "assets/textures/stage_reputation.png",
        "assets/textures/stage_folklore.png",
        "assets/textures/stage_evermore.png",
        "assets/textures/stage_1989.png",
        "assets/textures/stage_ttpd.png",
        "assets/textures/stage_midnights.png"
    };

    static const char* texture_files_platform[] = {
        "assets/textures/platform_lover.png",
        "assets/textures/platform_fearless.png",
        "assets/textures/platform_red.png",
        "assets/textures/platform_speaknow.png",
        "assets/textures/platform_reputation.png",
        "assets/textures/platform_folklore.png",
        "assets/textures/platform_evermore.png",
        "assets/textures/platform_1989.png",
        "assets/textures/platform_ttpd.png",
        "assets/textures/platform_midnights.png"
    };

    scene->texture_index = (scene->texture_index + 1) % 10;
    scene->screen_texture_id = load_texture((char*)texture_files_screen[scene->texture_index]);
    scene->stage_texture_id = load_texture((char*)texture_files_stage[scene->texture_index]);
    scene->platform_texture_id = load_texture((char*)texture_files_platform[scene->texture_index]);
}

GLuint load_texture(char *filename)
{
    SDL_Surface *surface;
    GLuint texture;

    surface = IMG_Load(filename);

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (Pixel *)(surface->pixels));

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}