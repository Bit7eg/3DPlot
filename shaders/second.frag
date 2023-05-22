
}

float getAxisX() {
    float ty = -user_pos.y/ray_direction.y;
    float tz = -user_pos.z/ray_direction.z;
    if (isEquals(ty, tz)) {
        return ty;
    }
    return -1.0;
}

float getAxisY() {
    float tx = -user_pos.x/ray_direction.x;
    float tz = -user_pos.z/ray_direction.z;
    if (isEquals(tx, tz)) {
        return tx;
    }
    return -1.0;
}

float getAxisZ() {
    float ty = -user_pos.y/ray_direction.y;
    float tx = -user_pos.x/ray_direction.x;
    if (isEquals(ty, tx)) {
        return ty;
    }
    return -1.0;
}

mat4 rot(vec3 axis, float angle) {
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    return mat4(
        c + axis.x*axis.x*(1-c), axis.x*axis.y*(1-c)-axis.z*s, axis.x*axis.z*(1-c)+axis.y*s, 0,
        axis.x*axis.y*(1-c)+axis.z*s, c + axis.y*axis.y*(1-c), axis.y*axis.z*(1-c)-axis.x*s, 0,
        axis.x*axis.z*(1-c)-axis.y*s, axis.y*axis.z*(1-c)+axis.x*s, c + axis.z*axis.z*(1-c), 0,
        0, 0, 0, 1
    );
}

vec3 getRayPoint(float dist) {
    return user_pos + dist*ray_direction.xyz;
}

vec4 castRay() {
    vec4 color = mix(vec4(1.0), vec4(ray_direction.xyz, 1.0), 0.2);

    float closest_t = max_distance;

    float current_t = getAxisX();
    if (current_t > incr && current_t < closest_t) {
        closest_t = current_t;
        color = vec4(1.0, 0.0, 0.0, 1.0);
    }
    current_t = getAxisY();
    if (current_t > incr && current_t < closest_t) {
        closest_t = current_t;
        color = vec4(0.0, 1.0, 0.0, 1.0);
    }
    current_t = getAxisZ();
    if (current_t > incr && current_t < closest_t) {
        closest_t = current_t;
        color = vec4(0.0, 0.0, 1.0, 1.0);
    }

    for (float t = incr; t < closest_t; t += incr) {
        if (isFigure(getRayPoint(t))) {
            closest_t = t;
            color = mix(vec4(figure_color, 1.0), color, figure_transparency);
            break;
        }
    }

    return color;
}

void main() {
    vec2 uv = zoom*(frag_tex_coords - 0.5);
    ray_direction *= rot(cross(user_face, user_up), -uv.y);
    ray_direction *= rot(user_up, uv.x);
    res_color = castRay();
}