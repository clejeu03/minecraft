/* Standard */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>
/* SDL & GL */
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
/*Parser Json*/
#include "rapidjson/document.h"
/* Home-baked */
#include <minecraft/GraphicEngine.hpp>
#include <minecraft/GameEngine.hpp>
#include <minecraft/GameIO.hpp>
#include <minecraft/Sound.hpp>

#define FPS 1000/30 //Actually this is the number of milliseconds per frame
#define MAP_SIZE 100


/* GAME PARAMETERS */
static const size_t WINDOW_WIDTH = 512, WINDOW_HEIGHT = 512;
static const size_t BYTES_PER_PIXEL = 32;

glm::vec3 formerPosition;
bool formerBottomCollide=1;
bool currentBottomCollide=1;

float minFPS = 1000.0;
float maxFPS = 0.0;
float somme = 0.0;
float total = 0.0;

int main(int argc, char* argv[]) {
	/// INITIALIZATION
	// SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	// Initialize sound context
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
 
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		exit(1);
	}

	// Window and GL context
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BYTES_PER_PIXEL, SDL_OPENGL);
	
    // Hide Cursor
	SDL_ShowCursor(SDL_DISABLE);
	// Prevent from leaving the screen
	SDL_WM_GrabInput(SDL_GRAB_ON);
	
	// GLEW
	GLenum error;
	if(GLEW_OK != (error = glewInit())) {
		std::cerr << "Impossible d'initialiser GLEW: " << glewGetErrorString(error) << std::endl;
		return EXIT_FAILURE;
	}
	
    /// CREATION OF THE RESSOURCES
    minecraft::Character player(glm::vec3(MAP_SIZE/20,MAP_SIZE/10,MAP_SIZE/20));
    minecraft::Map map;
	
	minecraft::GraphicEngine graphicEng;
	graphicEng.StartGL();
	graphicEng.Initialize(WINDOW_WIDTH,WINDOW_HEIGHT);
	graphicEng.SetCharacter(&player);
	graphicEng.SetMap(&map);
	
	/*Load a Map*/
	/*minecraft::GameIO IOManager("data/myFirstIsland.json");
	IOManager.SetCharacter(&player);
	IOManager.SetMap(&map);
	IOManager.SetGameObjects(graphicEng.GetGameObjects());
	IOManager.LoadMap();*/
	
	std::cout<<"Génération de la carte..."<<std::endl;
	/*Start a new Map*/
	minecraft::GameIO IOManager;
	IOManager.SetCharacter(&player);
	IOManager.SetMap(&map);
	IOManager.SetGameObjects(graphicEng.GetGameObjects());
    //IOManager.GenerateMap(MAP_SIZE);
    //IOManager.SaveMap();
    IOManager.LoadMap("data/autoMap.json");
    
    minecraft::GameEngine gameEng;
    gameEng.SetCharacter(&player);
	gameEng.SetMap(&map);
	gameEng.InitializeSound();
    
    /*Keys pressed*/
	bool keyZ=0;
	bool keyQ=0;
	bool keyS=0;
	bool keyD=0;
	float speed=0.01;
	float diagSpeed=sqrt(speed*speed/2);
	
	// Display tips in the terminal
	std::cout<<"Press P to free the cursor and Escape to quit"<<std::endl;
	
    /// RENDERING LOOP
    bool done = false;
    
    Uint32 startTime, elapsedTime;

    while(!done) {
		// Allows to calculate the elapsed time in order to control the framerate - see the end of the loop
        startTime = SDL_GetTicks();
        
        // Clean the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Drawing
        graphicEng.RefreshDisplay();

        // Refresh the display
        SDL_GL_SwapBuffers();
        
        // Events handling
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            // Window close
            if(e.type == SDL_QUIT) {
                done = true;
                break;
            }
            
            if(e.type == SDL_MOUSEMOTION) {
					player.RotateLeft(-e.motion.xrel);
					player.LookUp(-e.motion.yrel);
			}
			
			if(e.type ==  SDL_MOUSEBUTTONDOWN){
				if(e.button.button==SDL_BUTTON_LEFT){
					//Delete
					gameEng.aimCube(0);
				}
				if(e.button.button==SDL_BUTTON_RIGHT){
					//Add
					gameEng.aimCube(1);
				}
			}
			
			/* Detect keys down */
			 if(e.type == SDL_KEYDOWN) {
			    	switch(e.key.keysym.sym) {
			    		case SDLK_z:
							keyZ=1;
			    			break;
			    		case SDLK_s:
			    			keyS=1;
			    			break;
			    		case SDLK_q:
			    			keyQ=1;
			    			break;
			    		case SDLK_d:
			    			keyD=1;
			    			break;
			    		case SDLK_SPACE:
			    			gameEng.jump();
			    			break;
						case SDLK_p:
							// Free the cursor
			    			SDL_WM_GrabInput(SDL_GRAB_OFF);
			    			SDL_ShowCursor(SDL_ENABLE);
			    			break;
			    		case SDLK_ESCAPE:
							// Free the cursor
			    			done=1;
			    			break;
			    		default:
			    			break;
			    	}

			    }
			
			if(e.type == SDL_KEYUP) {
			    	switch(e.key.keysym.sym) {
			    		case SDLK_z:
							keyZ=0;
			    			break;
			    		case SDLK_s:
			    			keyS=0;
			    			break;
			    		case SDLK_q:
			    			keyQ=0;
			    			break;
			    		case SDLK_d:
			    			keyD=0;
			    			break;
			    		default:
			    			break;
			    	}

			    }    

		}
		
		/* Acutally move the player */
		
		// Save former collide
		formerBottomCollide=currentBottomCollide;
		currentBottomCollide=gameEng.collideBottom();
		
		// Process gravity
		gameEng.processGravity(formerBottomCollide);
		
		// Save former position
		formerPosition = player.position();
		
		// Footsteps
		if(keyZ||keyQ||keyS||keyD){
			gameEng.walkSound();

		}else{
			gameEng.walkSoundStop();
		}
		
		//Move player
		if(keyZ && keyQ){player.MoveFront(diagSpeed);player.MoveLeft(diagSpeed);}
		else if(keyZ && keyD){player.MoveFront(diagSpeed);player.MoveLeft(-diagSpeed);}
		else if(keyS && keyQ){player.MoveFront(-diagSpeed);player.MoveLeft(diagSpeed);}
		else if(keyS && keyD){player.MoveFront(-diagSpeed);player.MoveLeft(-diagSpeed);}
		else if(keyZ==1){player.MoveFront(speed);}
		else if(keyQ==1){player.MoveLeft(speed);}
		else if(keyS==1){player.MoveFront(-speed);}
		else if(keyD==1){player.MoveLeft(-speed);}
		
		// Check for collision
		if (gameEng.collideSides()){
			// If the new position collides, go back
			player.setPosition(formerPosition);
		}
		
		// Calculate elapsed time
		elapsedTime = SDL_GetTicks() - startTime;
		// Framerate control : pause briefly the program if it's running too fast
		if(elapsedTime < FPS) {
			SDL_Delay(FPS - elapsedTime);
			//std::cout << "framerate : " << FPS << std::endl;
		}
		else {
			//std::cout << "framerate : " << 1000. / elapsedTime << std::endl;
		}	
		//printf("\033[2J");
    }
    
	/// QUIT AND CLEAN (ALL IS AUTOMATIC BY NOW, MAYBE LATER)
    SDL_Quit();

	return EXIT_SUCCESS;
}
