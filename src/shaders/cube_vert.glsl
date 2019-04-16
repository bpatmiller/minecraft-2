#version 330 core
layout (location = 0) in vec3 vertex_position;
layout (location = 2) in vec3 offset_position;

void main() {
	gl_Position = vec4(vertex_position + offset_position, 1.0);

}
