#version 330

in vec3 vNormal;
in vec2 vTexCoords;
in float lightedPixel;

uniform sampler2D uTexture;

out vec4 fFragColor;

uniform vec3 sunColor; 
uniform vec3 sunDirection; 
uniform float sunAmbient; 

void main() {
	vec4 vTexColor = texture(uTexture, vTexCoords);
	vec4 prePixel = vTexColor*(lightedPixel);
	fFragColor = vec4(prePixel.x,prePixel.y,prePixel.z,vTexColor.w);
}
