#include <cmath>
#include <vector>
#include <iostream>
#include "imac2gl3/shapes/common.hpp"
#include "imac2gl3/shapes/Sphere.hpp"

namespace imac2gl3 {

void Sphere::build(GLfloat r, GLsizei discLat, GLsizei discLong) {
    // Equation paramétrique en (r, phi, theta) de la sphère 
    // avec r >= 0, -PI / 2 <= theta <= PI / 2, 0 <= phi <= 2PI
    //
    // x(r, phi, theta) = r sin(phi) cos(theta)
    // y(r, phi, theta) = r sin(theta)
    // z(r, phi, theta) = r cos(phi) cos(theta)
    //
    // Discrétisation:
    // dPhi = 2PI / discLat, dTheta = PI / discLong
    //
    // x(r, i, j) = r * sin(i * dPhi) * cos(-PI / 2 + j * dTheta)
    // y(r, i, j) = r * sin(-PI / 2 + j * dTheta)
    // z(r, i, j) = r * cos(i * dPhi) * cos(-PI / 2 + j * dTheta)

    GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
    GLfloat dPhi = 2 * PI * rcpLat, dTheta = PI * rcpLong;
    
    std::vector<ShapeVertex> data;
    
    // Construit l'ensemble des vertex
    for(GLsizei j = 0; j <= discLong; ++j) {
        GLfloat cosTheta = cos(-PI / 2 + j * dTheta);
        GLfloat sinTheta = sin(-PI / 2 + j * dTheta);
        
        for(GLsizei i = 0; i <= discLat; ++i) {
            ShapeVertex vertex;
            
            vertex.texCoords.x = i * rcpLat;
            vertex.texCoords.y = 1.f - j * rcpLong;

            vertex.normal.x = sin(i * dPhi) * cosTheta;
            vertex.normal.y = sinTheta;
            vertex.normal.z = cos(i * dPhi) * cosTheta;
            
            vertex.position = r * vertex.normal;
            
            data.push_back(vertex);
        }
    }

    m_nVertexCount = discLat * discLong * 6;
    m_pDataPointer = new ShapeVertex[m_nVertexCount];
    
    GLuint idx = 0;
    // Construit les vertex finaux en regroupant les données en triangles:
    // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
    // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
    // avec i sur la bande correspondant à la longitude
    for(GLsizei j = 0; j < discLong; ++j) {
        GLsizei offset = j * (discLat + 1);
        for(GLsizei i = 0; i < discLat; ++i) {
            m_pDataPointer[idx] = data[offset + i];
            idx++;
            m_pDataPointer[idx] = data[offset + (i + 1)];
            idx++;
            m_pDataPointer[idx] = data[offset + discLat + 1 + (i + 1)];
            idx++;
            
            m_pDataPointer[idx] = data[offset + i];
            idx++;
            m_pDataPointer[idx] = data[offset + discLat + 1 + (i + 1)];
            idx++;
            m_pDataPointer[idx] = data[offset + i + discLat + 1];
            idx++;
        }
    }
    
    // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
    // par un Index Buffer Object, que nous verrons dans les prochains TDs
}

}
