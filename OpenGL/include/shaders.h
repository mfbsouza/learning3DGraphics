#ifndef SHADERS_H
#define SHADERS_H

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>

void compile_shaders();
void link_shaders();
void load_vertex_array();
void draw();
void shader_exit();

#endif
