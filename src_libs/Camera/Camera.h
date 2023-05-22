#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    GLfloat _yaw;
    GLfloat _pitch;
    GLfloat _speed;
    GLfloat _sensitivity;
    GLfloat _zoom;
    GLfloat _zoom_speed;

    void updateCameraVectors();
public:
    enum Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    Camera();

    glm::vec3 position();
    Camera& position(glm::vec3 pos);

    glm::vec3 front();
    glm::vec3 up();
    glm::vec3 right();

    GLfloat yaw();
    Camera& yaw(GLfloat angle);

    GLfloat pitch();
    Camera& pitch(GLfloat angle);

    GLfloat speed();
    Camera& speed(GLfloat val);

    GLfloat sensitivity();
    Camera& sensitivity(GLfloat val);

    GLfloat zoom();
    Camera& zoom(GLfloat angle);

    GLfloat zoom_speed();
    Camera& zoom_speed(GLfloat val);

    glm::mat4 view_matrix();

    Camera& move(Camera::Direction direction, GLfloat delta_time);
    Camera& rotate(GLfloat h_angle, GLfloat v_angle);
    Camera& changeZoom(GLfloat angle_offset);
};