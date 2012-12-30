#ifndef _MINECRAFT_FIRSTPERSONCAMERA_HPP_
#define _MINECRAFT_FIRSTPERSONCAMERA_HPP_

#include <minecraft/GLtools.hpp>
#include <glm/glm.hpp>

namespace minecraft {
	class Camera {
		public:
			virtual void MoveLeft(GLfloat) = 0;
			virtual void MoveFront(GLfloat) = 0;
			virtual void RotateLeft(GLfloat) = 0;
			virtual void RotateUp(GLfloat) = 0;
			virtual glm::mat4 GetViewMatrix() = 0;
	};
	
	class FirstPersonCamera : public Camera { // For the moment just a trackball...
		private:
			GLfloat m_fDistance;
			GLfloat m_fAngleX;
			GLfloat m_fAngleY;
		public:
			FirstPersonCamera() : m_fDistance(1), m_fAngleX(0), m_fAngleY(0) {}
			void MoveLeft(GLfloat);
			void MoveFront(GLfloat);
			void RotateLeft(GLfloat);
			void RotateUp(GLfloat);
			glm::mat4 GetViewMatrix();
	};
}

#endif
