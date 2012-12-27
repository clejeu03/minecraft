#ifndef _MINECRAFT_MATH_HPP_
#define _MINECRAFT_MATH_HPP_

#include <GL/glew.h>

namespace minecraft {
	typedef struct Vec2f_tmp {
		GLfloat x;
		GLfloat y;
		Vec2f_tmp(GLfloat xIn, GLfloat yIn) : x(xIn), y(yIn) {}
	} Vec2f;

	typedef struct Vec3f_tmp {
		GLfloat x;
		GLfloat y;
		GLfloat z;
		Vec3f_tmp(GLfloat xIn, GLfloat yIn, GLfloat zIn) : x(xIn), y(yIn), z(zIn) {}
	} Vec3f;

	typedef struct Vertex_tmp {
		Vec3f position;
		Vec3f normal;
		Vec2f textureXY;
		Vertex_tmp(GLfloat x, GLfloat y, GLfloat z) :
		position(Vec3f(x,y,z)), normal(Vec3f(0,0,0)), textureXY(Vec2f(0,0))
		{}
		Vertex_tmp(GLfloat x, GLfloat y, GLfloat z, GLfloat xn, GLfloat yn, GLfloat zn) :
		position(Vec3f(x,y,z)), normal(Vec3f(xn,yn,zn)), textureXY(Vec2f(0,0))
		{}
		Vertex_tmp(GLfloat x, GLfloat y, GLfloat z, GLfloat xn, GLfloat yn, GLfloat zn, GLfloat xt, GLfloat yt) :
		position(Vec3f(x,y,z)), normal(Vec3f(xn,yn,zn)), textureXY(Vec2f(xt,yt))
		{}
	} Vertex;
}

#endif
