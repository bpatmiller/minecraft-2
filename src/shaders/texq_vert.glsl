#version 330 core
in vec3 vertex_position;

out vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    uv = (vertex_position.xy + vec2(1,1)) / 2;
	gl_Position = vec4(vertex_position, 1.0);
}
