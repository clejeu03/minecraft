#ifndef _MINECRAFT_CUBE_HPP_
#define _MINECRAFT_CUBE_HPP_

#include <GL/glew.h>
#include <minecraft/Drawable.hpp>
#include <string>

namespace minecraft {
	class Cube : public Drawable {
		private:
			GLuint m_textureId;
			GLuint m_VAO;
			size_t m_nbVertices;
			
		protected:
			std::string m_name;
			
		public:
			constexpr static GLfloat m_size = 0.1f;
			inline void SetNbVertices(size_t nb) { m_nbVertices = nb; }
			inline void SetTexId(GLuint id) { m_textureId = id; }
			inline void SetVAOId(GLuint id) { m_VAO = id; }
			void Draw() const;
			std::string GetName(){return m_name;};
	};
	
	class SkyBoxCube : public Cube {
		public:
			constexpr static GLfloat m_size = 1.f;
	};

	/* Indiferent to gravity */
	class FloatingCube : public Cube {
	};

	/* Affected by gravity */
	class PhysicCube : public Cube {
	};

	class CloudCube : public FloatingCube {
		public:
			CloudCube(){m_name="CloudCube";};
	};

	class RockCube : public PhysicCube {
		public:
			RockCube(){m_name="RockCube";};
	};

	class CrystalCube : public PhysicCube {
	};
}

#endif
