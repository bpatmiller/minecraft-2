#version 330 core
out vec4 fragment_color;
in vec3 cube_position;
void main() {
    float dark = cube_position.y;

    fragment_color = dark * vec4(0.1,0.3,0.7,1.0);
}
