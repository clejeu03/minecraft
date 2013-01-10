#ifndef _MINECRAFT_CUBE_HPP_
#define _MINECRAFT_CUBE_HPP_

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <minecraft/Drawable.hpp>
#include <string>

namespace minecraft {
	class Cube : public Drawable {
		private:
			GLuint m_textureId;
			GLuint m_VAO;
			size_t m_nbVertices;
			
		public:
			const char* m_name;
			constexpr static GLfloat m_size = 0.1f;
			constexpr static GLuint m_tmpNbVertices = 36; //solution temporaire
			inline void SetNbVertices(size_t nb) { m_nbVertices = nb; }
			inline void SetTexId(GLuint id) { m_textureId = id; }
			inline GLuint GetTexId() { return m_textureId; }
			inline void SetVAOId(GLuint id) { m_VAO = id; }
			inline GLuint GetVAOId() { return m_VAO; }
			void Draw() const;
			const char* GetName(){return m_name;};
	};
	
	class SkyBoxCube : public Cube {
		public:
			constexpr static GLfloat m_size = 1.f;
			SkyBoxCube(){ m_name = "SkyBoxCube"; }
			
	};

	/* Indiferent to gravity */
	class FloatingCube : public Cube {
		public:
			FloatingCube(){ m_name = "FloatingCube"; }
	};

	/* Affected by gravity */
	class PhysicCube : public Cube {
		public:
			PhysicCube(){ m_name = "PhysicCube"; }
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
		public:
			CrystalCube(){ m_name = "CrystalCube"; }
	};
}

#endif
