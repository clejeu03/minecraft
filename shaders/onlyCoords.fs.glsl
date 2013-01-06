#version 330

in vec3 vNormal;
in vec2 vTexCoords;

uniform sampler2D uTexture;

out vec4 fFragColor;

void main() {
    fFragColor = texture(uTexture, vTexCoords);
}

