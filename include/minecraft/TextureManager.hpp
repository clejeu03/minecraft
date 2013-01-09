#ifndef _MINECRAFT_TEXTUREMANAGER_HPP_
#define _MINECRAFT_TEXTUREMANAGER_HPP_

#include <string>
#include <map>
#include <stdexcept>
#include <GL/glew.h>
#include <SDL/SDL_image.h>

namespace minecraft {
	/* Manage the textures into the hardware */
	class TextureManager {
		private:
			std::map<std::string,GLuint> m_textureIds;
		public:
			~TextureManager();
			void LoadTexture(const char*, const char*) throw(std::runtime_error);
			GLuint GetTextureId(const char*) throw(std::invalid_argument);
	};
}

#endif
