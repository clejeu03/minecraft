#ifndef _MINECRAFT_SHADER_TOOLS_HPP_
#define _MINECRAFT_SHADER_TOOLS_HPP_

#include <GL/glew.h>

namespace minecraft {

/* Load, compile and link GLSL files given as parameters and return the compiled program's id */
GLuint loadProgram(const char* vertexShaderFile, const char* fragmentShaderFile);

}

#endif
