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
#include <minecraft/Sound.hpp>

namespace minecraft {
	class GameEngine {
		private:
			Map* m_world;
			Character* m_character;
			GLfloat gravity;
			GLfloat velocity;
			
			//A few sounds
			Sound steps;
			Sound buildCube;
			Sound breakCube;
			Sound scream;
			
			
		public:
			Sound music;
			GameEngine();
			void SetMap(Map* map) { m_world = map; }
			void SetCharacter(Character* character) { m_character = character; }
			bool collideBottom();
			bool collideTop();
			bool collideSides();
			void processGravity(bool formerCollide);
			void jump();
			bool aimCube(int);
			void InitializeSound();
			void walkSound();
			void walkSoundStop();
	};
}

#endif
