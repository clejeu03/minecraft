#ifndef _MINECRAFT_MAP_HPP_
#define _MINECRAFT_MAP_HPP_

#include <stdexcept>
#include <map>
#include <tuple>
#include <vector>
#include <minecraft/Drawable.hpp>
#include <minecraft/Cube.hpp>
#include <minecraft/MatrixStack.hpp>

namespace minecraft {
	/* x, y, z : the game map is only a 3D matrix of slots */
	typedef std::tuple<size_t,size_t,size_t> MapCoords;
	/* Cube is pointing an unique instance o the cube type. The boolean indicate whether
	 * the cube is visible or doesn't need to be drawn (hidden by other cubes) */
	typedef std::tuple<Cube*,bool> CubeInstance;
	/* Iterator */
	typedef std::map<MapCoords,CubeInstance>::iterator ItCubeInstance;
	typedef std::map<MapCoords,CubeInstance>::const_iterator ItCubeInstanceConst;
	
	class Map : public Drawable {
		private:
			size_t m_width;
			size_t m_height;
			size_t m_depth;
			std::map<MapCoords,CubeInstance> m_data;
			bool m_refresh;

		public:
			Map() : m_width(0), m_height(0), m_depth(0), m_refresh(true) {}
			inline size_t GetSizeW() { return m_width; }
			inline size_t GetSizeH() { return m_height; }
			inline size_t GetSizeD() { return m_depth; }
			inline void Resize(size_t w, size_t h, size_t d) {
				m_width = w;
				m_height = h;
				m_depth = d;
			}
			
			Cube* Get(size_t,size_t,size_t) throw(std::out_of_range);
			Cube* GetByPixel(GLfloat,GLfloat,GLfloat) throw(std::out_of_range);
			void Set(size_t,size_t,size_t,Cube*) throw(std::out_of_range);
			void SetByPixel(GLfloat,GLfloat,GLfloat,Cube*) throw(std::out_of_range);
			void Del(size_t,size_t,size_t) throw(std::out_of_range);
			void DelByPixel(GLfloat,GLfloat,GLfloat) throw(std::out_of_range);
			void FakeCreation(GLfloat,GLfloat,GLfloat);
			
			bool Exists(size_t,size_t,size_t) throw(std::out_of_range);
			bool ExistsByPixel(GLfloat,GLfloat,GLfloat);
			
			void UpdateVisibility(size_t,size_t,size_t) throw(std::out_of_range);
			void UpdateVisibilities(size_t,size_t,size_t,bool);
			
			void Draw() const;
			void Draw(MatrixStack&, GLuint) const;

			inline bool checkForRefresh(){ return m_refresh;}

			std::vector<MapCoords> GetPositions() const;
	};
}

#endif
