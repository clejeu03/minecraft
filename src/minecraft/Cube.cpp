#include <minecraft/Cube.hpp>
#include <iostream>

namespace minecraft {
	float Cube::m_size = 0.1;
	GLuint Cube::m_texture = 0;
	
	GLuint CloudCube::m_texture = 0;
	GLuint RockCube::m_texture = 0;
	GLuint CrystalCube::m_texture = 0;
	
	void Cube::Draw() const {
		std::cout << "Draw cube with texture : " << GetTexId() << std::endl;
	}
}
