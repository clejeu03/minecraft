#version 330

in vec3 vFragPosition;
in vec3 vNormal;
in vec2 vTexCoords;

out vec3 fFragColor;

void main() {
    fFragColor = glm::vec3(10, 10, 10) * dot(normalize(-vFragPosition), normalize(vNormal)) / dot(vFragPosition, vFragPosition);
}


