#ifndef _IMAC2GL3_CYLINDER_HPP_
#define _IMAC2GL3_CYLINDER_HPP_

#include <GL/glew.h>

namespace imac2gl3 {
    
// Représente un cylindre ouvert discrétisé dont la base est centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Cylinder {
    static const GLint POSITION_NUM_COMPONENTS = 3;
    static const GLint NORMAL_NUM_COMPONENTS = 3;
    static const GLint TEXCOORDS_NUM_COMPONENTS = 2;
    
    static const GLsizei POSITION_OFFSET = 0;
    static const GLsizei NORMAL_OFFSET = POSITION_NUM_COMPONENTS * sizeof(GLfloat);
    static const GLsizei TEX_COORDS_OFFSET = (POSITION_NUM_COMPONENTS + NORMAL_NUM_COMPONENTS) * sizeof(GLfloat);
    
    static const GLsizei VERTEX_BYTE_SIZE = 
        (POSITION_NUM_COMPONENTS + NORMAL_NUM_COMPONENTS + TEXCOORDS_NUM_COMPONENTS) * sizeof(GLfloat);
        
    // Alloue et construit les données (implantation dans le .cpp)
    void build(GLfloat height, GLfloat radius, GLsizei discLat, GLsizei discHeight);
    
    // Pas de copie possible
    Cylinder(const Cylinder& c) {
    }
    
    Cylinder& operator =(const Cylinder& c) {
        return *this;
    }
public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Cylinder(GLfloat height, GLfloat radius, GLsizei discLat, GLsizei discHeight):
        m_pDataPointer(0), m_nVertexCount(0) {
        build(height, radius, discLat, discHeight); // Construction (voir le .cpp)
    }
    
    // Destructeur: désalloue le tableau de données
    ~Cylinder() {
        delete [] m_pDataPointer;
    }

    // Renvoit le pointeur vers les données
    const GLvoid* getDataPointer() const {
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

private:
    ShapeVertex* m_pDataPointer; // Pointeur vers les données du tableau
    GLsizei m_nVertexCount; // Nombre de sommets
};
    
}

#endif
