#ifndef _MINECRAFT_CHARACTER_HPP_
#define _MINECRAFT_CHARACTER_HPP_

#include <minecraft/GLtools.hpp>
#include <minecraft/FirstPersonCamera.hpp>
#include <minecraft/Box.hpp>
#include <glm/glm.hpp>

namespace minecraft {
	class Character {
		private:
			FirstPersonCamera m_camera;
			//struct Vec3f m_position; Included in the Box
			bool m_mining;
			Box m_box;
			
			//! inventory
		public:
			GLfloat povHeight;
			Character(glm::vec3);
		
			Box& getBox();
			glm::vec3 position();
			
			void setPosition(glm::vec3);
			void setBoxSize(glm::vec3);
			// We may want to add a setter for each dimension of the size later
			
			void MoveFront(GLfloat);
			void MoveLeft(GLfloat);
			void RotateLeft(GLfloat);
			void LookUp(GLfloat);
			
			/* Return the view matrix from the camera following the player */
			glm::mat4 GetPointOfView();
	};
}

#endif
