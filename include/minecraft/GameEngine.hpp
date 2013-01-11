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
	typedef std::map<std::string, int>::iterator ItInventory;
	typedef std::map<std::string,Cube*>::iterator ItGameObjects;

	class GameEngine {
		private:
			Map* m_world;
			Character* m_character;
			GLfloat gravity;
			GLfloat velocity;
			std::map<std::string,Cube*>* m_gameObjects;
			std::map<std::string, int> m_inventory;
			std::map<size_t, std::string> m_inventoryPosition;
			size_t m_currentInventory;
			
			//A few sounds
			Sound steps;
			Sound buildCube;
			Sound breakCube;
			Sound scream;
			
		public:
			GameEngine(){
				gravity=0.003;
				velocity=0;
				m_currentInventory = 1;};
			void SetMap(Map* map) { m_world = map; }
			void SetCharacter(Character* character) { m_character = character; }
			void SetGameObjects(std::map<std::string,Cube*>* dictionary) { m_gameObjects = dictionary; }
			bool collideBottom();
			bool collideSides();
			void processGravity(bool formerCollide);
			void jump();
			bool aimCube(int);
			std::string GetCubeType(GLfloat x,GLfloat y,GLfloat z)throw(std::invalid_argument);
			void AddInInventory(std::string cubeType) throw(std::invalid_argument);
			void SetCurrentInventory(size_t pos);
			inline	size_t GetCurrentInventory(){ return m_currentInventory;}
			inline std::map<size_t, std::string> GetInventoryPosition(){return m_inventoryPosition;}
			void RemoveFromInventory(std::string cubeType) throw(std::invalid_argument);
			void InitializeSound();
			void walkSound();
			void walkSoundStop();
	};
}

#endif

