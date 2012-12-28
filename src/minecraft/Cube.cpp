#include <minecraft/Cube.hpp>

namespace minecraft {	
	void Cube::Draw() const {
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_nbVertices);
		glBindVertexArray(0);
	}
}
