#include <stdexcept>
#include <minecraft/Map.hpp>

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
