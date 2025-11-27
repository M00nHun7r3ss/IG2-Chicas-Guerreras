#version 330 core
in vec4 vertex; 
in vec3 normal;
in vec2 uv0; 

uniform mat4 modelViewMat; 
uniform mat4 modelViewProjMat; 
uniform mat4 normalMat;

uniform vec3 lightAmbient; 
uniform vec3 lightDiffuse; 
uniform vec4 lightPosition; 

uniform vec3 materialDiffuse; 

out vec2 vUv0; 
out vec3 vFrontColor;
out vec3 vBackColor;

void main() {
    vUv0 = uv0;
    vec4 vertexCoord = vertex;
    gl_Position = modelViewProjMat * vertexCoord;
}