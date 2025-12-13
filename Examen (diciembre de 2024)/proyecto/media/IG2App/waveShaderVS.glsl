#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform float time;
uniform vec2 center;
uniform mat4 modelViewProjMat;
out vec2 vUv0;

void main() {
    vUv0 = uv0;

    vec4 vertexCoord = vertex;
    float distanceCenter = distance(vec2(vertexCoord.x, vertexCoord.y), center);
    float amplitud = 60;
    float altura = 10;

    vertexCoord.y += sin(vertexCoord.x + (time * amplitud)) * altura; 

    gl_Position = modelViewProjMat * vertexCoord;
}