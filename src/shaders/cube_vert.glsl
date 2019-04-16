#version 330 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 offset_position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	gl_Position = model * vec4(vertex_position + offset_position, 1.0);
}
