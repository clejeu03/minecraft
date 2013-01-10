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
			GLfloat gravity;
			GLfloat velocity;
			std::map<std::string,Cube*>* m_gameObjects;
			
		public:
			GameEngine();
			void SetMap(Map* map) { m_world = map; }
			void SetCharacter(Character* character) { m_character = character; }
			//void SetGameObjects(std::map<std::string,Cube*>* dictionary) { m_gameObjects = dictionary; }
			bool collideBottom();
			bool collideSides();
			void processGravity(bool formerCollide);
			void jump();
			bool aimCube(int);
	};
}

#endif
