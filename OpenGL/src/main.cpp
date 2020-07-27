#include <iostream>
#include <stdlib.h>
#include <window.h>
#include <shaders.h>

int main(int argc, char const *argv[]) {

  const char *window_title = "Hello World";
  const int window_width = 640;
  const int window_height = 480;
  window_init(window_title, window_width, window_height);
  check_opengl();


  compile_shaders();
  link_shaders();
  load_vertex_array();


  // main loop
  while (!glfwWindowShouldClose(window)) {

    // input
    process_input();

    // rendering
    glClearColor(0.2f,0.2f,0.2f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    draw();

    // check call events and swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  shader_exit();
  window_exit();
  return 0;
}
