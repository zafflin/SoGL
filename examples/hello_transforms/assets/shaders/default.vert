// SoGL default.vert

# version 400 core

layout (location=0) in vec3 vPos;
layout (location=1) in vec2 vTexCoord;

out vec2 texCoord;

void main() {
    gl_Position = vec4(vPos, 1.0);
    texCoord = vec2(vTexCoord);
}