#ifndef _MINECRAFT_SHAPEMANAGER_HPP_
#define _MINECRAFT_SHAPEMANAGER_HPP_

#include <string>
#include <map>
#include <stdexcept>
#include <GL/glew.h>
#include <vector>
#include <minecraft/GLtools.hpp>
#include <minecraft/Map.hpp>

namespace minecraft {
	/* Just a collection of vertices */
	struct Shape {
			struct Vertex* vertices;
			size_t nbVertices;

			Shape() : vertices(new Vertex[0]), nbVertices(0) { }
			Shape(size_t nb) : vertices(new Vertex[nb]), nbVertices(nb) { }
			Shape(const Shape&);
			Shape& operator=(const Shape&);
			~Shape();
			size_t GetByteSize();
	};
	
	/* Manage the shapes into the hardware */
	class ShapeManager {
		private:
			std::map<std::string,struct Shape> m_shapes;
			std::map<std::string,GLuint> m_shapeVAOs;
			std::map<GLuint,GLuint> m_VAOVBOs;
		public:
			ShapeManager();
			~ShapeManager();
			void SetSkyboxBuffer();
			void SetBuffer(const char*, std::vector<MapCoords>&);
			void LoadShapes();
			void LoadShape(std::string,struct Shape);
			GLuint GetShapeVAO(std::string) throw(std::invalid_argument);
			size_t GetShapeNbVertices(std::string) throw(std::invalid_argument);
	};
}

#endif
