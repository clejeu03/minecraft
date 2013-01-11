#include <minecraft/ShapeManager.hpp>
#include <minecraft/Map.hpp>
#include <string>
#include <vector>
#include <iostream> 
#include <typeinfo>

namespace minecraft {
	Shape::Shape(const Shape& s) {
		nbVertices = s.nbVertices;
		vertices = new Vertex[nbVertices];
		for( size_t i = 0; i < nbVertices; i++ ) {
			vertices[i] = s.vertices[i];
		}
	}
	
	Shape::~Shape() {
		delete[] vertices;
		vertices = NULL;
	}
	
	Shape& Shape::operator=(const Shape& s) {
		nbVertices = s.nbVertices;
		vertices = new Vertex[nbVertices];
		for( size_t i = 0; i < nbVertices; i++ ) {
			vertices[i] = s.vertices[i];
		}
		return *this;
	}
	
	size_t Shape::GetByteSize() {
		return sizeof(struct Vertex)*nbVertices;
	}
	
	// Init the common shapes
	ShapeManager::ShapeManager() {
		/// Cube
		m_shapes[std::string("Cube")] = Shape(36);
		m_shapes[std::string("CrystalCube")] = Shape(36);
		m_shapes[std::string("CloudCube")] = Shape(36);
		m_shapes[std::string("RockCube")] = Shape(36);
		m_shapes[std::string("GrassCube")] = Shape(36);
		m_shapes[std::string("DirtCube")] = Shape(36);
		m_shapes[std::string("DiamondCube")] = Shape(36);
		m_shapes[std::string("GoldCube")] = Shape(36);

		//Face gauche
		m_shapes[std::string("Cube")].vertices[0] = Vertex(-0.5,-0.5,-0.5, -1.0, 0.0, 0.0, 0.0, 1.0);
		m_shapes[std::string("Cube")].vertices[1] = Vertex(-0.5,-0.5, 0.5, -1.0, 0.0, 0.0, 1.0, 1.0);
		m_shapes[std::string("Cube")].vertices[2] = Vertex(-0.5, 0.5, 0.5, -1.0, 0.0, 0.0, 1.0, 0.0);

		//Face gauche
		m_shapes[std::string("Cube")].vertices[12] = Vertex(-0.5,-0.5,-0.5, -1.0, 0.0, 0.0, 0.0, 1.0);
		m_shapes[std::string("Cube")].vertices[13] = Vertex(-0.5, 0.5, 0.5, -1.0, 0.0, 0.0, 1.0, 0.0);
		m_shapes[std::string("Cube")].vertices[14] = Vertex(-0.5, 0.5,-0.5, -1.0, 0.0, 0.0, 0.0, 0.0);
		
		//Face derrière
		m_shapes[std::string("Cube")].vertices[3] = Vertex(0.5, 0.5,-0.5, 0.0, 0.0, -1.0, 0.0, 0.0);
		m_shapes[std::string("Cube")].vertices[4] = Vertex(-0.5,-0.5,-0.5, 0.0, 0.0, -1.0, 1.0, 1.0);
		m_shapes[std::string("Cube")].vertices[5] = Vertex(-0.5, 0.5,-0.5, 0.0, 0.0, -1.0, 1.0, 0.0);

		//Face derrière
		m_shapes[std::string("Cube")].vertices[9] = Vertex(0.5, 0.5,-0.5, 0.0, 0.0, -1.0, 0.0, 0.0);
		m_shapes[std::string("Cube")].vertices[10] = Vertex(0.5,-0.5,-0.5, 0.0, 0.0, -1.0, 0.0, 1.0);
		m_shapes[std::string("Cube")].vertices[11] = Vertex(-0.5,-0.5,-0.5, 0.0, 0.0, -1.0, 1.0, 1.0);
		
		//Face dessous
		m_shapes[std::string("Cube")].vertices[6] = Vertex(0.5,-0.5, 0.5, 0.0, -1.0, 0.0, 1.0, 0.0);
		m_shapes[std::string("Cube")].vertices[7] = Vertex(-0.5,-0.5,-0.5, 0.0, -1.0, 0.0, 0.0, 1.0);
		m_shapes[std::string("Cube")].vertices[8] = Vertex(0.5,-0.5,-0.5, 0.0, -1.0, 0.0, 1.0, 1.0);

		//Face dessous
		m_shapes[std::string("Cube")].vertices[15] = Vertex(0.5,-0.5, 0.5, 0.0, -1.0, 0.0, 1.0, 0.0);
		m_shapes[std::string("Cube")].vertices[16] = Vertex(-0.5,-0.5, 0.5, 0.0, -1.0, 0.0, 0.0, 0.0);
		m_shapes[std::string("Cube")].vertices[17] = Vertex(-0.5,-0.5,-0.5, 0.0, -1.0, 0.0, 0.0, 1.0);
		
		//Face avant
		m_shapes[std::string("Cube")].vertices[18] = Vertex(-0.5, 0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0);
		m_shapes[std::string("Cube")].vertices[19] = Vertex(-0.5,-0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 1.0);
		m_shapes[std::string("Cube")].vertices[20] = Vertex(0.5,-0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0);

		//Face avant
		m_shapes[std::string("Cube")].vertices[33] = Vertex(0.5, 0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 0.0);
		m_shapes[std::string("Cube")].vertices[34] = Vertex(-0.5, 0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0);
		m_shapes[std::string("Cube")].vertices[35] = Vertex(0.5,-0.5, 0.5,  0.0, 0.0, 1.0, 1.0, 1.0);
		
		//Face droite
		m_shapes[std::string("Cube")].vertices[21] = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0);
		m_shapes[std::string("Cube")].vertices[22] = Vertex(0.5,-0.5,-0.5, 1.0, 0.0, 0.0, 1.0, 1.0);
		m_shapes[std::string("Cube")].vertices[23] = Vertex(0.5, 0.5,-0.5, 1.0, 0.0, 0.0, 1.0, 0.0);

		//Face droite
		m_shapes[std::string("Cube")].vertices[24] = Vertex(0.5,-0.5,-0.5, 1.0, 0.0, 0.0, 1.0, 1.0);
		m_shapes[std::string("Cube")].vertices[25] = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0);
		m_shapes[std::string("Cube")].vertices[26] = Vertex(0.5,-0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0);

		//Face haut
		m_shapes[std::string("Cube")].vertices[27] = Vertex(0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 1.0, 1.0);
		m_shapes[std::string("Cube")].vertices[28] = Vertex(0.5, 0.5,-0.5, 0.0, 1.0, 0.0, 1.0, 0.0);
		m_shapes[std::string("Cube")].vertices[29] = Vertex(-0.5, 0.5,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0);

		//Face haut
		m_shapes[std::string("Cube")].vertices[30] = Vertex(0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 1.0, 1.0);
		m_shapes[std::string("Cube")].vertices[31] = Vertex(-0.5, 0.5,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0);
		m_shapes[std::string("Cube")].vertices[32] = Vertex(-0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0);
		

		///Cubes
		m_shapes[std::string("CrystalCube")] = m_shapes[std::string("Cube")];
		m_shapes[std::string("CloudCube")] = m_shapes[std::string("Cube")];
		m_shapes[std::string("RockCube")] = m_shapes[std::string("Cube")];
		m_shapes[std::string("GrassCube")] = m_shapes[std::string("Cube")];
		m_shapes[std::string("DirtCube")] = m_shapes[std::string("Cube")];
		m_shapes[std::string("DiamondCube")] = m_shapes[std::string("Cube")];
		m_shapes[std::string("GoldCube")] = m_shapes[std::string("Cube")];
		
		/// SkyBox
		m_shapes[std::string("SkyBox")] = Shape(36);

		//Face gauche
		m_shapes[std::string("SkyBox")].vertices[0] = Vertex(0.5,-0.5,-0.5, 1.0, 0.0, 0.0, 0.0, 2.0/3);
		m_shapes[std::string("SkyBox")].vertices[1] = Vertex(0.5,-0.5, 0.5, 1.0, 0.0, 0.0, 1./4, 2.0/3);
		m_shapes[std::string("SkyBox")].vertices[2] = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 1./4, 1.0/3);

		//Face gauche
		m_shapes[std::string("SkyBox")].vertices[12] = Vertex(0.5,-0.5,-0.5, 1.0, 0.0, 0.0, 0.0, 2.0/3);
		m_shapes[std::string("SkyBox")].vertices[13] = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 1./4, 1.0/3);
		m_shapes[std::string("SkyBox")].vertices[14] = Vertex(0.5, 0.5,-0.5, 1.0, 0.0, 0.0, 0.0, 1.0/3);
		
		//Face derrière
		m_shapes[std::string("SkyBox")].vertices[3] = Vertex(0.5, 0.5,0.5, 0.0, 0.0, 1.0, 1./4, 1.0/3);
		m_shapes[std::string("SkyBox")].vertices[4] = Vertex(-0.5,-0.5,0.5, 0.0, 0.0, 1.0, 1./2, 2.0/3);
		m_shapes[std::string("SkyBox")].vertices[5] = Vertex(-0.5, 0.5,0.5, 0.0, 0.0, 1.0, 1./2, 1.0/3);

		//Face derrière
		m_shapes[std::string("SkyBox")].vertices[9] = Vertex(0.5, 0.5,0.5, 0.0, 0.0, 1.0, 1./4, 1.0/3);
		m_shapes[std::string("SkyBox")].vertices[10] = Vertex(0.5,-0.5,0.5, 0.0, 0.0, 1.0, 1./4, 2.0/3);
		m_shapes[std::string("SkyBox")].vertices[11] = Vertex(-0.5,-0.5,0.5, 0.0, 0.0, 1.0, 1./2, 2.0/3);
		
		//Face dessous
		m_shapes[std::string("SkyBox")].vertices[6] = Vertex(-0.5,0.5, -0.5, 0.0, 1.0, 0.0, 1./2, 0.);
		m_shapes[std::string("SkyBox")].vertices[7] = Vertex(0.5,0.5,0.5, 0.0, 1.0, 0.0, 1./4, 1.0/3);
		m_shapes[std::string("SkyBox")].vertices[8] = Vertex(-0.5,0.5,0.5, 0.0, 1.0, 0.0, 2./4, 1.0/3);

		//Face dessous
		m_shapes[std::string("SkyBox")].vertices[15] = Vertex(-0.5,0.5, -0.5, 0.0, 1.0, 0.0, 1./2, 0.);
		m_shapes[std::string("SkyBox")].vertices[16] = Vertex(0.5,0.5, -0.5, 0.0, 1.0, 0.0, 1./4, 0.);
		m_shapes[std::string("SkyBox")].vertices[17] = Vertex(0.5,0.5,0.5, 0.0, 1.0, 0.0, 1./4, 1.0/3);
		
		//Face avant
		m_shapes[std::string("SkyBox")].vertices[18] = Vertex(-0.5, 0.5, -0.5, 0.0, 0.0, -1.0, 3./4, 1.0/3);
		m_shapes[std::string("SkyBox")].vertices[19] = Vertex(-0.5,-0.5, -0.5, 0.0, 0.0, -1.0, 3./4, 2.0/3);
		m_shapes[std::string("SkyBox")].vertices[20] = Vertex(0.5,-0.5, -0.5, 0.0, 0.0, -1.0, 1.0, 2.0/3);

		//Face avant
		m_shapes[std::string("SkyBox")].vertices[33] = Vertex(0.5, 0.5, -0.5, 0.0, 0.0, -1.0, 1.0, 1.0/3);
		m_shapes[std::string("SkyBox")].vertices[34] = Vertex(-0.5, 0.5, -0.5, 0.0, 0.0, -1.0, 3./4, 1.0/3);
		m_shapes[std::string("SkyBox")].vertices[35] = Vertex(0.5,-0.5, -0.5,  0.0, 0.0, -1.0, 1.0, 2.0/3);
		
		//Face droite
		m_shapes[std::string("SkyBox")].vertices[21] = Vertex(-0.5, 0.5, 0.5, -1.0, 0.0, 0.0, 1./2, 1.0/3);
		m_shapes[std::string("SkyBox")].vertices[22] = Vertex(-0.5,-0.5,-0.5, -1.0, 0.0, 0.0, 3./4, 2.0/3);
		m_shapes[std::string("SkyBox")].vertices[23] = Vertex(-0.5, 0.5,-0.5, -1.0, 0.0, 0.0, 3./4, 1.0/3);

		//Face droite
		m_shapes[std::string("SkyBox")].vertices[24] = Vertex(-0.5,-0.5,-0.5, -1.0, 0.0, 0.0, 3./4, 2.0/3);
		m_shapes[std::string("SkyBox")].vertices[25] = Vertex(-0.5, 0.5, 0.5, -1.0, 0.0, 0.0, 1./2, 1.0/3);
		m_shapes[std::string("SkyBox")].vertices[26] = Vertex(-0.5,-0.5, 0.5, -1.0, 0.0, 0.0, 1./2, 2.0/3);

		//Face haut
		m_shapes[std::string("SkyBox")].vertices[27] = Vertex(0.5, -0.5, 0.5, 0.0, -1.0, 0.0, 1./4, 1.0);
		m_shapes[std::string("SkyBox")].vertices[28] = Vertex(0.5, -0.5,-0.5, 0.0, -1.0, 0.0, 1./4, 2./3);
		m_shapes[std::string("SkyBox")].vertices[29] = Vertex(-0.5, -0.5,-0.5, 0.0, -1.0, 0.0, 1./2, 2./3);

		//Face haut
		m_shapes[std::string("SkyBox")].vertices[30] = Vertex(0.5, -0.5, 0.5, 0.0, -1.0, 0.0, 1./4, 1.0);
		m_shapes[std::string("SkyBox")].vertices[31] = Vertex(-0.5, -0.5,-0.5, 0.0, -1.0, 0.0, 1./2, 2./3);
		m_shapes[std::string("SkyBox")].vertices[32] = Vertex(-0.5, -0.5, 0.5, 0.0, -1.0, 0.0, 1./2, 1.0);
		
		/// Cursor
		m_shapes[std::string("Cursor")] = Shape(6);
		
		m_shapes[std::string("Cursor")].vertices[0] = Vertex(-0.05,0.05,0,0,0,0,0,1.);
		m_shapes[std::string("Cursor")].vertices[1] = Vertex(0.05,0.05,0,0,0,0,1,1);
		m_shapes[std::string("Cursor")].vertices[2] = Vertex(-0.05,-0.05,0,0,0,0,0,0);
		m_shapes[std::string("Cursor")].vertices[3] = Vertex(-0.05,-0.05,0,0,0,0,0,0);
		m_shapes[std::string("Cursor")].vertices[4] = Vertex(0.05,-0.05,0,0,0,0,1,0);
		m_shapes[std::string("Cursor")].vertices[5] = Vertex(0.05,0.05,0,0,0,0,1,1);

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
	
	void ShapeManager::SetBuffer(const char* type) {
		GLuint vao = GetShapeVAO(type);
		GLuint vbo = m_VAOVBOs[vao];

		Shape shape = m_shapes[type];

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, shape.GetByteSize(), shape.vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

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
	}

	void ShapeManager::SetInstanciatedBuffer(const char* type, std::vector<MapCoords>& cubeCoords) {
		
		GLuint vao = GetShapeVAO(std::string(type));
		GLuint vbo = m_VAOVBOs[vao];

		size_t cubesCount = cubeCoords.size();
		
		int positionNumComponents = Vertex::GetPositionNumComponents();
		size_t shapeNbVertices = GetShapeNbVertices(std::string(type));
		int normalNumComponents = Vertex::GetNormalNumComponents();
		int textureNumComponents = Vertex::GetTextureNumComponents();

		GLfloat* positionCoords = new GLfloat[positionNumComponents * shapeNbVertices];
		GLfloat* normalsCoords = new GLfloat[normalNumComponents * shapeNbVertices];
		GLfloat* textCoords = new GLfloat[textureNumComponents * shapeNbVertices];

		size_t* instancePositions = new size_t[cubesCount * positionNumComponents];

		typedef std::map<MapCoords,Cube*>::const_iterator ItType;

		std::cout << "cubesCount = " << cubesCount << std::endl;
		for(size_t i = 0; i<cubesCount; ++i) {
			instancePositions[positionNumComponents*i] = std::get<0>(cubeCoords[i]);
			instancePositions[positionNumComponents*i+1] = std::get<1>(cubeCoords[i]);
			instancePositions[positionNumComponents*i+2] = std::get<2>(cubeCoords[i]);
			std::cout << "position[" << positionNumComponents*i << "] = " << std::get<0>(cubeCoords[i]) << std::endl; 
			std::cout << "position[" << positionNumComponents*i+1 << "] = " << std::get<1>(cubeCoords[i]) << std::endl; 
			std::cout << "position[" << positionNumComponents*i+2 << "] = " << std::get<2>(cubeCoords[i]) << std::endl; 
		}

		std::cout << "positionNumComponents = " << positionNumComponents << std::endl;
		
		Vertex* vertices = m_shapes[std::string(type)].vertices;

		for(size_t i=0; i<shapeNbVertices; ++i) {
			positionCoords[positionNumComponents*i] = vertices[i].position.x;
			positionCoords[positionNumComponents*i+1] = vertices[i].position.y;
			positionCoords[positionNumComponents*i+2] = vertices[i].position.z;

			normalsCoords[normalNumComponents*i] = vertices[i].normal.x;
			normalsCoords[normalNumComponents*i+1] = vertices[i].normal.y;
			normalsCoords[normalNumComponents*i+2] = vertices[i].normal.z;

			textCoords[textureNumComponents*i] = vertices[i].textureXY.x;
			textCoords[textureNumComponents*i+1] = vertices[i].textureXY.y;
		}


		size_t sizeofPositionCoords = positionNumComponents * shapeNbVertices * sizeof(GLfloat);
		size_t sizeofNormalsCoords = normalNumComponents * shapeNbVertices * sizeof(GLfloat);
		size_t sizeofTextCoords = textureNumComponents * shapeNbVertices * sizeof(GLfloat);
		size_t sizeofInstancePositions = cubesCount * positionNumComponents * sizeof(size_t);

	    glBindVertexArray(vao);
		    glBindBuffer(GL_ARRAY_BUFFER, vbo);
			    glBufferData(GL_ARRAY_BUFFER, sizeofPositionCoords + sizeofNormalsCoords + sizeofTextCoords + sizeofInstancePositions, NULL, GL_STATIC_DRAW);
			    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeofPositionCoords, positionCoords);
			    glBufferSubData(GL_ARRAY_BUFFER, sizeofPositionCoords, sizeofNormalsCoords, normalsCoords);
			    glBufferSubData(GL_ARRAY_BUFFER, sizeofPositionCoords + sizeofNormalsCoords, sizeofTextCoords, textCoords);
			    glBufferSubData(GL_ARRAY_BUFFER, sizeofPositionCoords + sizeofNormalsCoords + sizeofTextCoords, sizeofInstancePositions, instancePositions);

			    glVertexAttribPointer(0, positionNumComponents, Vertex::GetDataType(), GL_FALSE, 0, 0);
			    glVertexAttribPointer(1, normalNumComponents, Vertex::GetDataType(), GL_FALSE, 0, (GLvoid *)sizeofPositionCoords);
			    glVertexAttribPointer(2, textureNumComponents, Vertex::GetDataType(), GL_FALSE, 0, (GLvoid *)(sizeofPositionCoords + sizeofNormalsCoords));
			    glVertexAttribPointer(3, positionNumComponents, GL_UNSIGNED_INT, GL_FALSE, 0, (GLvoid *)(sizeofPositionCoords + sizeofNormalsCoords + sizeofTextCoords));

			    glEnableVertexAttribArray(0);
			    glEnableVertexAttribArray(1);
			    glEnableVertexAttribArray(2);
			    glEnableVertexAttribArray(3);

			    glVertexAttribDivisor(3, 1);

			glBindBuffer(GL_ARRAY_BUFFER,0);	
    	glBindVertexArray(0);

    	delete[] positionCoords;
    	delete[] normalsCoords;
    	delete[] textCoords;
    	delete[] instancePositions;
	}

	void ShapeManager::LoadShapes() {
		typedef std::map<std::string,struct Shape>::iterator ItType;
		for(ItType iterator = m_shapes.begin(); iterator != m_shapes.end(); iterator++) {
			LoadShape(iterator->first,iterator->second);
		}
	}
	
	void ShapeManager::LoadShape(std::string shapeName, struct Shape shape) {
		// Gen VBO
		GLuint vbo;
		glGenBuffers(1, &vbo);
		
		// Gen VAO
		GLuint vao;
		glGenVertexArrays(1,&vao);

		// Save the vao and vbo
		m_shapeVAOs[shapeName] = vao;
		m_VAOVBOs[vao] = vbo;
	}
	
	GLuint ShapeManager::GetShapeVAO(std::string shape) throw(std::invalid_argument) {
		if( m_shapeVAOs.find(shape) == m_shapeVAOs.end() )
			throw std::invalid_argument(std::string("No shape loaded for ") + shape);
			
		return m_shapeVAOs[shape];
	}
	
	size_t ShapeManager::GetShapeNbVertices(std::string shape) throw(std::invalid_argument) {
		if( m_shapeVAOs.find(shape) == m_shapeVAOs.end() )
			throw std::invalid_argument(std::string("No shape loaded for ") + shape);
			
		return m_shapes[shape].nbVertices;
	}
}
