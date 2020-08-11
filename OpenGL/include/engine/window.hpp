#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

class Window {
  public:

    // Constructor
    Window(const char *title, const int width, const int height);
    ~Window();

    void GraphicsAPI();

    // Event methods
    SDL_Event event;

    int  PollEvents();
    void SwapBuffers();
    bool shouldClose();

  private:
    SDL_Window    *window;
    SDL_GLContext  context;
};

#endif
