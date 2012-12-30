#include <minecraft/FirstPersonCamera.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace minecraft {
	void FirstPersonCamera::MoveLeft(GLfloat distance) {
		
	}
	
	void FirstPersonCamera::MoveFront(GLfloat distance) {
		m_fDistance += distance;
	}
	
	void FirstPersonCamera::RotateLeft(GLfloat angle) {
		m_fAngleY += angle;
	}
	
	void FirstPersonCamera::RotateUp(GLfloat angle) {
		m_fAngleX += angle;
	}
	
	glm::mat4 FirstPersonCamera::GetViewMatrix() {
		glm::mat4 view = glm::lookAt(glm::vec3(0.,0.,-m_fDistance),glm::vec3(0.,0.,0.),glm::vec3(0.,1.,0.));
		view = glm::rotate(view,m_fAngleX,glm::vec3(1,0,0));
		view = glm::rotate(view,m_fAngleY,glm::vec3(0,1,0));
		return view;
	}
}
