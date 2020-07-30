#include <cstdlib>
#include <iostream>
#include <engine/window.hpp>
#include <engine/shader.hpp>

#include <stb_image.h>

int main(void) {

  const char *window_title = "Hello World";
  const int window_width = 640;
  const int window_height = 480;

  Window screen(window_title, window_width, window_height);
  screen.GraphicsAPI();

  Shader testingShader("/home/bois/git/learning_3D/OpenGL/shaders/shader.vert",
                       "/home/bois/git/learning_3D/OpenGL/shaders/shader.frag");

  float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
  };

  unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  // load texture image
  int tex1_width, tex1_height, tex1_nrchannels;
  int tex2_width, tex2_height, tex2_nrchannels;

  stbi_set_flip_vertically_on_load(true); // flip y-axis cus OpenGL standards
  unsigned char *tex1_data = stbi_load(
    "/home/bois/git/learning_3D/OpenGL/textures/container.jpg",
    &tex1_width, &tex1_height, &tex1_nrchannels, 0
  );

  unsigned char *tex2_data = stbi_load(
    "/home/bois/git/learning_3D/OpenGL/textures/awesomeface.png",
    &tex2_width, &tex2_height, &tex2_nrchannels, 0
  );

  unsigned int VAO, VBO, EBO, TBO1, TBO2;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenTextures(1, &TBO1);
  glGenTextures(1, &TBO2);

  /* bind the Vertex Array Object first, then bind and set vertex buffer(s),
   * and then configure vertex attributes(s).
   */

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE,
    8 * sizeof(float), (void*)0
  );
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(
    1, 3, GL_FLOAT, GL_FALSE,
    8 * sizeof(float), (void*)(3 * sizeof(float))
  );
  glEnableVertexAttribArray(1);

  // texture coord
  glVertexAttribPointer(
    2, 2, GL_FLOAT, GL_FALSE,
    8 * sizeof(float), (void*)(6 * sizeof(float))
  );

  glEnableVertexAttribArray(2);

  // load and create a texture 1
  glBindTexture(GL_TEXTURE_2D, TBO1);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // gen texture and mipmaps
  if (tex1_data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex1_width, tex1_height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, tex1_data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else std::cout << "ERROR::READ_FILE_TEXTURE1\n";
  stbi_image_free(tex1_data);

  // load and create a texture 2
  glBindTexture(GL_TEXTURE_2D, TBO2);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // gen texture and mipmaps
  if (tex2_data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex2_width, tex2_height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, tex2_data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else std::cout << "ERROR::READ_FILE_TEXTURE2\n";
  stbi_image_free(tex2_data);

  testingShader.use();
  testingShader.setInt("texture1", 0);
  testingShader.setInt("texture2", 1);
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

    // render
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TBO1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, TBO2);

    // render container
    testingShader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // check call events and swap buffers
    screen.SwapBuffers();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteTextures(1, &TBO1);
  glDeleteTextures(1, &TBO2);

  return 0;
}
