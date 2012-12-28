#include <minecraft/TextureManager.hpp>
#include <string>

namespace minecraft {
	TextureManager::~TextureManager() {
		typedef std::map<char*,GLuint>::iterator ItType;
		for(ItType iterator = m_textureIds.begin(); iterator != m_textureIds.end(); iterator++) {
			glDeleteTextures(1, &(iterator->second));
		}
	}
	
	void TextureManager::LoadTexture(char* gameObject, char* path) throw(std::runtime_error) {
		// Loading
		SDL_Surface* image = IMG_Load(path);
		if(!image)
			throw std::runtime_error(std::string("Can't load image :") + IMG_GetError());
		
		// Format
		GLenum imageFormat;
		switch( image->format->BytesPerPixel ) {
			case 1:
				imageFormat = GL_RED;
			break;
			case 3:
				imageFormat = GL_RGB;
			break;
			case 4:
				imageFormat = GL_RGBA;
			break;
			default:
				throw std::runtime_error("Image format not recognized");
			break;
		}
		
		// Uploading into hardware
		GLuint texture;
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			image->w,
			image->h,
			0,
			imageFormat,
			GL_UNSIGNED_BYTE,
			image->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D,0);
		SDL_FreeSurface(image);
		
		// Deleting the old texture for this game object
		if( m_textureIds.find(gameObject) != m_textureIds.end() )
			glDeleteTextures(1, &(m_textureIds[gameObject]));
		
		// Save the texture id
		m_textureIds[gameObject] = texture;
	}
	
	GLuint TextureManager::GetTextureId(char* gameObject) throw(std::invalid_argument) {
		if( m_textureIds.find(gameObject) == m_textureIds.end() )
			throw std::invalid_argument(std::string("No texture for ") + gameObject);
			
		return m_textureIds[gameObject];
	}
}
