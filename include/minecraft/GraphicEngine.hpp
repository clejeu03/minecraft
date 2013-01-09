#ifndef _MINECRAFT_GRAPHICENGINE_HPP_
#define _MINECRAFT_GRAPHICENGINE_HPP_

#include <map>
#include <string>
#include <stdexcept>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <minecraft/Map.hpp>
#include <minecraft/TextureManager.hpp>
#include <minecraft/ShapeManager.hpp>
#include <minecraft/MatrixStack.hpp>
#include <minecraft/Character.hpp>

namespace minecraft {

	typedef std::map<std::string, int>::iterator ItInventory;
	typedef std::map<std::string,Cube*>::iterator ItGameObjects;


	class GraphicEngine {
		private:
			TextureManager m_textureMgr;
			ShapeManager m_shapeMgr;
			Map* m_world;
			std::map<std::string,Cube*> m_gameObjects;
			std::map<std::string, int> m_inventory;
			GLuint m_uniformTransformLocation;
			GLuint m_uniform2dMode;
			GLuint m_uniformSunColor;
			GLuint m_uniformSunDirection;
			GLuint m_uniformSunAmbient;
			Character* m_character;
			glm::mat4 m_perspectiveMatrix;
			MatrixStack m_transformStack;
			
			bool m_displayInventory;
		public:
			GraphicEngine() { m_displayInventory = false; }
			~GraphicEngine();
			/* Init openGL context and features */
			void StartGL() throw(std::runtime_error);
			/* Initialize the graphic ressources and structure used in the game */
			void Initialize(size_t,size_t);
			void SetMap(Map* map) { m_world = map; }
			void SetCharacter(Character* character) { m_character = character; }
			std::map<std::string,Cube*>* GetGameObjects() { return &m_gameObjects; }
			void RefreshDisplay() throw(std::logic_error);
			void DrawCursor();
			inline void OpenInventory() { m_displayInventory = true; }
			void DrawInventory();
			std::string GetCubeType(Cube* cube);
			void AddInInventory(Cube* cube) throw(std::invalid_argument);
			void RemoveFromInventory(std::string cubeType) throw(std::invalid_argument);
	};
}

#endif
