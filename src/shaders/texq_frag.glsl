#version 330 core
out vec4 fragment_color;
in vec2 uv;

uniform sampler2D screenTex;
uniform sampler2D depTex;
uniform int loopy;

void main() {
    if (loopy == 1) {
        fragment_color = vec4( texture(screenTex, uv + sin(gl_FragCoord.x / 100) / 40).xyz ,1.0);
        fragment_color += vec4(0.4,0.0,0.4,0.0);
    } else {
        fragment_color = vec4( texture(screenTex, uv).xyz ,1.0);
    }

    gl_FragDepth = texture(depTex, uv).x;
}
