#version 330

in vec3 vNormal;
in vec2 vTexCoords;

uniform sampler2D uTexture;

out vec4 fFragColor;

uniform vec3 sunDirection; 
uniform float sunAmbient; 
uniform float sunIntensity; 

void main() {
	vec4 vTexColor = texture(uTexture, vTexCoords);
	float diffuseIntensity = max(0.0, dot(normalize(vNormal), -sunDirection)); 
	vec4 lightedPixel = sunIntensity*vTexColor*(diffuseIntensity+sunAmbient);
	fFragColor = vec4(lightedPixel.x,lightedPixel.y,lightedPixel.z,vTexColor.w);
}
