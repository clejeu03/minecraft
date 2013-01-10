#include <minecraft/Cube.hpp>
#include <iostream>

namespace minecraft {	
	void Cube::Draw() const {
		glBindTexture(GL_TEXTURE_2D,m_textureId);
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_nbVertices);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D,0);
	}
}
