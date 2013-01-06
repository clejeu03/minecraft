#ifndef _MINECRAFT_CHARACTER_HPP_
#define _MINECRAFT_CHARACTER_HPP_

#include <minecraft/GLtools.hpp>
#include <minecraft/FirstPersonCamera.hpp>
#include <glm/glm.hpp>

namespace minecraft {
	class Character {
		private:
			FirstPersonCamera m_camera;
			struct Vec3f m_position;
			bool m_mining;
			//! collide box used by the gameEngine 
			//! inventory
		public:
			void MoveFront(GLfloat);
			void RotateLeft(GLfloat);
			void LookUp(GLfloat);
			/* Return the view matrix from the camera following the player */
			glm::mat4 GetPointOfView();
	};
}

#endif
