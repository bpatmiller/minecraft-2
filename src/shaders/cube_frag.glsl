#version 330 core
out vec4 fragment_color;

in vec3 vert_color;

void main() {
    fragment_color = vec4(vert_color, 1.0);
}