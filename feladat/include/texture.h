#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include <scene.h>

struct Scene;
typedef GLubyte Pixel[4];

void cycle_texture(struct Scene* scene, int dir);
GLuint load_texture(char* filename);

extern GLuint current_texture;

#endif
