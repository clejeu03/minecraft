#ifndef _MINECRAFT_FIRSTPERSONCAMERA_HPP_
#define _MINECRAFT_FIRSTPERSONCAMERA_HPP_

#include <minecraft/GLtools.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace minecraft {
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
				m_Position += t*glm::cross(m_LeftVector,glm::vec3(0,1,0));
			}
			inline void MoveVector(GLfloat t, glm::vec3 vec){
				m_Position += t*vec;
			}
			inline void RotateLeft(GLfloat degrees){
				m_fPhi += glm::radians(degrees);
				computeDirectionVectors();
			}
			inline void RotateUp(GLfloat degrees){
				m_fTheta += glm::radians(degrees);
				computeDirectionVectors();
			}
			
			inline glm::vec3 GetDirection(){
				return m_FrontVector;
			}
			glm::mat4 GetViewMatrix() const{
				return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
			}
			
	};
}

#endif
