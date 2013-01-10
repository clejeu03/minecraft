#include <minecraft/ShapeManager.hpp>
#include <minecraft/Map.hpp>
#include <string>
#include <vector>
#include <iostream>

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
		m_shapes[std::string("cube")] = Shape(36);
		m_shapes[std::string("CrystalCube")] = Shape(36);
		m_shapes[std::string("CloudCube")] = Shape(36);
		m_shapes[std::string("RockCube")] = Shape(36);

		//Face gauche
		m_shapes[std::string("cube")].vertices[0] = Vertex(-0.5,-0.5,-0.5, -1.0, 0.0, 0.0, 0.0, 1.0);
		m_shapes[std::string("cube")].vertices[1] = Vertex(-0.5,-0.5, 0.5, -1.0, 0.0, 0.0, 1.0, 1.0);
		m_shapes[std::string("cube")].vertices[2] = Vertex(-0.5, 0.5, 0.5, -1.0, 0.0, 0.0, 1.0, 0.0);

		//Face gauche
		m_shapes[std::string("cube")].vertices[12] = Vertex(-0.5,-0.5,-0.5, -1.0, 0.0, 0.0, 0.0, 1.0);
		m_shapes[std::string("cube")].vertices[13] = Vertex(-0.5, 0.5, 0.5, -1.0, 0.0, 0.0, 1.0, 0.0);
		m_shapes[std::string("cube")].vertices[14] = Vertex(-0.5, 0.5,-0.5, -1.0, 0.0, 0.0, 0.0, 0.0);
		
		//Face derrière
		m_shapes[std::string("cube")].vertices[3] = Vertex(0.5, 0.5,-0.5, 0.0, 0.0, -1.0, 0.0, 0.0);
		m_shapes[std::string("cube")].vertices[4] = Vertex(-0.5,-0.5,-0.5, 0.0, 0.0, -1.0, 1.0, 1.0);
		m_shapes[std::string("cube")].vertices[5] = Vertex(-0.5, 0.5,-0.5, 0.0, 0.0, -1.0, 1.0, 0.0);

		//Face derrière
		m_shapes[std::string("cube")].vertices[9] = Vertex(0.5, 0.5,-0.5, 0.0, 0.0, -1.0, 0.0, 0.0);
		m_shapes[std::string("cube")].vertices[10] = Vertex(0.5,-0.5,-0.5, 0.0, 0.0, -1.0, 0.0, 1.0);
		m_shapes[std::string("cube")].vertices[11] = Vertex(-0.5,-0.5,-0.5, 0.0, 0.0, -1.0, 1.0, 1.0);
		
		//Face dessous
		m_shapes[std::string("cube")].vertices[6] = Vertex(0.5,-0.5, 0.5, 0.0, -1.0, 0.0, 1.0, 0.0);
		m_shapes[std::string("cube")].vertices[7] = Vertex(-0.5,-0.5,-0.5, 0.0, -1.0, 0.0, 0.0, 1.0);
		m_shapes[std::string("cube")].vertices[8] = Vertex(0.5,-0.5,-0.5, 0.0, -1.0, 0.0, 1.0, 1.0);

		//Face dessous
		m_shapes[std::string("cube")].vertices[15] = Vertex(0.5,-0.5, 0.5, 0.0, -1.0, 0.0, 1.0, 0.0);
		m_shapes[std::string("cube")].vertices[16] = Vertex(-0.5,-0.5, 0.5, 0.0, -1.0, 0.0, 0.0, 0.0);
		m_shapes[std::string("cube")].vertices[17] = Vertex(-0.5,-0.5,-0.5, 0.0, -1.0, 0.0, 0.0, 1.0);
		
		//Face avant
		m_shapes[std::string("cube")].vertices[18] = Vertex(-0.5, 0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0);
		m_shapes[std::string("cube")].vertices[19] = Vertex(-0.5,-0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 1.0);
		m_shapes[std::string("cube")].vertices[20] = Vertex(0.5,-0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0);

		//Face avant
		m_shapes[std::string("cube")].vertices[33] = Vertex(0.5, 0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 0.0);
		m_shapes[std::string("cube")].vertices[34] = Vertex(-0.5, 0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0);
		m_shapes[std::string("cube")].vertices[35] = Vertex(0.5,-0.5, 0.5,  0.0, 0.0, 1.0, 1.0, 1.0);
		
		//Face droite
		m_shapes[std::string("cube")].vertices[21] = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0);
		m_shapes[std::string("cube")].vertices[22] = Vertex(0.5,-0.5,-0.5, 1.0, 0.0, 0.0, 1.0, 1.0);
		m_shapes[std::string("cube")].vertices[23] = Vertex(0.5, 0.5,-0.5, 1.0, 0.0, 0.0, 1.0, 0.0);

		//Face droite
		m_shapes[std::string("cube")].vertices[24] = Vertex(0.5,-0.5,-0.5, 1.0, 0.0, 0.0, 1.0, 1.0);
		m_shapes[std::string("cube")].vertices[25] = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0);
		m_shapes[std::string("cube")].vertices[26] = Vertex(0.5,-0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0);

		//Face haut
		m_shapes[std::string("cube")].vertices[27] = Vertex(0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 1.0, 1.0);
		m_shapes[std::string("cube")].vertices[28] = Vertex(0.5, 0.5,-0.5, 0.0, 1.0, 0.0, 1.0, 0.0);
		m_shapes[std::string("cube")].vertices[29] = Vertex(-0.5, 0.5,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0);

		//Face haut
		m_shapes[std::string("cube")].vertices[30] = Vertex(0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 1.0, 1.0);
		m_shapes[std::string("cube")].vertices[31] = Vertex(-0.5, 0.5,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0);
		m_shapes[std::string("cube")].vertices[32] = Vertex(-0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0);
		

		///CrystalCube
		m_shapes[std::string("CrystalCube")].vertices = m_shapes[std::string("cube")].vertices;
		m_shapes[std::string("RockCube")].vertices = m_shapes[std::string("cube")].vertices;
		m_shapes[std::string("CloudCube")].vertices = m_shapes[std::string("cube")].vertices;
		/// Skybox
		m_shapes[std::string("skybox")] = Shape(36);

		//Face gauche
		m_shapes[std::string("skybox")].vertices[0] = Vertex(0.5,-0.5,-0.5, 1.0, 0.0, 0.0, 0.0, 2.0/3);
		m_shapes[std::string("skybox")].vertices[1] = Vertex(0.5,-0.5, 0.5, 1.0, 0.0, 0.0, 1./4, 2.0/3);
		m_shapes[std::string("skybox")].vertices[2] = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 1./4, 1.0/3);

		//Face gauche
		m_shapes[std::string("skybox")].vertices[12] = Vertex(0.5,-0.5,-0.5, 1.0, 0.0, 0.0, 0.0, 2.0/3);
		m_shapes[std::string("skybox")].vertices[13] = Vertex(0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 1./4, 1.0/3);
		m_shapes[std::string("skybox")].vertices[14] = Vertex(0.5, 0.5,-0.5, 1.0, 0.0, 0.0, 0.0, 1.0/3);
		
		//Face derrière
		m_shapes[std::string("skybox")].vertices[3] = Vertex(0.5, 0.5,0.5, 0.0, 0.0, 1.0, 1./4, 1.0/3);
		m_shapes[std::string("skybox")].vertices[4] = Vertex(-0.5,-0.5,0.5, 0.0, 0.0, 1.0, 1./2, 2.0/3);
		m_shapes[std::string("skybox")].vertices[5] = Vertex(-0.5, 0.5,0.5, 0.0, 0.0, 1.0, 1./2, 1.0/3);

		//Face derrière
		m_shapes[std::string("skybox")].vertices[9] = Vertex(0.5, 0.5,0.5, 0.0, 0.0, 1.0, 1./4, 1.0/3);
		m_shapes[std::string("skybox")].vertices[10] = Vertex(0.5,-0.5,0.5, 0.0, 0.0, 1.0, 1./4, 2.0/3);
		m_shapes[std::string("skybox")].vertices[11] = Vertex(-0.5,-0.5,0.5, 0.0, 0.0, 1.0, 1./2, 2.0/3);
		
		//Face dessous
		m_shapes[std::string("skybox")].vertices[6] = Vertex(-0.5,0.5, -0.5, 0.0, 1.0, 0.0, 1./2, 0.);
		m_shapes[std::string("skybox")].vertices[7] = Vertex(0.5,0.5,0.5, 0.0, 1.0, 0.0, 1./4, 1.0/3);
		m_shapes[std::string("skybox")].vertices[8] = Vertex(-0.5,0.5,0.5, 0.0, 1.0, 0.0, 2./4, 1.0/3);

		//Face dessous
		m_shapes[std::string("skybox")].vertices[15] = Vertex(-0.5,0.5, -0.5, 0.0, 1.0, 0.0, 1./2, 0.);
		m_shapes[std::string("skybox")].vertices[16] = Vertex(0.5,0.5, -0.5, 0.0, 1.0, 0.0, 1./4, 0.);
		m_shapes[std::string("skybox")].vertices[17] = Vertex(0.5,0.5,0.5, 0.0, 1.0, 0.0, 1./4, 1.0/3);
		
		//Face avant
		m_shapes[std::string("skybox")].vertices[18] = Vertex(-0.5, 0.5, -0.5, 0.0, 0.0, -1.0, 3./4, 1.0/3);
		m_shapes[std::string("skybox")].vertices[19] = Vertex(-0.5,-0.5, -0.5, 0.0, 0.0, -1.0, 3./4, 2.0/3);
		m_shapes[std::string("skybox")].vertices[20] = Vertex(0.5,-0.5, -0.5, 0.0, 0.0, -1.0, 1.0, 2.0/3);

		//Face avant
		m_shapes[std::string("skybox")].vertices[33] = Vertex(0.5, 0.5, -0.5, 0.0, 0.0, -1.0, 1.0, 1.0/3);
		m_shapes[std::string("skybox")].vertices[34] = Vertex(-0.5, 0.5, -0.5, 0.0, 0.0, -1.0, 3./4, 1.0/3);
		m_shapes[std::string("skybox")].vertices[35] = Vertex(0.5,-0.5, -0.5,  0.0, 0.0, -1.0, 1.0, 2.0/3);
		
		//Face droite
		m_shapes[std::string("skybox")].vertices[21] = Vertex(-0.5, 0.5, 0.5, -1.0, 0.0, 0.0, 1./2, 1.0/3);
		m_shapes[std::string("skybox")].vertices[22] = Vertex(-0.5,-0.5,-0.5, -1.0, 0.0, 0.0, 3./4, 2.0/3);
		m_shapes[std::string("skybox")].vertices[23] = Vertex(-0.5, 0.5,-0.5, -1.0, 0.0, 0.0, 3./4, 1.0/3);

		//Face droite
		m_shapes[std::string("skybox")].vertices[24] = Vertex(-0.5,-0.5,-0.5, -1.0, 0.0, 0.0, 3./4, 2.0/3);
		m_shapes[std::string("skybox")].vertices[25] = Vertex(-0.5, 0.5, 0.5, -1.0, 0.0, 0.0, 1./2, 1.0/3);
		m_shapes[std::string("skybox")].vertices[26] = Vertex(-0.5,-0.5, 0.5, -1.0, 0.0, 0.0, 1./2, 2.0/3);

		//Face haut
		m_shapes[std::string("skybox")].vertices[27] = Vertex(0.5, -0.5, 0.5, 0.0, -1.0, 0.0, 1./4, 1.0);
		m_shapes[std::string("skybox")].vertices[28] = Vertex(0.5, -0.5,-0.5, 0.0, -1.0, 0.0, 1./4, 2./3);
		m_shapes[std::string("skybox")].vertices[29] = Vertex(-0.5, -0.5,-0.5, 0.0, -1.0, 0.0, 1./2, 2./3);

		//Face haut
		m_shapes[std::string("skybox")].vertices[30] = Vertex(0.5, -0.5, 0.5, 0.0, -1.0, 0.0, 1./4, 1.0);
		m_shapes[std::string("skybox")].vertices[31] = Vertex(-0.5, -0.5,-0.5, 0.0, -1.0, 0.0, 1./2, 2./3);
		m_shapes[std::string("skybox")].vertices[32] = Vertex(-0.5, -0.5, 0.5, 0.0, -1.0, 0.0, 1./2, 1.0);
		
		/// Cursor
		m_shapes[std::string("cursor")] = Shape(6);
		
		m_shapes[std::string("cursor")].vertices[0] = Vertex(-0.05,0.05,0,0,0,0,0,1.);
		m_shapes[std::string("cursor")].vertices[1] = Vertex(0.05,0.05,0,0,0,0,1,1);
		m_shapes[std::string("cursor")].vertices[2] = Vertex(-0.05,-0.05,0,0,0,0,0,0);
		m_shapes[std::string("cursor")].vertices[3] = Vertex(-0.05,-0.05,0,0,0,0,0,0);
		m_shapes[std::string("cursor")].vertices[4] = Vertex(0.05,-0.05,0,0,0,0,1,0);
		m_shapes[std::string("cursor")].vertices[5] = Vertex(0.05,0.05,0,0,0,0,1,1);

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
	
	void ShapeManager::SetSkyboxBuffer() {
		
		GLuint vao = GetShapeVAO("skybox");
		GLuint vbo = m_VAOVBOs[vao];

		Shape shape = m_shapes["skybox"];

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

	void ShapeManager::SetBuffer(const char* type, std::vector<MapCoords>& cubeCoords) {
		
		GLuint vao = GetShapeVAO(std::string(type));
		GLuint vbo = m_VAOVBOs[vao];

		std::cout << "vao[" << type << "] = " << vao << std::endl;
		std::cout << "vbo[" << type << "] = " << vbo << std::endl;

		size_t cubesCount = cubeCoords.size();
		
		int positionNumComponents = Vertex::GetPositionNumComponents();
		size_t shapeNbVertices = GetShapeNbVertices(std::string(type));
		int normalNumComponents = Vertex::GetNormalNumComponents();
		int textureNumComponents = Vertex::GetTextureNumComponents();

		GLfloat* positionCoords = new GLfloat[positionNumComponents * shapeNbVertices];
		GLfloat* normalsCoords = new GLfloat[normalNumComponents * shapeNbVertices];
		GLfloat* textCoords = new GLfloat[textureNumComponents * shapeNbVertices];

		GLfloat* instancePositions = new GLfloat[cubesCount * positionNumComponents];

		typedef std::map<MapCoords,Cube*>::const_iterator ItType;
		int i = 0;
		for(i = 0; i<cubesCount; ++i) {
			instancePositions[positionNumComponents*i] = std::get<0>(cubeCoords[i]) * Cube::m_size;
			instancePositions[positionNumComponents*i+1] = std::get<1>(cubeCoords[i]) * Cube::m_size;
			instancePositions[positionNumComponents*i+2] = std::get<2>(cubeCoords[i]) * Cube::m_size;
			//std::cout << "Cube[" << i << "] = (" << instancePositions[positionNumComponents*i] << "," << instancePositions[positionNumComponents*i+1] << "," << instancePositions[positionNumComponents*i+2] << ")" << std::endl;
		}

		//exit(EXIT_SUCCESS);
		Vertex* vertices = m_shapes[std::string(type)].vertices;

		for(int i=0; i<shapeNbVertices; ++i) {
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
		size_t sizeofInstancePositions = cubesCount * positionNumComponents * sizeof(GLfloat);

	    /*std::cout << "cubesCount = " << cubesCount << std::endl;
	    std::cout << "shapeNbVertices = " << shapeNbVertices << std::endl;
	    std::cout << "positionNumComponents = " << positionNumComponents << std::endl;
	    std::cout << "normalNumComponents = " << normalNumComponents << std::endl;
	    std::cout << "textureNumComponents = " << textureNumComponents << std::endl;
	    std::cout << "sizeofPositionCoords = " << sizeofPositionCoords << std::endl;
	    std::cout << "sizeofNormalsCoords = " << sizeofNormalsCoords << std::endl;
	    std::cout << "sizeofTextCoords = " << sizeofTextCoords << std::endl;
	    std::cout << "sizeofInstancePositions = " << sizeofInstancePositions << std::endl;*/

	    //exit(EXIT_SUCCESS);
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
			    glVertexAttribPointer(3, positionNumComponents, Vertex::GetDataType(), GL_FALSE, 0, (GLvoid *)(sizeofPositionCoords + sizeofNormalsCoords + sizeofTextCoords));

			    glEnableVertexAttribArray(0);
			    glEnableVertexAttribArray(1);
			    glEnableVertexAttribArray(2);
			    glEnableVertexAttribArray(3);

			    glVertexAttribDivisor(3, 1);

			glBindBuffer(GL_ARRAY_BUFFER,0);	
    	glBindVertexArray(0);
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
