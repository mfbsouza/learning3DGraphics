#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <stdlib.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern GLFWwindow *window;

void window_init(const char *title, const int width, const int height);
void window_exit();
void check_opengl();
void resize_callback(GLFWwindow *window, int width, int height);
void process_input();

#endif
