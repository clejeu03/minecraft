#ifndef _MINECRAFT_GLTOOLS_HPP_
#define _MINECRAFT_GLTOOLS_HPP_

#include <GL/glew.h>

namespace minecraft {
	inline const GLvoid* BufferOffset(size_t offset) {
		return (const GLvoid*) offset;
	}

	struct Vec2f {
		GLfloat x;
		GLfloat y;
		Vec2f() : x(0), y(0) {}
		Vec2f(GLfloat xIn, GLfloat yIn) : x(xIn), y(yIn) {}
		inline static int GetNumComponents() { return 2; }
	};

	struct Vec3f {
		GLfloat x;
		GLfloat y;
		GLfloat z;
		Vec3f() : x(0), y(0), z(0) {}
		Vec3f(GLfloat xIn, GLfloat yIn, GLfloat zIn) : x(xIn), y(yIn), z(zIn) {}
		inline static int GetNumComponents() { return 3; }
	};
	
	struct Vertex {
		struct Vec3f position;
		struct Vec3f normal;
		struct Vec2f textureXY;
		
		Vertex() :
		position(Vec3f(0,0,0)), normal(Vec3f(0,0,0)), textureXY(Vec2f(0,0))
		{}
		Vertex(GLfloat x, GLfloat y, GLfloat z) :
		position(Vec3f(x,y,z)), normal(Vec3f(0,0,0)), textureXY(Vec2f(0,0))
		{}
		Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat xn, GLfloat yn, GLfloat zn) :
		position(Vec3f(x,y,z)), normal(Vec3f(xn,yn,zn)), textureXY(Vec2f(0,0))
		{}
		Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat xn, GLfloat yn, GLfloat zn, GLfloat xt, GLfloat yt) :
		position(Vec3f(x,y,z)), normal(Vec3f(xn,yn,zn)), textureXY(Vec2f(xt,yt))
		{}
		
		inline static int GetDataType() { return GL_FLOAT; }
		inline static int GetPositionNumComponents() { return 3; }
		inline static const GLvoid* GetPositionOffset() { return BufferOffset(offsetof(Vertex,position)); }
		inline static int GetNormalNumComponents() { return 3; }
		inline static const GLvoid* GetNormalOffset() { return BufferOffset(offsetof(Vertex,normal)); }
		inline static int GetTextureNumComponents() { return 2; }
		inline static const GLvoid* GetTextureOffset() { return BufferOffset(offsetof(Vertex,textureXY)); }
		inline static int GetByteSize() {
			return (GetPositionNumComponents() + GetNormalNumComponents() + GetTextureNumComponents()) * sizeof(GLfloat);
		}
	};
}

#endif
