// SoGl default.frag

#version 400 core

out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D fTexture;

void main() {
    vec4 baseColor = vec4(1.0);
    fragColor = texture(fTexture, texCoord) * baseColor;
}
