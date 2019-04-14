R"zzz(#version 330 core
uniform mat4 bone_transform; // transform the cylinder to the correct configuration
uniform mat4 bone_orientation;
const float kPi = 3.1415926535897932384626433832795;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
in vec4 vertex_position;
uniform float bone_length;
const float cyl_rad = 0.25;

// FIXME: Implement your vertex shader for cylinders
// Note: you need call sin/cos to transform the input mesh to a cylinder
void main() {
	mat4 mvp = projection * view * model;
	gl_Position = mvp * bone_transform * bone_orientation *
                            vec4(cyl_rad * cos(2.0 * kPi * vertex_position.x),
                             bone_length * vertex_position.y,
                             cyl_rad * sin(2.0 * kPi * vertex_position.x),
                             1.);
}
)zzz"
