#ifndef _MINECRAFT_GRAPHICENGINE_HPP_
#define _MINECRAFT_GRAPHICENGINE_HPP_

#include <map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <minecraft/Map.hpp>
#include <minecraft/TextureManager.hpp>
#include <minecraft/ShapeManager.hpp>
#include <minecraft/MatrixStack.hpp>
#include <minecraft/Character.hpp>

namespace minecraft {
	class GraphicEngine {
		private:
			TextureManager m_textureMgr;
			ShapeManager m_shapeMgr;
			Map m_world;
			std::map<std::string,Cube*> m_gameObjects;
			GLuint m_uniformTransformLocation;
			Character* m_character;
			glm::mat4 m_perspectiveMatrix;
			MatrixStack m_transformStack;
		public:
			GraphicEngine() : m_world(Map(100,100,100)) {} // To change : map must be a pointer and not be initialized there
			void Initialize(GLuint,size_t,size_t);
			void RefreshDisplay();
	};
}

#endif
