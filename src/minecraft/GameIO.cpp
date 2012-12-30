#include <minecraft/GameIO.hpp>

namespace minecraft {
	void GameIO::LoadMap() throw(std::logic_error) {
		if( NULL == m_gameObjects || NULL == m_file )
			throw std::logic_error("Can't load map without game objects dictionary");
		
		/* Just an example, should be parsed from json */
		m_map->Resize(100,100,100);
		std::map<std::string,Cube*> dictionary = *m_gameObjects;
		m_map->Set(1,1,2,dictionary[std::string("CloudCube")]);
		m_map->Set(0,0,5,dictionary[std::string("RockCube")]);
		m_map->Set(0,1,2,dictionary[std::string("CloudCube")]);
		m_map->Set(1,2,5,dictionary[std::string("RockCube")]);
		m_map->Set(2,4,9,dictionary[std::string("CloudCube")]);
		m_map->Set(25,0,5,dictionary[std::string("RockCube")]);
		m_map->Set(0,1,1,dictionary[std::string("CloudCube")]);	
	}
}
