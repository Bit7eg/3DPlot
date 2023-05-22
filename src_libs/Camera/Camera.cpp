#include "Camera.h"

static const glm::vec3 POSITION(0.0f, 0.0f, 0.0f);
static const glm::vec3 FRONT(0.0f, 0.0f, -1.0f);
static const glm::vec3 UP(0.0f, 1.0f, 0.0f);
static const glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);
static const GLfloat YAW = -(float)M_PI_2;
static const GLfloat PITCH = 0.0f;
static const GLfloat SPEED = 5.0f;
static const GLfloat SENSITIVITY = 2.0f;
static const GLfloat ZOOM = (float)M_PI_4;
static const GLfloat ZOOM_SPEED = 0.1f;

void Camera::updateCameraVectors() {
    this->_front = glm::normalize(glm::vec3(
        std::cos(this->_yaw)*std::cos(this->_pitch),
        std::sin(this->_pitch),
        std::sin(this->_yaw)*std::cos(this->_pitch)
    ));
    this->_right = glm::normalize(glm::cross(this->_front, WORLD_UP));
    this->_up = glm::normalize(glm::cross(this->_front, this->_right));
}

Camera::Camera() {
    this->_position = POSITION;
    this->_yaw = YAW;
    this->_pitch = PITCH;
    this->_speed = SPEED;
    this->_sensitivity = SENSITIVITY;
    this->_zoom = ZOOM;
    this->_zoom_speed = ZOOM_SPEED;
    this->updateCameraVectors();
}

glm::vec3 Camera::position() {
    return this->_position;
}

Camera& Camera::position(glm::vec3 pos) {
    this->_position = pos;
    return *this;
}

glm::vec3 Camera::front() {
    return this->_front;
}

glm::vec3 Camera::up() {
    return this->_up;
}

glm::vec3 Camera::right() {
    return this->_right;
}

GLfloat Camera::yaw() {
    return this->_yaw;
}

Camera& Camera::yaw(GLfloat angle) {
    this->_yaw = angle;
    this->updateCameraVectors();
    return *this;
}

GLfloat Camera::pitch() {
    return this->_pitch;
}

Camera& Camera::pitch(GLfloat angle) {
    this->_pitch = angle;
    if (this->_pitch > (float)M_PI_2 - 0.01f) {
        this->_pitch = (float)M_PI_2 - 0.01f;
    } else if (this->_pitch < 0.01f - (float)M_PI_2) {
        this->_pitch = 0.01f - (float)M_PI_2;
    }
    this->updateCameraVectors();
    return *this;
}

GLfloat Camera::speed() {
    return this->_speed;
}

Camera& Camera::speed(GLfloat val) {
    if (val > 0)
    {
        this->_speed = val;
    }
    return *this;
}

GLfloat Camera::sensitivity() {
    return this->_sensitivity;
}

Camera& Camera::sensitivity(GLfloat val) {
    if (val > 0)
    {
        this->_sensitivity = val;
    }
    return *this;
}

GLfloat Camera::zoom() {
    return this->_zoom;
}

Camera& Camera::zoom(GLfloat angle) {
    this->_zoom = angle;
    if (this->_zoom > (float)M_PI_2) {
        this->_zoom = (float)M_PI_2;
    } else if (this->_zoom < 0.01f) {
        this->_pitch = 0.01f;
    }
    return *this;
}

GLfloat Camera::zoom_speed() {
    return this->_zoom_speed;
}

Camera& Camera::zoom_speed(GLfloat val) {
    if (val > 0)
    {
        this->_zoom_speed = val;
    }
    return *this;
}

glm::mat4 Camera::view_matrix() {
    return glm::lookAt(this->_position, this->_position + this->_front, this->_up);
}

Camera& Camera::move(Camera::Direction direction, GLfloat delta_time) {
    GLfloat velocity = this->_speed * delta_time;
    if (direction == FORWARD) {
        this->_position += glm::normalize(glm::vec3(this->_front.x, 0.0f, this->_front.z)) * velocity;
    } else if (direction == BACKWARD) {
        this->_position -= glm::normalize(glm::vec3(this->_front.x, 0.0f, this->_front.z)) * velocity;
    } else if (direction == LEFT) {
        this->_position -= this->_right * velocity;
    } else if (direction == RIGHT) {
        this->_position += this->_right * velocity;
    } else if (direction == UP) {
        this->_position += WORLD_UP * velocity;
    } else if (direction == DOWN) {
        this->_position -= WORLD_UP * velocity;
    }
    return *this;
}

Camera& Camera::rotate(GLfloat h_angle, GLfloat v_angle) {
    h_angle *= this->_sensitivity;
    v_angle *= this->_sensitivity;

    this->_yaw += h_angle;
    this->_pitch += v_angle;

    if (this->_pitch > (float)M_PI_2 - 0.01f) {
        this->_pitch = (float)M_PI_2 - 0.01f;
    } else if (this->_pitch < 0.01f - (float)M_PI_2) {
        this->_pitch = 0.01f - (float)M_PI_2;
    }

    this->updateCameraVectors();
    return *this;
}

Camera& Camera::changeZoom(GLfloat angle_offset) {
    this->_zoom -= angle_offset * this->_zoom_speed;
    if (this->_zoom > (float)M_PI_2) {
        this->_zoom = (float)M_PI_2;
    }
    if (this->_zoom < 0.01f) {
        this->_zoom = 0.01f;
    }
    return *this;
}