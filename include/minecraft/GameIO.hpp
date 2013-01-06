#ifndef _MINECRAFT_GAMEIO_HPP_
#define _MINECRAFT_GAMEIO_HPP_

#include <map>
#include <string>
#include <stdexcept>
#include <minecraft/Map.hpp>
#include <minecraft/Character.hpp>

namespace minecraft {
	class GameIO {
		private:
			char* m_file; // Could be a FILE stream type or something like this
			Map* m_map;
			Character* m_character;
			std::map<std::string,Cube*>* m_gameObjects;
		public:
			GameIO() {};
			GameIO(char* filePath) { m_file = filePath; }
			void SetCharacter(Character* character) { m_character = character; }
			void SetMap(Map* map) { m_map = map; }
			void SetGameObjects(std::map<std::string,Cube*>* dictionary) { m_gameObjects = dictionary; }
			void LoadMap() throw(std::logic_error);
			void GenerateMap(size_t width, size_t height, size_t depth);
			void LoadInventory() {} // Why not ?
			void SaveMap();
			void SaveInventory() {}
	};
}

#endif
