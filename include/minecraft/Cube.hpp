#ifndef _MINECRAFT_CUBE_HPP_
#define _MINECRAFT_CUBE_HPP_

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <minecraft/Drawable.hpp>
#include <string>

namespace minecraft {
	typedef enum {
		CUBE = -1,
		SKYBOX_CUBE = -2,
		FLOATING_CUBE = -3,
		PHYSIC_CUBE = -4,
		EMPTY_CUBE = 0,
		CRYSTAL_CUBE = 1,
		CLOUD_CUBE = 2,
		ROCK_CUBE = 3,
		GRASS_CUBE = 4,
		DIRT_CUBE = 5,
		DIAMOND_CUBE = 6,
		GOLD_CUBE = 7
	}CubeType;

	class Cube : public Drawable {
		private:
			GLuint m_textureId;
			GLuint m_VAO;
			size_t m_nbVertices;
			
		public:
			const char* m_name;
			CubeType m_type;
			constexpr static GLfloat m_size = 0.1f;
			constexpr static GLuint m_tmpNbVertices = 36; //solution temporaire
			inline void SetNbVertices(size_t nb) { m_nbVertices = nb; }
			inline void SetTexId(GLuint id) { m_textureId = id; }
			inline GLuint GetTexId() { return m_textureId; }
			inline void SetVAOId(GLuint id) { m_VAO = id; }
			inline GLuint GetVAOId() { return m_VAO; }
			void Draw() const;
			const char* GetName(){return m_name;};
			CubeType GetType(){return m_type;};
	};
	
	class SkyBoxCube : public Cube {
		public:
			constexpr static GLfloat m_size = 1.f;
			SkyBoxCube(){ m_name = "SkyBoxCube"; m_type = SKYBOX_CUBE; }
			
	};

	/* Indiferent to gravity */
	class FloatingCube : public Cube {
		public:
			FloatingCube(){ m_name = "FloatingCube"; m_type = FLOATING_CUBE; }
	};

	/* Affected by gravity */
	class PhysicCube : public Cube {
		public:
			PhysicCube(){ m_name = "PhysicCube"; m_type = PHYSIC_CUBE; }
	};

	class CloudCube : public FloatingCube {
		public:
			CloudCube(){m_name="CloudCube"; m_type = CLOUD_CUBE; };
	};

	class RockCube : public PhysicCube {
		public:
			RockCube(){m_name="RockCube"; m_type = ROCK_CUBE; };
	};

	class CrystalCube : public PhysicCube {
		public:
			CrystalCube(){ m_name = "CrystalCube"; m_type = CRYSTAL_CUBE; }
	};

	class DirtCube : public PhysicCube {
		public:
			DirtCube(){ m_name = "DirtCube"; m_type = DIRT_CUBE; }
	};

	class GoldCube : public PhysicCube {
		public:
			GoldCube(){ m_name = "GoldCube"; m_type = GOLD_CUBE; }
	};

	class DiamondCube : public PhysicCube {
		public:
			DiamondCube(){ m_name = "DiamondCube"; m_type = DIAMOND_CUBE; }
	};

	class GrassCube : public PhysicCube {
		public:
			GrassCube(){ m_name = "GrassCube"; m_type = GRASS_CUBE; }
	};


}

#endif
