#version 330 core
out vec4 fragment_color;
in vec2 uv;

uniform sampler2D screenTex;
uniform sampler2D depTex;

void main() {
    fragment_color = vec4( texture(screenTex, uv).xyz ,1.0);
    gl_FragDepth = texture(depTex, uv).x;
}
