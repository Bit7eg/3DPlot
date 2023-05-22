#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

Shader::Shader(const char* figure_name) {
    std::string figurePath = "figures/" + std::string(figure_name);
    std::string fragmentCode;
    std::ifstream fragmentFile1, fragmentFile2, figureFile;

    try {
        fragmentFile1.open("shaders/first.frag");
        fragmentFile2.open("shaders/second.frag");
        figureFile.open(figurePath);
        std::stringstream fragmentStream;
        fragmentStream << fragmentFile1.rdbuf() << figureFile.rdbuf() << fragmentFile2.rdbuf();
        fragmentFile1.close();
        fragmentFile2.close();
        figureFile.close();
        fragmentCode = fragmentStream.str();
    } catch (std::ifstream::failure &e) {
        std::cerr << "Failed to read figure file\n" << e.what() << "\n";
    }

    const char *fragmentShader = fragmentCode.c_str();
    const char *vertexShader = "\
    #version 460 core\n\
    layout (location = 0) in vec2 position;\n\
    layout (location = 1) in vec2 vert_tex_coords;\n\
    out vec2 frag_tex_coords;\n\
    void main(){\n\
    gl_Position = vec4(position, 0.0, 1.0);\n\
    frag_tex_coords = vert_tex_coords;\n\
    }\
    ";
    GLuint vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShader, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr<<"Vertex shader compilation failed\n"<<infoLog<<"\n";
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShader, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr<<"Fragment shader compilation failed\n"<<infoLog<<"\n";
    }

    programID = glCreateProgram();
    
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr<<"Shader program compilation failed\n"<<infoLog<<"\n";
    }
}

Shader::~Shader() {
    glDeleteProgram(programID);
}

void Shader::use() const {
    glUseProgram(programID);
}

void Shader::setUniform(const char* name, GLdouble v0) const {
    glUniform1d(glGetUniformLocation(this->programID, name), v0);
}

void Shader::setUniform(const char* name, GLdouble v0, GLdouble v1) const {
    glUniform2d(glGetUniformLocation(this->programID, name), v0, v1);
}

void Shader::setUniform(const char* name, GLdouble v0, GLdouble v1, GLdouble v2) const {
    glUniform3d(glGetUniformLocation(this->programID, name), v0, v1, v2);
}

void Shader::setUniform(const char* name, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) const {
    glUniform4d(glGetUniformLocation(this->programID, name), v0, v1, v2, v3);
}

void Shader::setUniform(const char* name, GLfloat v0) const {
    glUniform1f(glGetUniformLocation(this->programID, name), v0);
}

void Shader::setUniform(const char* name, GLfloat v0, GLfloat v1) const {
    glUniform2f(glGetUniformLocation(this->programID, name), v0, v1);
}

void Shader::setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2) const {
    glUniform3f(glGetUniformLocation(this->programID, name), v0, v1, v2);
}

void Shader::setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
    glUniform4f(glGetUniformLocation(this->programID, name), v0, v1, v2, v3);
}

void Shader::setUniform(const char* name, GLint v0) const {
    glUniform1i(glGetUniformLocation(this->programID, name), v0);
}

void Shader::setUniform(const char* name, GLint v0, GLint v1) const {
    glUniform2i(glGetUniformLocation(this->programID, name), v0, v1);
}

void Shader::setUniform(const char* name, GLint v0, GLint v1, GLint v2) const {
    glUniform3i(glGetUniformLocation(this->programID, name), v0, v1, v2);
}

void Shader::setUniform(const char* name, GLint v0, GLint v1, GLint v2, GLint v3) const {
    glUniform4i(glGetUniformLocation(this->programID, name), v0, v1, v2, v3);
}

void Shader::setUniform(const char* name, GLuint v0) const {
    glUniform1ui(glGetUniformLocation(this->programID, name), v0);
}

void Shader::setUniform(const char* name, GLuint v0, GLuint v1) const {
    glUniform2ui(glGetUniformLocation(this->programID, name), v0, v1);
}

void Shader::setUniform(const char* name, GLuint v0, GLuint v1, GLuint v2) const {
    glUniform3ui(glGetUniformLocation(this->programID, name), v0, v1, v2);
}

void Shader::setUniform(const char* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const {
    glUniform4ui(glGetUniformLocation(this->programID, name), v0, v1, v2, v3);
}

void Shader::setUniform(const char* name, GLsizei cols, GLsizei rows, GLboolean transpose, const GLfloat *values) const {
    if (cols == 1 && rows == 1) {
        glUniform1fv(glGetUniformLocation(this->programID, name), 1, values);
    } else if ((cols == 1 && rows == 2) || (cols == 2 && rows == 1)) {
        glUniform2fv(glGetUniformLocation(this->programID, name), 1, values);
    } else if ((cols == 1 && rows == 3) || (cols == 3 && rows == 1)) {
        glUniform3fv(glGetUniformLocation(this->programID, name), 1, values);
    } else if ((cols == 1 && rows == 4) || (cols == 4 && rows == 1)) {
        glUniform4fv(glGetUniformLocation(this->programID, name), 1, values);
    } else if (cols == 2 && rows == 2) {
        glUniformMatrix2fv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 2 && rows == 3) {
        glUniformMatrix2x3fv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 2 && rows == 4) {
        glUniformMatrix2x4fv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 3 && rows == 2) {
        glUniformMatrix3x2fv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 3 && rows == 3) {
        glUniformMatrix3fv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 3 && rows == 4) {
        glUniformMatrix3x4fv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 4 && rows == 2) {
        glUniformMatrix4x2fv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 4 && rows == 3) {
        glUniformMatrix4x3fv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 4 && rows == 4) {
        glUniformMatrix4fv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    }
}

void Shader::setUniform(const char* name, GLsizei cols, GLsizei rows, GLboolean transpose, const GLdouble *values) const {
    if (cols == 1 && rows == 1) {
        glUniform1dv(glGetUniformLocation(this->programID, name), 1, values);
    } else if ((cols == 1 && rows == 2) || (cols == 2 && rows == 1)) {
        glUniform2dv(glGetUniformLocation(this->programID, name), 1, values);
    } else if ((cols == 1 && rows == 3) || (cols == 3 && rows == 1)) {
        glUniform3dv(glGetUniformLocation(this->programID, name), 1, values);
    } else if ((cols == 1 && rows == 4) || (cols == 4 && rows == 1)) {
        glUniform4dv(glGetUniformLocation(this->programID, name), 1, values);
    } else if (cols == 2 && rows == 2) {
        glUniformMatrix2dv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 2 && rows == 3) {
        glUniformMatrix2x3dv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 2 && rows == 4) {
        glUniformMatrix2x4dv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 3 && rows == 2) {
        glUniformMatrix3x2dv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 3 && rows == 3) {
        glUniformMatrix3dv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 3 && rows == 4) {
        glUniformMatrix3x4dv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 4 && rows == 2) {
        glUniformMatrix4x2dv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 4 && rows == 3) {
        glUniformMatrix4x3dv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    } else if (cols == 4 && rows == 4) {
        glUniformMatrix4dv(glGetUniformLocation(this->programID, name), 1, transpose, values);
    }
}
