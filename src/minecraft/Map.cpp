#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>
#include <minecraft/Map.hpp>
#include <iostream>

namespace minecraft {	
	Cube* Map::Get(size_t x, size_t y, size_t z) throw(std::out_of_range) {
		if( x >= m_width || x < 0 ||
		y >= m_height || y < 0 ||
		z >= m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map");
		
		ItCubeInstance res = m_data.find(MapCoords(x,y,z));
		if( res == m_data.end() )
			return NULL;

		return std::get<0>(res->second);
	}
	
	
	void Map::Set(size_t x, size_t y, size_t z, Cube* cube) throw(std::out_of_range) {
		if( x > m_width || x < 0 ||
		y > m_height || y < 0 ||
		z > m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map");

		m_data[MapCoords(x,y,z)] = std::make_tuple(cube,true);
		UpdateVisibilities(x,y,z,true);
	}
	
	void Map::SetByPixel(GLfloat x,GLfloat y,GLfloat z, Cube* cube) throw(std::out_of_range) {
		if( x > m_width || x < 0 ||
		y > m_height || y < 0 ||
		z > m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map in SetByPixel");
		
		Set((size_t)(x/Cube::m_size),(size_t)(y/Cube::m_size),(size_t)(z/Cube::m_size),cube);
	}
	
	void Map::Del(size_t x, size_t y, size_t z)  throw(std::out_of_range) {
		if( x > m_width || x < 0 ||
		y > m_height || y < 0 ||
		z > m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map");
			
		m_data.erase(MapCoords(x,y,z));
		UpdateVisibilities(x,y,z,false);
	}
	
	void Map::DelByPixel(GLfloat x,GLfloat y,GLfloat z) throw(std::out_of_range) {
		GLfloat cubeSize=Cube::m_size;
		x+=cubeSize*0.5;
		y+=cubeSize*0.5;
		z+=cubeSize*0.5;
		Del((size_t)(x/Cube::m_size),(size_t)(y/Cube::m_size),(size_t)(z/Cube::m_size));
	}
	
	void Map::FakeCreation(GLfloat x,GLfloat y,GLfloat z){
		if (Exists(15,25,15)){
			GLfloat cubeSize=Cube::m_size;
			x+=cubeSize*0.5;
			y+=cubeSize*0.5;
			z+=cubeSize*0.5;
			SetByPixel(x,y,z, Get(15,25,15));
		}
	}
	
	bool Map::Exists(size_t x, size_t y, size_t z) throw(std::out_of_range) {
		/*if( x > m_width || x < 0 ||
		y > m_height || y < 0 ||
		z > m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map in Exists");*/
			
		if( m_data.find(MapCoords(x,y,z)) == m_data.end() ){
			return false;
		}else{
			return true;
		}
	}
	
	bool Map::ExistsByPixel(GLfloat x, GLfloat y, GLfloat z){			
			
		GLfloat cubeSize=Cube::m_size;
		x+=cubeSize*0.5;
		y+=cubeSize*0.5;
		z+=cubeSize*0.5;
		
		return Exists((size_t)(x/Cube::m_size),(size_t)(y/Cube::m_size),(size_t)(z/Cube::m_size));
	}
	
	/* Update the visibility of the cube x,y,z.
	 * add: true = adding a cube, false = removing */
	void Map::UpdateVisibility(size_t x, size_t y, size_t z) throw(std::out_of_range) {
		if( x > m_width || x < 0 ||
		y > m_height || y < 0 ||
		z > m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map in UpdateVisibility");
			
		ItCubeInstance cube, neighbour1, neighbour2, neighbour3, neighbour4, neighbour5, neighbour6, end;
		cube = m_data.find(MapCoords(x,y,z));
		end = m_data.end();
		if( cube == end )
			throw std::out_of_range("Cube is not in the map in UpdateVisibility");
		neighbour1 = m_data.find(MapCoords(x-1,y,z));
		neighbour2 = m_data.find(MapCoords(x+1,y,z));
		neighbour3 = m_data.find(MapCoords(x,y-1,z));
		neighbour4 = m_data.find(MapCoords(x,y+1,z));
		neighbour5 = m_data.find(MapCoords(x,y,z-1));
		neighbour6 = m_data.find(MapCoords(x,y,z+1));
		
		if( neighbour1 != end && neighbour2 != end && neighbour3 != end
		&& neighbour4 != end && neighbour5 != end && neighbour6 != end ) {
			// It can be hidden
			Cube* pointer = std::get<0>(cube->second);
			cube->second = std::make_tuple(pointer,false);
		}
	}

	Cube* Map::GetByPixel(GLfloat x, GLfloat y, GLfloat z) throw(std::out_of_range) {
		if( x/Cube::m_size >= m_width || x < 0 ||
		y/Cube::m_size >= m_height || y < 0 ||
		z/Cube::m_size >= m_depth || z < 0 )
			throw std::out_of_range("Position is out of the map");
		
		ItCubeInstance res = m_data.find(MapCoords((size_t)(x/Cube::m_size),(size_t)(y/Cube::m_size),(size_t)(z/Cube::m_size)));
		if( res == m_data.end() )
			return NULL;
		
		return std::get<0>(res->second);
	}

	/* Update the visibility of a cube x,y,z and its neighbourhood if we
	 * add or remove it */
	void Map::UpdateVisibilities(size_t x, size_t y, size_t z, bool adding) {
		if( adding )
			UpdateVisibility(x,y,z);
		
		/* Foreach neighbour too, it can happen that it's out of range (at the border), no big deal */
		try {
			UpdateVisibility(x-1,y,z);
			UpdateVisibility(x+1,y,z);
			UpdateVisibility(x,y-1,z);
			UpdateVisibility(x,y+1,z);
			UpdateVisibility(x,y,z-1);
			UpdateVisibility(x,y,z+1);
		}
		catch( std::out_of_range e ) {}
	}
	
	/* Draw all the cubes at 0,0,0. . . */
	void Map::Draw() const{
		for(ItCubeInstanceConst iterator = m_data.begin(); iterator != m_data.end(); iterator++) {
			if( std::get<1>(iterator->second) ) // If the cube is not hidden by other cubes
				std::get<0>(iterator->second)->Draw();
		}
	}
	
	/* Draw the cubes at the right places considering their size */
	void Map::Draw(MatrixStack& matrixStack, GLuint uniformLocation) const {
		GLfloat cubeSize = Cube::m_size;
		for(ItCubeInstanceConst iterator = m_data.begin(); iterator != m_data.end(); iterator++) {
			if( std::get<1>(iterator->second) ) { // If the cube is not hidden by other cubes
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
					std::get<0>(iterator->second)->Draw();
				matrixStack.Pop();
			}
		}
	}

}
