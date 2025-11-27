#version 330 core
in vec3 vFrontColor;
in vec3 vBackColor; 

in vec2 vUv0;

uniform sampler2D corrosionTex;
uniform float flipping;

uniform vec3 lightAmbient; 
uniform vec3 lightDiffuse; 
uniform vec4 lightPosition; 

uniform vec3 materialDiffuse; 

out vec4 fFragColor;

void main(){

    bool side;
    if(flipping > 0) {
        side = gl_FrontFacing;
    }
    else {
        side = !gl_FrontFacing;
    } 

    vec3 color = texture(materialTex, vUv0).rgb;
    if (color.r > 0.6) {
        discard;
    }

    vec3 diffuse;
    float diff;

    if (side)
        color = vFrontColor * color;
        //diff = max(0, dot(vNormal, -vLightDirection));
        //diffuse = diff * LightDiffuse * MaterialDiffuse;
    else {
        color = vBackColor * color;
        //color = -vNormal;
        //diff = max(0, dot(-vNormal, -vLightDirection));
        //diffuse = diff * LightDiffuse * MaterialDiffuse;
    }

    //I = colorBase * colorLuz * max(N*L, 0)
    color = color * (ambient + diffuse);

    fFragColor = vec4(color, 1.0);
}