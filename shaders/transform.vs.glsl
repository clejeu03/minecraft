#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

uniform mat4 uMVPMatrix;
uniform int u2dMode = 0;
uniform int uLightening = 1;
/* Directional light */
uniform vec3 sunDirection;
uniform float sunAmbient;
uniform float sunIntensity;
/* Point light */
uniform float lightIntensity;
uniform vec3 lightPosition;

out vec3 vNormal;
out vec2 vTexCoords;
flat out int vEnlight;
out float vLightedPixel;

void main() {
	if( u2dMode == 0 ) {
		gl_Position = uMVPMatrix * vec4(position,1.);
	}
	else {
		gl_Position = vec4(position.x,position.y,0.,1.);
	}
	
	if( uLightening ) {
		float directional = sunIntensity*max(0.0, dot(normalize(normal), -sunDirection));
		float ambient = sunAmbient*sunIntensity;
		
		vLightedPixel = directional+ambient;	
	}
	
	vNormal = normal;
	vTexCoords = texCoords;
	vEnlight = uLightening;
}
