#version 330 core
out vec4 fragment_color;
uniform sampler2D screenTex;
uniform sampler2D depTex;
uniform vec3 screenRes;

in vec2 uv;

void main() {
    vec2 screenCoord = vec2(gl_FragCoord.x / screenRes.x, gl_FragCoord.y / screenRes.y);
        
    vec3 sampleColor = texture(screenTex, screenCoord).xyz;

    float depthSample = 2.0 * texture(depTex, screenCoord).x - 1.0;
    float zLinear = 2.0 * 0.1 * 200 / (200 + 0.1 - depthSample * (200 - 0.1));
    zLinear /= 10;

    vec3 waterColor = vec3(0.0,0.4,0.6);
    vec3 filteredColor = mix(sampleColor, waterColor, zLinear);

    

    fragment_color = vec4(filteredColor, 1);

}
