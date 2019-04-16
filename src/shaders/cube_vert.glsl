#version 330 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 offset_position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 vert_color;

void main() {
	vert_color = (vec3(1.0,1.0,1.0) + vertex_position) / 2.0;
	gl_Position = projection * view * model * vec4(vertex_position + offset_position, 1.0);

}
