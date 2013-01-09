#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

uniform mat4 uMVPMatrix;
uniform int u2dMode = 0;
uniform vec3 sunDirection;

out vec3 vNormal;
out vec2 vTexCoords;
out int v2dMode;
out float lightBase;

void main() {
	if( u2dMode == 0 )
		gl_Position = uMVPMatrix * vec4(position,1.);
	else
		gl_Position = vec4(position.x,position.y,0.,1.);
	
	vNormal = normal;
	vTexCoords = texCoords;
	v2dMode = u2dMode;
	
	lightBase = max(0.0, dot(normalize(normal), -sunDirection));
}
