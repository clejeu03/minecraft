#ifndef __TRACKBALLCAMERA__
#define __TRACKBALLCAMERA__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TrackBallCamera{ 
	private:
		float m_fDistance;
		float m_fAngle_X;
		float m_fAngle_Y;
		
	public:
		TrackBallCamera(){
			m_fDistance = 0;
			m_fAngle_X = 0;
			m_fAngle_Y = 0;
		}
		inline void moveFront(float distance){
			m_fDistance += distance;
		}
		inline void rotateLeft(float degrees){
			m_fAngle_Y += degrees;
		}
		inline void rotateUp(float degrees){
			m_fAngle_X += degrees;
		}
		glm::mat4 getViewMatrix() const {
			glm::mat4 M = glm::lookAt(glm::vec3(0,0,-m_fDistance), glm::vec3(0,0,0), glm::vec3(0,1,0));
			M = glm::rotate(M, this->m_fAngle_X, glm::vec3(1,0,0));
			M = glm::rotate(M, this->m_fAngle_Y, glm::vec3(0,1,0));
			return M;
		}
		/*glm::vec3 getPosition() {
			return m_Position;
		}*/
};
#endif

