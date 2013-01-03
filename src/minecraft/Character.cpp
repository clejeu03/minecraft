#include <minecraft/Character.hpp>

namespace minecraft {
	void Character::MoveFront(GLfloat distance) {
		m_camera.MoveFront(distance);
	}
	
	void Character::MoveLeft(GLfloat distance) {
		m_camera.MoveLeft(distance);
	}

	void Character::RotateLeft(GLfloat angle) {
		m_camera.RotateLeft(angle);
	}

	void Character::LookUp(GLfloat angle) {
		m_camera.RotateUp(angle);
	}
		
	glm::mat4 Character::GetPointOfView() {
		return m_camera.GetViewMatrix();
	}
}
