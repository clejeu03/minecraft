#ifndef _IMAC2GL3_CUBE_HPP_
#define _IMAC2GL3_CUBE_HPP_

#include <GL/glew.h>

#include "common.hpp"

namespace imac2gl3 {
    
// Représente un cube discrétisé centré en (0, 0, 0) (dans son repère local)
	class Cube {

	    private :

	    static const GLint POSITION_NUM_COMPONENTS = 3; // nombre de composantes de l'attribut POSITION
	    static const GLint NORMAL_NUM_COMPONENTS = 3; // nombre de composantes de l'attribut NORMAL
	    static const GLint TEXCOORDS_NUM_COMPONENTS = 2; // nombre de composantes de l'attribut TEXCOORDS
	    static const GLint TOTAL_NUM_COMPONENTS = POSITION_NUM_COMPONENTS + NORMAL_NUM_COMPONENTS + TEXCOORDS_NUM_COMPONENTS;
	    
	    static const GLsizei POSITION_OFFSET = 0; // décalage dans le vertex pour accéder aux composantes de l'attribut POSITION
	    static const GLsizei NORMAL_OFFSET = POSITION_NUM_COMPONENTS * sizeof(GLfloat); // décalage dans le vertex pour accéder aux composantes de l'attribut NORMAL
	    static const GLsizei TEX_COORDS_OFFSET = (POSITION_NUM_COMPONENTS + NORMAL_NUM_COMPONENTS) * sizeof(GLfloat); // décalage dans le vertex pour accéder aux composantes de l'attribut TEXCOORD
	    
	    static const GLsizei VERTEX_BYTE_SIZE = 
		   (POSITION_NUM_COMPONENTS + NORMAL_NUM_COMPONENTS + TEXCOORDS_NUM_COMPONENTS) * sizeof(GLfloat); // taille en octet d'un vertex
		   
	    
	    void build(GLfloat size); // Construit les données (implantation dans le .cpp)
	    
	    Cube(const Cube& c) {} // Pas de copie possible
	    Cube& operator =(const Cube& c) {return *this;} // Pas de copie possible (bis)
	    
	    ShapeVertex m_pDataPointer[36]; // Tableau(pointeur) de vertex (pas d'allocation dynamique)
	    GLsizei m_nVertexCount; // Nombre de sommets
	    
	    public:
	    
	    // Constructeur: le nombre de vertex est de 36 (3 vertex par triangle & 2 triangles par face : 3*2*6 = 36 points)
	    Cube(GLfloat size): m_nVertexCount(36) {
		   build(size);
	    }
	    
	    // Destructeur: pas besoin de désallouer car il n'y a pas d'allocation (nombre de vertex connu : 36)
	    ~Cube() {}

	    // Renvoit le pointeur vers les données
	    const ShapeVertex* getDataPointer() const {
		   return m_pDataPointer;
	    }
	    
	    // Renvoit le nombre de vertex
	    GLsizei getVertexCount() const {
		   return m_nVertexCount;
	    }

	    // Renvoit la taille du tableau en octets
	    GLsizeiptr getByteSize() const {
		   return getVertexCount() * VERTEX_BYTE_SIZE; // Nombre de sommet * taille d'un sommet
	    }
	    
	    // Renvoit le nombre de composantes de l'attribut position
	    GLint getPositionNumComponents() const {
		   return POSITION_NUM_COMPONENTS;
	    }
	    
	    // Renvoit le nombre de composantes de l'attribut normale
	    GLint getNormalNumComponents() const {
		   return NORMAL_NUM_COMPONENTS;
	    }
	    
	    // Renvoit le nombre de composantes de l'attribut coordonnées de texture
	    GLint getTexCoordsNumComponents() const {
		   return TEXCOORDS_NUM_COMPONENTS;
	    }
	    
	    GLint getTotalComponents() const {
	        return TOTAL_NUM_COMPONENTS;
	    }
	    
	    // Renvoit la taille d'un vertex en octets
	    GLsizei getVertexByteSize() const {
		   return VERTEX_BYTE_SIZE;
	    }
	    
	    // Renvoit l'offset de l'attribut position
	    const GLvoid* getPositionOffset() const {
		   return reinterpret_cast<const GLvoid*>(POSITION_OFFSET);
	    }
	    
	    // Renvoit l'offset de l'attribut normale
	    const GLvoid* getNormalOffset() const {
		   return reinterpret_cast<const GLvoid*>(NORMAL_OFFSET);
	    }
	    
	    // Renvoit l'offset de l'attribut coordonnées de texture
	    const GLvoid* getTexCoordsOffset() const {
		   return reinterpret_cast<const GLvoid*>(TEX_COORDS_OFFSET);
	    }
	    
	    // Renvoit le type OpenGL d'une composante d'attribut
	    GLenum getDataType() const {
		   return GL_FLOAT;
	    }
	};
}

#endif
