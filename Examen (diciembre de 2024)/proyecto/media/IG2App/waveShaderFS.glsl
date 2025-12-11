#version 330 core
in vec2 vUv0;
uniform sampler2D waves;
out vec4 fFragColor;

void main() {
    vec4 color = texture(waves, vUv0);
    fFragColor = color;
}