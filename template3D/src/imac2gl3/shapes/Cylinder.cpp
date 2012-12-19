#include <cmath>
#include <vector>
#include <iostream>
#include "imac2gl3/shapes/common.hpp"
#include "imac2gl3/shapes/Cylinder.hpp"

namespace imac2gl3 {

void Cylinder::build(GLfloat height, GLfloat r, GLsizei discLat, GLsizei discHeight) {
    // Equation paramétrique en (r, phi, h) du cylindre
    // avec r >= 0, -PI / 2 <= theta <= PI / 2, 0 <= h <= height
    //
    // x(r, phi, h) = r sin(phi)
    // y(r, phi, h) = h
    // z(r, phi, h) = r cos(phi)
    //
    // Discrétisation:
    // dPhi = 2PI / discLat, dH = height / discHeight
    //
    // x(r, i, j) = r * sin(i * dPhi)
    // y(r, i, j) = j * dH
    // z(r, i, j) = r * cos(i * dPhi)

    GLfloat rcpLat = 1.f / discLat, rcpH = 1.f / discHeight;
    GLfloat dPhi = 2 * PI * rcpLat, dH = height * rcpH;
    
    std::vector<ShapeVertex> data;
    
    // Construit l'ensemble des vertex
    for(GLsizei j = 0; j <= discHeight; ++j) {
        for(GLsizei i = 0; i < discLat; ++i) {
            ShapeVertex vertex;
            
            vertex.texCoords.x = i * rcpLat;
            vertex.texCoords.y = j * rcpH;
            
            vertex.normal.x = sin(i * dPhi);
            vertex.normal.y = 0;
            vertex.normal.z = cos(i * dPhi);
            
            vertex.position = r * vertex.normal;
            vertex.position.y = j * dH;
            
            data.push_back(vertex);
        }
    }

    m_nVertexCount = discLat * discHeight * 6;
    m_pDataPointer = new ShapeVertex[m_nVertexCount];
    
    GLuint idx = 0;
    // Construit les vertex finaux en regroupant les données en triangles:
    // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
    // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
    // avec i sur la bande correspondant à la longitude
    for(GLsizei j = 0; j < discHeight; ++j) {
        GLsizei offset = j * discLat;
        for(GLsizei i = 0; i < discLat; ++i) {
            m_pDataPointer[idx] = data[offset + i];
            idx++;
            m_pDataPointer[idx] = data[offset + (i + 1) % discLat];
            idx++;
            m_pDataPointer[idx] = data[offset + discLat + (i + 1) % discLat];
            idx++;
            
            m_pDataPointer[idx] = data[offset + i];
            idx++;
            m_pDataPointer[idx] = data[offset + discLat + (i + 1) % discLat];
            idx++;
            m_pDataPointer[idx] = data[offset + i + discLat];
            idx++;
        }
    }
    
    // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
    // par un Index Buffer Object, que nous verrons dans les prochains TDs
}

}

