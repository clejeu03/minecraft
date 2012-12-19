#version 330

in vec2 vTexCoords;

out vec4 fFragColor;

uniform sampler2D uEarthSampler;
uniform sampler2D uCloudSampler;
uniform sampler2D uNightSampler;

void main() {
	fFragColor = mix((0.5 * texture(uEarthSampler, vTexCoords) +	0.5 * texture(uCloudSampler, vTexCoords)), texture(uNightSampler, vTexCoords), sin(3.14 * vTexCoords.x));
}
