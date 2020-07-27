#include <shaders.h>

const char *vert_source = "#version 460\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";
const char *frag_source = "#version 460\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n\0";

int shader_program;
int vert_shader;
int frag_shader;

unsigned int VBO, VAO, EBO;

float vertices[] = {
  0.5f,  0.5f, 0.0f,  // top right
  0.5f, -0.5f, 0.0f,  // bottom right
  -0.5f, -0.5f, 0.0f,  // bottom left
  -0.5f,  0.5f, 0.0f   // top left
};

unsigned int indices[] = {  // note that we start from 0!
  0, 1, 3,  // first Triangle
  1, 2, 3   // second Triangle
};

void compile_shaders() {
  int success;
  char infolog[512];

  vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &vert_source, NULL);
  glCompileShader(vert_shader);

  // check errors
  glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vert_shader, 512, NULL, infolog);
    std::cout << "ERROR compiling Vertex Shader: " << infolog << '\n';
  }

  frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &frag_source, NULL);
  glCompileShader(frag_shader);

  // check errors
  glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(frag_shader, 512, NULL, infolog);
    std::cout << "ERROR compiling Fragment Shader: " << infolog << '\n';
  }
}

void link_shaders() {
  int success;
  char infolog[512];

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vert_shader);
  glAttachShader(shader_program, frag_shader);
  glLinkProgram(shader_program);

  // check errors
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, infolog);
    std::cout << "ERROR linking Shader Program" << infolog << '\n';
  }
  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);
}

void load_vertex_array() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // bind the Vertex Array Object first, then bind and set Vertex Buffers,
  // and the configure vertex attributes.
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally
  // modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally
  // don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void draw() {
  glUseProgram(shader_program);
  glBindVertexArray(VAO);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //glBindVertexArray(0); // no need to unbind it every time
}

void shader_exit() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shader_program);
}
