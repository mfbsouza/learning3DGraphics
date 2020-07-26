#include <window.h>

GLFWwindow *window;

void window_init(const char *title, const int width, const int height){
  if (!glfwInit()) exit(EXIT_FAILURE);
  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window){
    std::cout << "Failed Creating GLFW Window\n";
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  //glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(window, resize_callback);
  std::cout << "Window Created!\n";

  if(glewInit() != GLEW_OK) exit(EXIT_FAILURE);
  std::cout << "GLEW Initialized" << '\n';
}

void window_exit(){
  glfwDestroyWindow(window);
  glfwTerminate();
  std::cout << "Window Closed\n";
}

void check_opengl(){
  const GLubyte *gl_version = glGetString(GL_VERSION);
  std::cout << "OpenGL Graphics Driver: " << gl_version << '\n';
  const GLubyte *glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cout << "GL Shading Language Version: " << glsl_version << '\n';
}

void resize_callback(GLFWwindow *window, int width, int height){
  glViewport(0, 0, width, height);
}
