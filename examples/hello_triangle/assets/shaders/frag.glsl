#version 400 core

out vec4 fragColor;

in vec2 texCoord;
in vec3 vertColor;

uniform bool hasColor;
uniform bool hasTexture;

uniform sampler2D fTexture;

void main() {
    vec4 baseColor = hasColor ? vec4(vertColor, 1.0) : vec4(1.0);
    if (hasTexture) {
        fragColor = texture(fTexture, texCoord) * baseColor;
    } else {
        fragColor = baseColor;
    }
}
