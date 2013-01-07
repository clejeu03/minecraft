#ifndef _MINECRAFT_MAP_HPP_
#define _MINECRAFT_MAP_HPP_

#include <stdexcept>
#include <map>
#include <tuple>
#include <minecraft/Drawable.hpp>
#include <minecraft/Cube.hpp>
#include <minecraft/MatrixStack.hpp>

namespace minecraft {
	/* x, y, z : the game map is only a 3D matrix of slots */
	typedef std::tuple<int,int,int> MapCoords;
	
	class Map : public Drawable {
		private:
			size_t m_width;
			size_t m_height;
			size_t m_depth;
			std::map<MapCoords,Cube*> m_data;

		public:
			Map() : m_width(0), m_height(0), m_depth(0) {}
			~Map();
			void Resize(size_t w, size_t h, size_t d) {
				m_width = w;
				m_height = h;
				m_depth = d;
			}
			void Draw() const;
			/* Draw the cubes at the right places considering their size */
			void Draw(MatrixStack&, GLuint) const;
			size_t GetSizeW();
			size_t GetSizeH();
			size_t GetSizeD();
			void Set(size_t,size_t,size_t,Cube*) throw(std::out_of_range);

			bool Exists(size_t,size_t,size_t) throw(std::out_of_range);
			bool ExistsByPixel(GLfloat,GLfloat,GLfloat) throw(std::out_of_range);
			Cube* Get(size_t,size_t,size_t) throw(std::out_of_range);
			Cube* GetByPixel(GLfloat,GLfloat,GLfloat) throw(std::out_of_range);


	};
}

#endif
