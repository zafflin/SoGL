# version 400 core

layout (location=0) in vec3 vPos;
layout (location=1) in vec3 vColor;
layout (location=2) in vec2 vTexCoord;

out vec2 texCoord;
out vec3 vertColor;

void main() {
    gl_Position = vec4(vPos.xyz, 1.0);
    texCoord = vec2(vTexCoord.xy);
    vertColor = vColor;
}