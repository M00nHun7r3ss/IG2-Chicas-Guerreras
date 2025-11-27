#version 330 core
in vec4 vertex; 
in vec3 normal;
in vec2 uv0; 

uniform mat4 modelViewMat; 
uniform mat4 modelViewProjMat; 
uniform mat4 normalMat;

out vec2 vUv0; 
out vec3 vFrontColor;
out vec3 vBackColor;

void main() {
    vec3 ambient = lightAmbient * materialDiffuse;

    // Diffuse en view space (front)
    vec3 viewVertex = vec3(modelViewMat * vertex);
    vec3 viewNormal = normalize(normalMat * normal);
    vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;
    vFrontColor = ambient + diffuse;

    // Diffuse en view space (back)
    diffuse = diff(viewVertex, -viewNormal) * lightDiffuse * materialDiffuse;
    vBackColor = ambient + diffuse;

    vUv0 = uv0;
    gl_Position = modelViewProjMat * vertex;

    vUv0 = uv0;
    vec4 vertexCoord = vertex;
    gl_Position = modelViewProjMat * vertexCoord;

}