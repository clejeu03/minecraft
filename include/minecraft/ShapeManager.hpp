#ifndef _MINECRAFT_SHAPEMANAGER_HPP_
#define _MINECRAFT_SHAPEMANAGER_HPP_

#include <map>
#include <stdexcept>
#include <GL/glew.h>
#include <minecraft/GLtools.hpp>

namespace minecraft {
	typedef struct Shape_tmp {
			Vertex* vertices;
			size_t nbVertices;

			Shape_tmp() : nbVertices(0) {}
			Shape_tmp(size_t nb) : vertices(new Vertex[nb]()), nbVertices(nb) {}
			~Shape_tmp();
			size_t GetByteSize();
	} Shape;
	
	class ShapeManager {
		private:
			std::map<char*,Shape> m_shapes;
			std::map<char*,GLuint> m_shapeVAOs;
			std::map<GLuint,GLuint> m_VAOVBOs;
		public:
			ShapeManager();
			~ShapeManager();
			void LoadShapes();
			void LoadShape(char*,Shape);
			GLuint GetShapeVAO(char*) throw(std::invalid_argument);
	};
}

#endif
