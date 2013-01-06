#ifndef _MINECRAFT_FIRSTPERSONCAMERA_HPP_
#define _MINECRAFT_FIRSTPERSONCAMERA_HPP_

#include <minecraft/GLtools.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace minecraft {
	/*class Camera {
		public:
			virtual void MoveLeft(GLfloat) = 0;
			virtual void MoveFront(GLfloat) = 0;
			virtual void RotateLeft(GLfloat) = 0;
			virtual void RotateUp(GLfloat) = 0;
			virtual glm::mat4 GetViewMatrix() = 0;
	};*/
	
	/* For the moment just a trackball... 
	class TrackballCamera : public Camera {
		private:
			GLfloat m_fDistance;
			GLfloat m_fAngleX;
			GLfloat m_fAngleY;
		public:
			TrackballCamera() : m_fDistance(1), m_fAngleX(0), m_fAngleY(0) {}
			void MoveLeft(GLfloat);
			void MoveFront(GLfloat);
			void RotateLeft(GLfloat);
			void RotateUp(GLfloat);
			glm::mat4 GetViewMatrix();
	};*/
	
	/*Implementing the FP camera*/
	class FirstPersonCamera /*: public Camera*/{ 
		private:
			glm::vec3 m_Position;
			GLfloat m_fPhi;
			GLfloat m_fTheta;
			glm::vec3 m_FrontVector;
			glm::vec3 m_LeftVector;
			glm::vec3 m_UpVector;
			
			void computeDirectionVectors(){
				m_FrontVector = glm::vec3(
									cos(m_fTheta)*sin(m_fPhi),
									sin(m_fTheta),
									cos(m_fTheta)*cos(m_fPhi)
								);
				m_LeftVector = glm::vec3(
									sin(m_fPhi+(M_PI/2)),
									0,
									cos(m_fPhi+(M_PI/2))
								);
				m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
			}
			
		public:
			
			FirstPersonCamera(){
				m_Position = glm::vec3(0,0,0);
				m_fPhi = 0;
				m_fTheta = 0;
				computeDirectionVectors();
			}
			
			inline glm::vec3 Position(){
				return m_Position;
			}
			
			inline void setPosition(glm::vec3 position){
				m_Position=position;
			}
			inline void MoveLeft(GLfloat t){
				m_Position += t*m_LeftVector;
				
			}
			inline void MoveFront(GLfloat t){
				m_Position+=t*glm::dot(m_FrontVector,glm::vec3 (1,0,0));
				// WIP m_Position += t*glm::cross(m_LeftVector,glm::vec3(0,1,0));
			}
			inline void RotateLeft(GLfloat degrees){
				m_fPhi += glm::radians(degrees);
				computeDirectionVectors();
			}
			inline void RotateUp(GLfloat degrees){
				m_fTheta += glm::radians(degrees);
				computeDirectionVectors();
			}
			glm::mat4 GetViewMatrix() const{
				return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
			}
			
	};
}

#endif
