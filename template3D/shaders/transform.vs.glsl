#version 330

layout(location=0) in vec3 vPositionIn;
layout(location=1) in vec3 vNormalIn;
layout(location=2) in vec2 vTexCoordsIn;

out vec3 vNormal;
out vec2 vTexCoords;

uniform mat4 uMVPMatrix;

void main()
{
	gl_Position = uMVPMatrix*vec4(vPositionIn,1.f);
	
	vNormal = vNormalIn;
	vTexCoords = vTexCoordsIn;

}
