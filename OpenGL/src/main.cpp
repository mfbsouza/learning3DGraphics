#include <cstdlib>
#include <iostream>
#include <engine/window.hpp>
#include <engine/shader.hpp>

#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left
  };

  unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  SDL_Surface *tex1 = IMG_Load(
    "/home/bois/git/learning_3D/OpenGL/textures/container.jpg"
  );
  if (!tex1) {
    std::cout << "tex1 error" << '\n';
    exit(EXIT_FAILURE);
  }
  SDL_Surface *tex2 = IMG_Load(
    "/home/bois/git/learning_3D/OpenGL/textures/awesomeface.png"
  );
  if (!tex2) {
    std::cout << "tex2 error" << '\n';
    exit(EXIT_FAILURE);
  }

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
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex1->w, tex1->h, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, tex1->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  SDL_FreeSurface(tex1);

  // load and create a texture 2
  glBindTexture(GL_TEXTURE_2D, TBO2);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // gen texture and mipmaps
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex2->w, tex2->h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, tex2->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  SDL_FreeSurface(tex2);

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
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TBO1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, TBO2);

    // create transformations matrix
    glm::mat4 transform = glm::mat4(1.0f); // indentity matrix
    transform = glm::translate(
      transform,
      glm::vec3(0.5f,-0.5f,0.0f)
    );
    transform = glm::rotate(
      transform,
      ((float)SDL_GetTicks())/1000,
      glm::vec3(0.0f, 0.0f, 1.0f)
    );
    // create transformations matrix for second container
    glm::mat4 transform2 = glm::mat4(1.0f); // indentity matrix
    transform2 = glm::translate(
      transform2,
      glm::vec3(
        sin(((float)SDL_GetTicks())/1000),
        sin(((float)SDL_GetTicks())/1000),
        0.0f
      )
    );
    transform2 = glm::rotate(
      transform2,
      ((float)SDL_GetTicks())/1000 + glm::radians(90.0f),
      glm::vec3(0.0f, 0.0f, 1.0f)
    );
    transform2 = glm::scale(
      transform2,
      glm::vec3(
        sin(((float)SDL_GetTicks())/1000),
        sin(((float)SDL_GetTicks())/1000),
        sin(((float)SDL_GetTicks())/1000)
      )
    );

    // render container
    testingShader.use();

    // send transform matrix to shader
    glUniformMatrix4fv(
      glGetUniformLocation(testingShader.ID, "transform"),
      1,
      GL_FALSE,
      glm::value_ptr(transform)
    );

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glUniformMatrix4fv(
      glGetUniformLocation(testingShader.ID, "transform"),
      1,
      GL_FALSE,
      glm::value_ptr(transform2)
    );
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
