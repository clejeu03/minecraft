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
			glm::vec3 m_formerPosition;
			bool m_formerBottomCollide;
			bool m_currentBottomCollide;
			
			//A few sounds
			Sound steps;
			Sound buildCube;
			Sound breakCube;
			Sound scream;
			Sound music;
			
			
		public:
			GameEngine();
			void SetMap(Map* map) { m_world = map; }
			void SetCharacter(Character* character) { m_character = character; }
			
			void SaveFormerCollide();
			void SaveFormerPosition();
			void BackToFormerPosition();
			bool collideBottom();
			bool collideTop();
			bool collideSides();
			void processGravity();
			void jump();
			bool aimCube(int);
			void InitializeSound();
			void ToggleMusic();
			void WalkSound();
			void WalkSoundStop();
	};
}

#endif
