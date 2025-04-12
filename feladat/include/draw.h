#ifndef OBJ_DRAW_H
#define OBJ_DRAW_H

#include "model.h"
#include <GL/gl.h>

void draw_model(const Model* model, GLuint texture_id);
void draw_triangles(const Model* model);

#endif
