#include <minecraft/ShapeManager.hpp>
#include <string>

namespace minecraft {
	Shape::~Shape() {
		delete vertices;
	}
	
	size_t Shape::GetByteSize() {
		return vertices[0].GetByteSize()*nbVertices;
	}
	
	// Init the common shapes
	ShapeManager::ShapeManager() {
		// Cube
		m_shapes[(char*)"cube"] = Shape(36);
		m_shapes[(char*)"cube"].vertices[0] = Vertex(-0.5,-0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[1] = Vertex(-0.5,-0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[2] = Vertex(-0.5, 0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[3] = Vertex(0.5, 0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[4] = Vertex(-0.5,-0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[5] = Vertex(-0.5, 0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[6] = Vertex(0.5,-0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[7] = Vertex(-0.5,-0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[8] = Vertex(0.5,-0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[9] = Vertex(0.5, 0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[10] = Vertex(0.5,-0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[11] = Vertex(-0.5,-0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[12] = Vertex(-0.5,-0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[13] = Vertex(-0.5, 0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[14] = Vertex(-0.5, 0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[15] = Vertex(0.5,-0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[16] = Vertex(-0.5,-0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[17] = Vertex(-0.5,-0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[18] = Vertex(-0.5, 0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[19] = Vertex(-0.5,-0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[20] = Vertex(0.5,-0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[21] = Vertex(0.5, 0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[22] = Vertex(0.5,-0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[23] = Vertex(0.5, 0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[24] = Vertex(0.5,-0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[25] = Vertex(0.5, 0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[26] = Vertex(0.5,-0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[27] = Vertex(0.5, 0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[28] = Vertex(0.5, 0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[29] = Vertex(-0.5, 0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[30] = Vertex(0.5, 0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[31] = Vertex(-0.5, 0.5,-0.5);
		m_shapes[(char*)"cube"].vertices[32] = Vertex(-0.5, 0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[33] = Vertex(0.5, 0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[34] = Vertex(-0.5, 0.5, 0.5);
		m_shapes[(char*)"cube"].vertices[35] = Vertex(0.5,-0.5, 0.5);
	}
	
	ShapeManager::~ShapeManager() {
		typedef std::map<GLuint,GLuint>::iterator ItType;
		for(ItType iterator = m_VAOVBOs.begin(); iterator != m_VAOVBOs.end(); iterator++) {
			// Delete VBO
			glDeleteBuffers(1,&(iterator->second));
			// Delete VAO
			glDeleteVertexArrays(1,&(iterator->first));
		}
	}
	
	void ShapeManager::LoadShapes() {
		typedef std::map<char*,Shape>::iterator ItType;
		for(ItType iterator = m_shapes.begin(); iterator != m_shapes.end(); iterator++) {
			LoadShape(iterator->first,iterator->second);
		}
	}
	
	void ShapeManager::LoadShape(char* shapeName, Shape shape) {
		// Gen VBO
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, shape.GetByteSize(), shape.vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Gen VAO
		GLuint vao;
		glGenVertexArrays(1,&vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer(0,
				Vertex::GetPositionNumComponents(),
				Vertex::GetDataType(),
				GL_FALSE,
				Vertex::GetByteSize(),
				Vertex::GetPositionOffset());
			glVertexAttribPointer(1,
				Vertex::GetNormalNumComponents(),
				Vertex::GetDataType(),
				GL_FALSE,
				Vertex::GetByteSize(),
				Vertex::GetNormalOffset());
			glVertexAttribPointer(2,
				Vertex::GetTextureNumComponents(),
				Vertex::GetDataType(),
				GL_FALSE,
				Vertex::GetByteSize(),
				Vertex::GetTextureOffset());
		glBindBuffer(GL_ARRAY_BUFFER,0);	
		glBindVertexArray(0);
		
		// Deleting the old shape for this game object
		if( m_shapeVAOs.find(shapeName) != m_shapeVAOs.end() ) {
			GLuint oldVao = m_shapeVAOs[shapeName];
			// Delete VBO
			glDeleteBuffers(1,&(m_VAOVBOs[oldVao]));
			// Delete VAO
			glDeleteVertexArrays(1,&oldVao);
		}
		
		// Save the vao and vbo
		m_shapeVAOs[shapeName] = vao;
		m_VAOVBOs[vao] = vbo;
	}
	
	GLuint ShapeManager::GetShapeVAO(char* shape) throw(std::invalid_argument) {
		if( m_shapeVAOs.find(shape) == m_shapeVAOs.end() )
			throw std::invalid_argument(std::string("No texture for ") + shape);
			
		return m_shapeVAOs[shape];
	}
}
