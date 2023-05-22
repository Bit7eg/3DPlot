#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class Shader {
private:
    GLuint programID;
public:
    Shader(const char* figure_name);
    ~Shader();
    void use() const;
    
    void setUniform(const char* name, GLdouble v0) const;
    void setUniform(const char* name, GLdouble v0, GLdouble v1) const;
    void setUniform(const char* name, GLdouble v0, GLdouble v1, GLdouble v2) const;
    void setUniform(const char* name, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) const;
    void setUniform(const char* name, GLfloat v0) const;
    void setUniform(const char* name, GLfloat v0, GLfloat v1) const;
    void setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2) const;
    void setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
    void setUniform(const char* name, GLint v0) const;
    void setUniform(const char* name, GLint v0, GLint v1) const;
    void setUniform(const char* name, GLint v0, GLint v1, GLint v2) const;
    void setUniform(const char* name, GLint v0, GLint v1, GLint v2, GLint v3) const;
    void setUniform(const char* name, GLuint v0) const;
    void setUniform(const char* name, GLuint v0, GLuint v1) const;
    void setUniform(const char* name, GLuint v0, GLuint v1, GLuint v2) const;
    void setUniform(const char* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const;
    void setUniform(const char* name, GLsizei cols, GLsizei rows, GLboolean transpose, const GLfloat *values) const;
    void setUniform(const char* name, GLsizei cols, GLsizei rows, GLboolean transpose, const GLdouble *values) const;
};
