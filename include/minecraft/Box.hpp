#ifndef _BOX_HPP_
#define _BOX_HPP_

#include <minecraft/GLtools.hpp>
#include <glm/glm.hpp>

namespace minecraft {
	class Box{
		private:
			glm::vec3 m_base;
			GLfloat m_width;
			GLfloat m_length;
			GLfloat m_height;
		public:
			
			Box(){
				m_width=0.075;
				m_length=0.075;
				m_height=0.175;
			}
			
			inline void setBase(glm::vec3 base){
				m_base=base;
			}
			inline void setWidth(GLfloat width){
				m_width=width;
			}
			inline void setLength(GLfloat length){
				m_length=length;
			}
			inline void setHeight(GLfloat height){
				m_height=height;
			}
			inline void setSize(glm::vec3 size){
				m_width=size.x;
				m_length=size.y;
				m_height=size.z;
			}
			inline glm::vec3 getBase(){
				return(m_base);
			}
			inline glm::vec3 getSize(){
				return glm::vec3(m_width,m_length,m_height);
			}
			inline glm::vec3 getBottomCorner(){
				return glm::vec3(m_base.x+m_width/2,m_base.y+m_length/2,m_base.z);
			}
			inline glm::vec3 getTopCorner(){
				return glm::vec3(m_base.x-m_width/2,m_base.y-m_length/2,m_base.z+m_height);
			}

	};
}

#endif
