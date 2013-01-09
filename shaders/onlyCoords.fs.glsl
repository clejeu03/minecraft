#version 330

in vec3 vNormal;
in vec2 vTexCoords;

uniform sampler2D uTexture;

out vec4 fFragColor;

uniform vec3 sunColor; 
uniform vec3 sunDirection; 
uniform float sunAmbient; 

void main() {
	vec4 vTexColor = texture(uTexture, vTexCoords);
	float diffuseIntensity = max(0.0, dot(normalize(vNormal), -sunDirection)); 
	fFragColor = vTexColor*(diffuseIntensity+sunAmbient);
}
