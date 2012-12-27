#ifndef _MINECRAFT_MAP_HPP_
#define _MINECRAFT_MAP_HPP_

#include <map>
#include <tuple>
#include <minecraft/Drawable.hpp>
#include <minecraft/Cube.hpp>

namespace minecraft {
	typedef std::tuple<int,int,int> MapCoords;
	
	class Map : public Drawable {
		private:
			int m_width;
			int m_height;
			int m_depth;
			std::map<MapCoords,Cube*> m_data;
		public:
			Map(int w,int h,int d) : m_width(w), m_height(h), m_depth(d) {}
			~Map();
			void Draw() const;
			void Set(int,int,int,Cube*) throw(std::out_of_range);
			Cube& Get(int,int,int) throw(std::out_of_range);
	};
}

#endif
