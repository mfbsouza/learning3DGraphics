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
  const int window_width = 800;
  const int window_height = 600;

  Window screen(window_title, window_width, window_height);
  screen.GraphicsAPI();

  Shader testingShader(
    "/home/bois/git/learning_3D/OpenGL/shaders/shader.vert",
    "/home/bois/git/learning_3D/OpenGL/shaders/shader.frag"
  );

  /*
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
  */

  float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
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

  unsigned int VAO, VBO; //, EBO;
  unsigned int TBO[2];
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  //glGenBuffers(1, &EBO);
  glGenTextures(2, TBO);

  /* bind the Vertex Array Object first, then bind and set vertex buffer(s),
   * and then configure vertex attributes(s).
   */

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  /*
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  */

  // position attribute
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE,
    5 * sizeof(float), (void*)0
  );
  glEnableVertexAttribArray(0);

  // color attribute
  /*
  glVertexAttribPointer(
    1, 3, GL_FLOAT, GL_FALSE,
    8 * sizeof(float), (void*)(3 * sizeof(float))
  );
  glEnableVertexAttribArray(1);
  */

  // texture coord
  glVertexAttribPointer(
    1, 2, GL_FLOAT, GL_FALSE,
    5 * sizeof(float), (void*)(3 * sizeof(float))
  );
  glEnableVertexAttribArray(1);

  // load and create a texture 1
  glBindTexture(GL_TEXTURE_2D, TBO[0]);
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
  glBindTexture(GL_TEXTURE_2D, TBO[1]);
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
  glEnable(GL_DEPTH_TEST);
  bool running = true;
  while (running) {

    while (screen.PollEvents()) {
      running = !screen.shouldClose();
    }

    // input

    // clear screen
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TBO[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, TBO[1]);

    // activate shader
    testingShader.use();

    // create transformations
    glm::mat4 model      = glm::mat4(1.0f); // Local Space -> World Space
    glm::mat4 view       = glm::mat4(1.0f); // World Space -> View Space
    glm::mat4 projection = glm::mat4(1.0f); // View Space  -> Clip Space

    /*model = glm::rotate(
      model,
      ((float)SDL_GetTicks()/1000) * glm::radians(50.0f),
      glm::vec3(0.5f,1.0f,0.0f)
    );*/
    view  = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f));
    projection = glm::perspective(
      glm::radians(45.0f),
      (float)window_width / (float)window_height,
      0.1f,
      100.0f
    );

    // send to the GPU Shaders
    //unsigned int modelLoc = glGetUniformLocation(testingShader.ID, "model");
    unsigned int viewLoc = glGetUniformLocation(testingShader.ID, "view");
    unsigned int projLoc = glGetUniformLocation(testingShader.ID, "projection");

    //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // render
    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 10; i++) {
      // calculate the model matrix for each object before drawing
      model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * ((float)SDL_GetTicks()/1000) * (i+1);
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f,0.3f,0.5f));

      // send to vertex shader
      unsigned int modelLoc = glGetUniformLocation(testingShader.ID, "model");
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

      // draw
      glDrawArrays(GL_TRIANGLES,0,36);
    }

    // swap buffers
    screen.SwapBuffers();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  //glDeleteBuffers(1, &EBO);
  glDeleteTextures(2, TBO);

  return 0;
}
