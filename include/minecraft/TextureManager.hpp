#ifndef _MINECRAFT_TEXTUREMANAGER_HPP_
#define _MINECRAFT_TEXTUREMANAGER_HPP_

#include <map>
#include <stdexcept>
#include <GL/glew.h>
#include <SDL/SDL_image.h>

namespace minecraft {
	class TextureManager {
		private:
			std::map<char*,GLuint> m_textureIds;
		public:
			~TextureManager();
			void LoadTexture(char*,char*) throw(std::runtime_error);
			GLuint GetTextureId(char*) throw(std::invalid_argument);
	};
}

#endif
