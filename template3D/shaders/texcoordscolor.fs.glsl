#version 330

in vec3 vNormal;
in vec2 vTexCoords;

out vec3 fFragColor;

void main() {
    fFragColor = vec3(vTexCoords, 0.f);
}
