#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>
#include <minecraft/Map.hpp>
#include <iostream>

namespace minecraft {
	Map::~Map() {
		typedef std::map<MapCoords,Cube*>::iterator ItType;
		for(ItType iterator = m_data.begin(); iterator != m_data.end(); iterator++) {
			iterator->second = NULL;
		}
	}
	
	/* Draw all the cubes at 0,0,0. . . */
	void Map::Draw() const{
		typedef std::map<MapCoords,Cube*>::const_iterator ItType;
		for(ItType iterator = m_data.begin(); iterator != m_data.end(); iterator++) {
			iterator->second->Draw();
		}
	}
	
	/* Draw the cubes at the right places considering their size */
	void Map::Draw(MatrixStack& matrixStack, GLuint uniformLocation) const {
		GLfloat cubeSize = Cube::m_size;
		typedef std::map<MapCoords,Cube*>::const_iterator ItType;
		for(ItType iterator = m_data.begin(); iterator != m_data.end(); iterator++) {
			matrixStack.Push();
			matrixStack.Scale(glm::vec3(cubeSize));
			matrixStack.Translate(
				glm::vec3(
					std::get<0>(iterator->first),
					std::get<1>(iterator->first),
					std::get<2>(iterator->first)
				)
			);
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrixStack.Top()));
			iterator->second->Draw();
			matrixStack.Pop();
		}

	}
	
	void Map::Set(size_t x, size_t y, size_t z, Cube* cube) throw(std::out_of_range) {
		if( x > m_width || x < 0 ||
		y > m_height || y < 0 ||
		z > m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map");
		
		m_data[MapCoords(x,y,z)] = cube;
	}
	
	size_t Map::GetSizeW(){
		return m_width;
	}
	size_t Map::GetSizeH(){
		return m_height;
	}
	size_t Map::GetSizeD(){
		return m_depth;
	}
	
	bool Map::Exists(size_t x, size_t y, size_t z) throw(std::out_of_range) {	
		if( m_data.find(MapCoords(x,y,z)) == m_data.end() ){
			return 0;
		}else{
			return 1;
		}
	}
	
	bool Map::ExistsByPixel(GLfloat x, GLfloat y, GLfloat z) throw(std::out_of_range) {	
		GLfloat cubeSize=Cube::m_size;
		x+=cubeSize*0.5;
		y+=cubeSize*0.5;
		z+=cubeSize*0.5;
		if( m_data.find(MapCoords((size_t)(x/Cube::m_size),(size_t)(y/Cube::m_size),(size_t)(z/Cube::m_size))) == m_data.end() ){
			return 0;
		}else{
			return 1;
		}
	}
	
	Cube* Map::Get(size_t x, size_t y, size_t z) throw(std::out_of_range) {
		if( x >= m_width || x < 0 ||
		y >= m_height || y < 0 ||
		z >= m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map");
		
		//Cube doesn't exist	
		if( m_data.find(MapCoords(x,y,z)) == m_data.end() ){return NULL;}

		return m_data[MapCoords(x,y,z)];
	}
	
	Cube* Map::GetByPixel(GLfloat x, GLfloat y, GLfloat z) throw(std::out_of_range) {
		if( x/Cube::m_size >= m_width || x < 0 ||
		y/Cube::m_size >= m_height || y < 0 ||
		z/Cube::m_size >= m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map");
		
		//Cube doesn't exist	
		if( m_data.find(MapCoords((size_t)(x/Cube::m_size),(size_t)(y/Cube::m_size),(size_t)(z/Cube::m_size))) == m_data.end() ){return NULL;}
		
		return m_data[MapCoords((size_t)(x/Cube::m_size),(size_t)(y/Cube::m_size),(size_t)(z/Cube::m_size))];
	}
}
