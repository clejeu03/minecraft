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
			void load(char* file){
				sound = Mix_LoadWAV(file);
				if(sound == NULL) {
					fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
				}
			}
			
			void play(){	
				channel = Mix_PlayChannel(-1, sound, 0);
				fprintf(stderr, "play ");

				if(channel == -1) {
					fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
				}
			}
			
			void play(int loop){	 
				channel = Mix_PlayChannel(-1, sound, -1);
				if(channel == -1) {
					fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
				}
			}
			
			void stop(){	 
				Mix_HaltChannel(channel);
				//fprintf(stderr, "stop\n");
			}
			
			bool playing(){
				return Mix_Playing(channel);
			}
			
			/*~Sound{
				Mix_FreeChunk(sound);
				sample=NULL;
			}*/
	};
}

#endif
