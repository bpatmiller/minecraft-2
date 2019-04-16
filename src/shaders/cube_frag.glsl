#version 330 core
out vec4 fragment_color;

uniform vec3 light_position;

in float top;
in vec3 normal;
in vec3 world_position;

void main() {
    vec3 col = vec3(0.4392, 0.2824, 0.2353) * 1.0;
    if (top > 0.9) {
      col = vec3(0.3, 0.7, 0.4);
    }

    vec3 L = normalize(light_position - world_position);
    float kd = 0.5 + 0.5 * dot(L, normal);

    fragment_color = vec4(kd * col, 1.0);
}