#version 330 core
in vec3 vNormals;
in vec2 vUv0;

uniform sampler2D corrosionTex;
uniform float flipping;

uniform vec3 lightDiffuse; 
uniform vec4 lightPosition; 

uniform vec3 materialDiffuse; 

out vec4 fFragColor;

void main(){

    bool side;
    if(flipping > -1) {
        side = gl_FrontFacing;
    }
    else {
        side = !gl_FrontFacing;
    } 

    vec3 ambient = vLightAmbient * vMaterialDiffuse;
    float diff;
    vec3 color = texture(corrosionTex, vUv0).rgb;
    if (color.r > 0.6) {
        discard;
    }

    if (side) {
        diff = max(0, dot(vNormal, -vLightDirection));
        diffuse = diff * LightDiffuse.xyz * MaterialDiffuse;
        color = diffuse * color;
    }
    else {
        diff = max(0, dot(-vNormal, -vLightDirection));
        diffuse = diff * LightDiffuse.xyz * MaterialDiffuse;
        color = diffuse * color;
    }

    fFragColor = vec4(color, 1.0);
}