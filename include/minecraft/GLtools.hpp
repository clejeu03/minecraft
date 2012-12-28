#ifndef _MINECRAFT_GLTOOLS_HPP_
#define _MINECRAFT_GLTOOLS_HPP_

#include <GL/glew.h>
#include <typeinfo>

namespace minecraft {
	inline const GLvoid* BufferOffset(size_t offset) {
		return (const GLvoid*) offset;
	}

	typedef struct Vec2f_tmp {
		GLfloat x;
		GLfloat y;
		Vec2f_tmp(GLfloat xIn, GLfloat yIn) : x(xIn), y(yIn) {}
		inline static int GetNumComponents() { return 2; }
	} Vec2f;

	typedef struct Vec3f_tmp {
		GLfloat x;
		GLfloat y;
		GLfloat z;
		Vec3f_tmp(GLfloat xIn, GLfloat yIn, GLfloat zIn) : x(xIn), y(yIn), z(zIn) {}
		inline static int GetNumComponents() { return 3; }
	} Vec3f;
	
	typedef struct Vertex_tmp {
		Vec3f position;
		Vec3f normal;
		Vec2f textureXY;
		
		Vertex_tmp() :
		position(Vec3f(0,0,0)), normal(Vec3f(0,0,0)), textureXY(Vec2f(0,0))
		{}
		Vertex_tmp(GLfloat x, GLfloat y, GLfloat z) :
		position(Vec3f(x,y,z)), normal(Vec3f(0,0,0)), textureXY(Vec2f(0,0))
		{}
		Vertex_tmp(GLfloat x, GLfloat y, GLfloat z, GLfloat xn, GLfloat yn, GLfloat zn) :
		position(Vec3f(x,y,z)), normal(Vec3f(xn,yn,zn)), textureXY(Vec2f(0,0))
		{}
		Vertex_tmp(GLfloat x, GLfloat y, GLfloat z, GLfloat xn, GLfloat yn, GLfloat zn, GLfloat xt, GLfloat yt) :
		position(Vec3f(x,y,z)), normal(Vec3f(xn,yn,zn)), textureXY(Vec2f(xt,yt))
		{}
		inline static int GetDataType() { return GL_FLOAT; }
		inline static int GetPositionNumComponents() { return 3; }
		inline static const GLvoid* GetPositionOffset() { return BufferOffset(offsetof(Vertex_tmp,position)); }
		inline static int GetNormalNumComponents() { return 3; }
		inline static const GLvoid* GetNormalOffset() { return BufferOffset(offsetof(Vertex_tmp,normal)); }
		inline static int GetTextureNumComponents() { return 2; }
		inline static const GLvoid* GetTextureOffset() { return BufferOffset(offsetof(Vertex_tmp,textureXY)); }
		inline static int GetByteSize() {
			return (GetPositionNumComponents() + GetNormalNumComponents() + GetTextureNumComponents()) * sizeof(GLfloat);
		}
	} Vertex;
}

#endif
