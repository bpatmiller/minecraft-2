#version 330 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 offset_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;

void main() {
    uv = vec2( vertex_position.x, vertex_position.z );
	gl_Position = projection * view * model * vec4(vertex_position + offset_position, 1.0);
}
