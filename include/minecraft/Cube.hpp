#ifndef _MINECRAFT_CUBE_HPP_
#define _MINECRAFT_CUBE_HPP_

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <minecraft/Drawable.hpp>

namespace minecraft {
	class Cube : public Drawable {
		private:
			GLuint m_textureId;
			GLuint m_VAO;
			size_t m_nbVertices;
		public:
			constexpr static GLfloat m_size = 0.1f;
			constexpr static GLuint m_tmpNbVertices = 36; //solution temporaire
			inline void SetNbVertices(size_t nb) { m_nbVertices = nb; }
			inline void SetTexId(GLuint id) { m_textureId = id; std::cout << "textureId[" << m_type << "] = " << id << std::endl; }
			inline GLuint GetTexId() { return m_textureId; }
			inline void SetVAOId(GLuint id) { m_VAO = id; }
			inline GLuint GetVAOId() { return m_VAO; }
			void Draw() const;
			const char* m_type;
	};
	
	class SkyBoxCube : public Cube {
		public:
			constexpr static GLfloat m_size = 1.f;
			SkyBoxCube(){ m_type = "SkyBoxCube"; }
			
	};

	/* Indiferent to gravity */
	class FloatingCube : public Cube {
		public:
			FloatingCube(){ m_type = "FloatingCube"; }
	};

	/* Affected by gravity */
	class PhysicCube : public Cube {
		public:
			PhysicCube(){ m_type = "PhysicCube"; }
	};

	class CloudCube : public FloatingCube {
		public:
			CloudCube(){ m_type = "CloudCube"; }
	};

	class RockCube : public PhysicCube {
		public:
			RockCube(){ m_type = "RockCube"; }
	};

	class CrystalCube : public PhysicCube {
		public:
			CrystalCube(){ m_type = "CrystalCube"; }
	};
}

#endif
