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
		public:
			glm::mat4 GetPointOfView();
	};
}

#endif
