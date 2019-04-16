#version 330 core
out vec4 fragment_color;
uniform float col;
void main() {
    fragment_color = vec4(col, 0.7, 1.0, 1.0);
}