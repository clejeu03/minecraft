#version 330

in vec3 vNormal;
in vec2 vTexCoords;
in float lightBase;

uniform sampler2D uTexture;

out vec4 fFragColor;

uniform vec3 sunColor; 
uniform vec3 sunDirection; 
uniform float sunAmbient; 

void main() {
	vec4 vTexColor = texture(uTexture, vTexCoords);
	vec4 lightedPixel = vTexColor*(lightBase+sunAmbient);
	fFragColor = vec4(lightedPixel.x,lightedPixel.y,lightedPixel.z,vTexColor.w);
}
