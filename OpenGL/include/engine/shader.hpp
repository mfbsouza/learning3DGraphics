#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class Shader {
  public:
    // Shader Program ID
    unsigned int ID;

    // Constructor
    Shader (const char *vertexPath,
            const char *fragmentPath,
            const char *geometryPath = nullptr);

    // Use/activate Shader Program
    void use();

    // utility uniform functions
    void setBool  (const std::string &name, bool value) const;
    void setInt   (const std::string &name, int value) const;
    void setFloat (const std::string &name, float value) const;

  private:
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif
