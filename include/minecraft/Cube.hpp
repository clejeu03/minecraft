#ifndef _MINECRAFT_CUBE_HPP_
#define _MINECRAFT_CUBE_HPP_

#include <GL/glew.h>
#include <minecraft/Drawable.hpp>

namespace minecraft {
	class Cube : public Drawable {
		private:
			static float m_size;
			static GLuint m_texture;
		public:
			void Draw() const;
			virtual void SetTexId(GLuint id) = 0;
			virtual GLuint GetTexId() const = 0;
	};

	class FloatingCube : public Cube {
	};

	class PhysicCube : public Cube {
	};

	class CloudCube : public FloatingCube {
		private:
			static GLuint m_texture;
		public:
			void SetTexId(GLuint id) { m_texture = id; }
			GLuint GetTexId() const { return m_texture; }
	};

	class RockCube : public PhysicCube {
		private:
			static GLuint m_texture;
		public:
			void SetTexId(GLuint id) { m_texture = id; }
			GLuint GetTexId() const { return m_texture; }
	};

	class CrystalCube : public PhysicCube {
		private:
			static GLuint m_texture;
		public:
			void SetTexId(GLuint id) { m_texture = id; }
			GLuint GetTexId() const { return m_texture; }
	};
}

#endif
