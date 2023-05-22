#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <sstream>
#include <exception>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src_libs/libs.h"

int window_width, window_height;

bool key_states[1024];

GLfloat last_frame_time = 0.0f;
GLfloat delta_time = 0.0f;
GLfloat last_mouse_x, last_mouse_y;

Camera camera;
Config options("config.txt");

void errorCallback(int error, const char* description) {
    std::cout<<description<<"\n";
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        key_states[key] = true;
        if (key == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(window, true);
        }
    } else if (action == GLFW_RELEASE) {
        key_states[key] = false;
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    GLfloat x_offset = (xpos - last_mouse_x)/window_width;
    GLfloat y_offset = (last_mouse_y - ypos)/window_height;
    last_mouse_x = xpos;
    last_mouse_y = ypos;

    camera.rotate(x_offset, y_offset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.changeZoom(yoffset);
}

void doMovement() {
    if (key_states[GLFW_KEY_W]) {
        camera.move(Camera::FORWARD, delta_time);
    }
    if (key_states[GLFW_KEY_A]) {
        camera.move(Camera::LEFT, delta_time);
    }
    if (key_states[GLFW_KEY_S]) {
        camera.move(Camera::BACKWARD, delta_time);
    }
    if (key_states[GLFW_KEY_D]) {
        camera.move(Camera::RIGHT, delta_time);
    }
    if (key_states[GLFW_KEY_LEFT_SHIFT]) {
        camera.move(Camera::UP, delta_time);
    }
    if (key_states[GLFW_KEY_LEFT_CONTROL]) {
        camera.move(Camera::DOWN, delta_time);
    }
}

int main() {
    int buffi[2];
    float bufff[3];

    if (!glfwInit()) {
        std::cout<<"Failed to initialize GLFW\n";
        return -1;
    }

    glfwSetErrorCallback(errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    try {
        buffi[0] = stoi(options["WIDTH"]);
    } catch(const std::invalid_argument& e) {
        buffi[0] = 800;
    }
    if (buffi[0] <= 0) buffi[0] = 800;

    try {
        buffi[1] = stoi(options["HIEGHT"]);
    } catch(const std::invalid_argument& e) {
        buffi[1] = 600;
    }
    if (buffi[1] <= 0) buffi[1] = 600;

    GLFWwindow* window = glfwCreateWindow(buffi[0], buffi[1], "Plot3D", nullptr, nullptr);
    if (nullptr == window) {
        std::cout<<"Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum glew_status = glewInit();
    if (GLEW_OK != glew_status) {
        std::cout << "Failed to initialize GLEW\n" << glewGetErrorString(glew_status) << "\n";
        glfwTerminate();
        return -1;
    }

    glfwGetFramebufferSize(window, &window_width, &window_height);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glViewport(0, 0, window_width, window_height);

    last_mouse_x = window_width/2;
    last_mouse_y = window_height/2;
    glfwSetCursorPos(window, last_mouse_x, last_mouse_y);

    glEnable(GL_DEPTH_TEST);

    GLfloat screen[] = {
        -1.0f,  1.0f,   0.0f, 1.0f,
         1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f,   1.0f, 0.0f
    };
    GLuint indexes[] = {
        0, 1, 2,
        1, 2, 3
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screen), screen, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::string figure = options["FIGURE"];
    if (figure != "") figure = figure.erase(0, 1);
    Shader shader(figure.c_str());

    std::stringstream pos_option(options["CAMERA_POSITION"]);
    if (pos_option>>bufff[0]>>bufff[1]>>bufff[2])
    {
        camera.position(glm::vec3(bufff[0], bufff[1], bufff[2]));
    }

    try {
        bufff[0] = std::stof(options["HORIZONTAL_CAMERA_ROTATION"]);
    } catch(const std::invalid_argument& e) {
        bufff[0] = -(float)M_PI_2;
    }
    camera.yaw(bufff[0]);

    try {
        bufff[0] = std::stof(options["VERTICAL_CAMERA_ROTATION"]);
    } catch(const std::invalid_argument& e) {
        bufff[0] = 0.0f;
    }
    camera.pitch(bufff[0]);

    try {
        bufff[0] = std::stof(options["CAMERA_MOVING_SPEED"]);
    } catch(const std::invalid_argument& e) {
        bufff[0] = 5.0f;
    }
    camera.speed(bufff[0]);

    try {
        bufff[0] = std::stof(options["MOUSE_SENSITIVITY"]);
    } catch(const std::invalid_argument& e) {
        bufff[0] = 2.0f;
    }
    camera.sensitivity(bufff[0]);

    try {
        bufff[0] = std::stof(options["VIEWING_ANGLE"]);
    } catch(const std::invalid_argument& e) {
        bufff[0] = (float)M_PI_4;
    }
    camera.zoom(bufff[0]);

    try {
        bufff[0] = std::stof(options["ZOOM_SPEED"]);
    } catch(const std::invalid_argument& e) {
        bufff[0] = 0.1f;
    }
    camera.zoom_speed(bufff[0]);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window_width, window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        doMovement();

        delta_time = glfwGetTime() - last_frame_time;
        last_frame_time += delta_time;

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.use();
        glm::vec3 cam_param = camera.position();
        shader.setUniform("user_pos", cam_param.x, cam_param.y, cam_param.z);
        cam_param = camera.front();
        shader.setUniform("user_face", cam_param.x, cam_param.y, cam_param.z);
        cam_param = camera.up();
        shader.setUniform("user_up", cam_param.x, cam_param.y, cam_param.z);
        shader.setUniform("zoom", camera.zoom());
        std::stringstream color(options["FIGURE_COLOR"]);
        if (!(color>>bufff[0]) || (bufff[0] > 1.0f || bufff[0] < 0.0f)) bufff[0] = 0.5f;
        if (!(color>>bufff[1]) || (bufff[1] > 1.0f || bufff[1] < 0.0f)) bufff[1] = 0.5f;
        if (!(color>>bufff[2]) || (bufff[2] > 1.0f || bufff[2] < 0.0f)) bufff[2] = 0.5f;
        shader.setUniform("figure_color", bufff[0], bufff[1], bufff[2]);

        try {
            bufff[0] = std::stof(options["STEP_SIZE"]);
        } catch(const std::invalid_argument& e) {
            bufff[0] = 0.01f;
        }
        if (bufff[0] <= 0.0f) bufff[0] = 0.01f;
        shader.setUniform("incr", bufff[0]);

        try {
            bufff[0] = std::stof(options["VIEW_DISTANCE"]);
        } catch(const std::invalid_argument& e) {
            bufff[0] = 10.0f;
        }
        if (bufff[0] <= 0.0f) bufff[0] = 10.0f;
        shader.setUniform("max_distance", bufff[0]);

        try {
            bufff[0] = std::stof(options["FIGURE_TRANSPARENCY"]);
        } catch(const std::invalid_argument& e) {
            bufff[0] = 0.5f;
        }
        if (bufff[0] < 0.0f || bufff[0] > 1.0f) bufff[0] = 0.5f;
        shader.setUniform("figure_transparency", bufff[0]);
        // TODO: тесты

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
