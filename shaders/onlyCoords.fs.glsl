#version 330

in vec3 vNormal;
in vec2 vTexCoords;
flat in int vEnlight;

uniform sampler2D uTexture;

out vec4 fFragColor;

uniform vec3 sunColor; 
uniform vec3 sunDirection; 
uniform float sunAmbient; 

void main() {
	vec4 vTexColor = texture(uTexture, vTexCoords);
	if( vEnlight == 1 ) {
		float diffuseIntensity = max(0.0, dot(normalize(vNormal), -sunDirection)); 
		vec4 lightedPixel = vTexColor*(diffuseIntensity+sunAmbient);
		fFragColor = vec4(lightedPixel.x,lightedPixel.y,lightedPixel.z,vTexColor.w);
	}
	else
		fFragColor = vTexColor;
}
