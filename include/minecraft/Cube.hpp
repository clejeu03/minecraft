#ifndef _MINECRAFT_CUBE_HPP_
#define _MINECRAFT_CUBE_HPP_

#include <GL/glew.h>
#include <minecraft/GLtools.hpp>
#include <minecraft/Drawable.hpp>
#include <iostream>

namespace minecraft {
	class Cube : public Drawable {
		private:
			GLuint m_textureId;
			GLuint m_VAO;
			size_t m_nbVertices;
		public:
			constexpr static float m_size = 0.1f;
			
			void SetTexId(GLuint id) { m_textureId = id; }
			void SetVAOId(GLuint id) { m_VAO = id; }
			void Draw() const;
	};

	class FloatingCube : public Cube {
	};

	class PhysicCube : public Cube {
	};

	class CloudCube : public FloatingCube {
	};

	class RockCube : public PhysicCube {
	};

	class CrystalCube : public PhysicCube {
	};
}

#endif
