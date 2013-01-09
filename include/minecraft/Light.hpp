#ifndef _MINECRAFT_LIGHT_HPP_
#define _MINECRAFT_LIGHT_HPP_

#include <glm/glm.hpp>

namespace minecraft {
	
	struct DirectionalLight 
	{ 
	   glm::vec3 direction; 
	   float intensity; 
	   float ambient; 
	}; 
	
	struct PointLight 
	{ 
	   glm::vec3 color; 
	   glm::vec3 position;
	   float constantAttenuation;
	   float linearAttenuation;
	   float quadraticAttenuation;
	}; 

}

#endif



