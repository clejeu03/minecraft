#ifndef _MINECRAFT_GAMEENGINE_HPP_
#define _MINECRAFT_GAMEENGINE_HPP_

#include <map>
#include <iostream>
#include <string>
#include <stdexcept>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <minecraft/Map.hpp>
#include <minecraft/Character.hpp>

namespace minecraft {
	class GameEngine {
		private:
			Map* m_world;
			Character* m_character;
			
		public:
			//~GraphicEngine();
			void SetMap(Map* map) { m_world = map; }
			void SetCharacter(Character* character) { m_character = character; }
			bool collide(){
				//glm::vec3 position=m_character->position();
				return m_world->Exists(10,19,10);/*position.x,position.y,position.z*/
			}

	};
}

#endif
