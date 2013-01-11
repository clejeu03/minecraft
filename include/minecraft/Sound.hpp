#ifndef _MINECRAFT_SOUND_HPP_
#define _MINECRAFT_SOUND_HPP_

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <cstdlib>
#include <string>

namespace minecraft {
	class Sound {
		private:
			Mix_Chunk *sound;
			int channel;
		public:
		
			Sound(){
				sound=NULL;
			}
			void load(int channelIndex, char* file){
				channel=channelIndex;
				sound = Mix_LoadWAV(file);
				if(sound == NULL) {
					std::cout<<"Unable to load file: %s\n"<< Mix_GetError()<<std::endl;
				}
			}
			
			void play(){	
				Mix_PlayChannel(channel, sound, 0);
			}
			
			void play(int loop){	 
				Mix_PlayChannel(channel, sound, -1);
			}
			
			void stop(){	 
				Mix_HaltChannel(channel);
			}
			
			bool playing(){
				return false;
				//return Mix_Playing(channel);
			}
			
			~Sound(){
				Mix_FreeChunk(sound);
				sound=NULL;
			}
	};
}

#endif
