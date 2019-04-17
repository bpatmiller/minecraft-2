#version 330 core
out vec4 fragment_color;
in vec3 cube_position;
void main() {
    float x = cube_position.x;
    float y = cube_position.y;
    float z = cube_position.z;

    float h = y * sqrt(1 - (z * z / 2) - (x * x / 2) + (x * x * z * z / 3));

    fragment_color = (0.5 + 0.5 * h) * vec4(0.1,0.3,0.7,1.0);

    if (h > 0.8) {
        fragment_color += (h - 0.8) * 5 * vec4(0.2,0.2,0.1,0.0);
    }
}
