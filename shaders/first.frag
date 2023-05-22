#version 460 core

uniform sampler2D screen_texture;
uniform vec3 user_pos;
uniform vec3 user_face;
uniform vec3 user_up;
uniform vec3 figure_color;
uniform float zoom;
uniform float incr;
uniform float max_distance;
uniform float figure_transparency;

in vec2 frag_tex_coords;

out vec4 res_color;

vec4 ray_direction = vec4(user_face, 0.0);
float eps = 10*incr;

bool isEquals(float a, float b) {
    return (a > b - eps)&&(a < b + eps);
}

bool isFigure(vec3 point) {
