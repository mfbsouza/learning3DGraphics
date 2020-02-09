#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

int  init_gl        ( void );
void window_init    ( const char *window_title, const int screen_width, const int screen_height );
void window_quit    ( void );
void handle_keys    ( unsigned char key, int x, int y );
void update         ( void );
void render         ( void );

#endif