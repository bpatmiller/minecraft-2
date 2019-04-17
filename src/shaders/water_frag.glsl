#version 330 core
out vec4 fragment_color;
uniform sampler2D screenTex;
uniform sampler2D depTex;
uniform vec3 screenRes;

in vec2 uv;

void main() {
    vec2 screenCoord = vec2(gl_FragCoord.x / screenRes.x, gl_FragCoord.y / screenRes.y);
        
    fragment_color = vec4(texture(screenTex, screenCoord).xyz, 1.0);
    fragment_color += vec4(0.0,0.3,0.4,0.0);
}
