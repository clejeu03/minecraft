#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

uniform mat4 uMVPMatrix;

out vec3 vNormal;
out vec2 vTexCoords;

void main() {
	gl_Position = uMVPMatrix * vec4(position,1.);
	vNormal = normal;
	vTexCoords = texCoords;
}
