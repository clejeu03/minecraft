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
			inline bool Exists(){
				if (m_textureId ==0){
					return 1;
				}else{
					return 0;
				}
			}
			constexpr static GLfloat m_size = 0.1f;
			inline void SetNbVertices(size_t nb) { m_nbVertices = nb; }
			inline void SetTexId(GLuint id) { m_textureId = id; }
			inline void SetVAOId(GLuint id) { m_VAO = id; }
			void Draw() const;
	};

	/* Indiferent to gravity */
	class FloatingCube : public Cube {
	};

	/* Affected by gravity */
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
