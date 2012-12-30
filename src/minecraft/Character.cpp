#include <minecraft/Character.hpp>

namespace minecraft {
	glm::mat4 Character::GetPointOfView() {
		return m_camera.GetViewMatrix();
	}
}
