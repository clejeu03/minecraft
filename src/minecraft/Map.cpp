#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>
#include <minecraft/Map.hpp>

#include <iostream>

namespace minecraft {
	Map::~Map() {
		typedef std::map<MapCoords,Cube*>::iterator ItType;
		for(ItType iterator = m_data.begin(); iterator != m_data.end(); iterator++) {
			free(iterator->second);
		}
	}
	
	void Map::Draw() const{
		typedef std::map<MapCoords,Cube*>::const_iterator ItType;
		for(ItType iterator = m_data.begin(); iterator != m_data.end(); iterator++) {
			/* TO DO : Move to the right place, using the static size of a cube and the indexes */
			iterator->second->Draw(); // Draw localy !
		}
	}
	
	void Map::Draw(MatrixStack& matrixStack, GLuint uniformLocation) const {
		GLfloat cubeSize = Cube::m_size;
		typedef std::map<MapCoords,Cube*>::const_iterator ItType;
		for(ItType iterator = m_data.begin(); iterator != m_data.end(); iterator++) {
			matrixStack.Push();
			matrixStack.Translate(
				glm::vec3(
					std::get<0>(iterator->first),
					std::get<1>(iterator->first),
					std::get<2>(iterator->first)
				)
			);
			matrixStack.Scale(glm::vec3(cubeSize));
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrixStack.Top()));
			iterator->second->Draw();
			matrixStack.Pop();
		}

	}
	
	void Map::Set(int x, int y, int z, Cube* cube) throw(std::out_of_range) {
		if( x > m_width || x < 0 ||
		y > m_height || y < 0 ||
		z > m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map");
		
		m_data[MapCoords(x,y,z)] = cube;
	}
	
	Cube& Map::Get(int x, int y, int z) throw(std::out_of_range) {
		if( x >= m_width || x < 0 ||
		y >= m_height || y < 0 ||
		z >= m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map");
		
		return *m_data[MapCoords(x,y,z)];
	}
}
