#include <cstdlib>
#include <iostream>
#include <engine/window.hpp>
#include <engine/shader.hpp>

int main(void) {

  const char *window_title = "Hello World";
  const int window_width = 640;
  const int window_height = 480;

  Window screen(window_title, window_width, window_height);
  screen.GraphicsAPI();

  Shader testingShader("/home/bois/git/learning_3D/OpenGL/shaders/shader.vert",
                       "/home/bois/git/learning_3D/OpenGL/shaders/shader.frag");

  float vertices[] = {
    // positions         // colors
    0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
    0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // top
  };

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  // glBindVertexArray(0);

  // render loop
  bool running = true;
  while (running) {

    while (screen.PollEvents()) {
      running = !screen.shouldClose();
    }

    // input

    // rendering
    glClearColor(0.2f,0.2f,0.2f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // render the triangle
    testingShader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // check call events and swap buffers
    screen.SwapBuffers();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VAO);

  return 0;
}
