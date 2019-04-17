#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec2[] uv;
in float[] block_type;

out float top;
out vec3 normal;
out vec3 world_position;
out float bt;

void main()
{
    vec3 A = gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz;
    vec3 B = gl_in[0].gl_Position.xyz - gl_in[2].gl_Position.xyz;
	
	normal = normalize(cross(A, B));

	for (int n = 0; n < gl_in.length(); n++) {
        bt = block_type[n];
		top = uv[n].y;
		world_position = gl_in[n].gl_Position.xyz;

        gl_Position = projection * view * model * gl_in[n].gl_Position;

		EmitVertex();
	}
	EndPrimitive();
}