#ifndef _IMAC2GL3_SHAPES_COMMON_HPP_
#define _IMAC2GL3_SHAPES_COMMON_HPP_

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace imac2gl3 {

static const GLfloat PI = 3.14159265358979323846;

struct ShapeVertex {
    glm::vec3 position, normal;
    glm::vec2 texCoords;
};

}

#endif
