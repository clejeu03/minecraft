#ifndef _MINECRAFT_GRAPHICENGINE_HPP_
#define _MINECRAFT_GRAPHICENGINE_HPP_

#include <map>
#include <minecraft/Map.hpp>
#include <minecraft/TextureManager.hpp>
#include <minecraft/ShapeManager.hpp>

namespace minecraft {
	class GraphicEngine {
		private:
			TextureManager m_textureMgr;
			ShapeManager m_shapeMgr;
			Map m_world;
			std::map<char*,Cube*> m_gameObjects;
			/* --->>> Character */
		public:
			GraphicEngine() : m_world(Map(100,100,100)) {}
			void Initialize();
			void Refresh();
	};
}

#endif
