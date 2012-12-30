#ifndef _MINECRAFT_CUBE_HPP_
#define _MINECRAFT_CUBE_HPP_

#include <GL/glew.h>
#include <minecraft/Drawable.hpp>

namespace minecraft {
	class Cube : public Drawable {
		private:
			GLuint m_textureId;
			GLuint m_VAO;
			size_t m_nbVertices;
		public:
			constexpr static GLfloat m_size = 0.1f;
			inline void SetNbVertices(size_t nb) { m_nbVertices = nb; }
			inline void SetTexId(GLuint id) { m_textureId = id; }
			inline void SetVAOId(GLuint id) { m_VAO = id; }
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
