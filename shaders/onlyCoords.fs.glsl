#version 330

in vec3 vNormal;
in vec2 vTexCoords;
flat in int vEnlight;
in float vLightedPixel;

uniform sampler2D uTexture;

out vec4 fFragColor;

void main() {
	vec4 vTexColor = texture(uTexture, vTexCoords);
	if( vEnlight == 1 ) {
		vec4 vTexColor = texture(uTexture, vTexCoords);
		vec4 prePixel = vTexColor*(lightedPixel);
		fFragColor = vec4(prePixel.x,prePixel.y,prePixel.z,vTexColor.w);
	}
	else
		fFragColor = vTexColor;
}

