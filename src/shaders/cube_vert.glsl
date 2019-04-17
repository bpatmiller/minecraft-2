#version 330 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec4 offset_position;

out vec2 uv;
out float block_type;

void main() {
	block_type = offset_position[3];
	uv = vec2( vertex_position.x, vertex_position.y );
	gl_Position = vec4(vertex_position + offset_position.xyz, 1.0);
}
