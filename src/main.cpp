/* Standard */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cmath>
/* SDL & GL */
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
/*Parser Json*/
#include "rapidjson/document.h"
/* Home-baked */
#include <minecraft/GraphicEngine.hpp>
#include <minecraft/GameEngine.hpp>
#include <minecraft/GameIO.hpp>

/* GAME PARAMETERS */
static const size_t WINDOW_WIDTH = 512, WINDOW_HEIGHT = 512;
static const size_t BYTES_PER_PIXEL = 32;



int main(int argc, char* argv[]) {
	/// INITIALIZATION
	// SDL
	SDL_Init(SDL_INIT_VIDEO);
	
	// Window and GL context
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BYTES_PER_PIXEL, SDL_OPENGL);
	
	// GLEW
	GLenum error;
	if(GLEW_OK != (error = glewInit())) {
		std::cerr << "Impossible d'initialiser GLEW: " << glewGetErrorString(error) << std::endl;
		return EXIT_FAILURE;
	}
	
    /// CREATION OF THE RESSOURCES
    minecraft::Character player(glm::vec3(1,1.9,1));
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

	/*Start a new Map*/
	minecraft::GameIO IOManager;
	IOManager.SetCharacter(&player);
	IOManager.SetMap(&map);
	IOManager.SetGameObjects(graphicEng.GetGameObjects());
    IOManager.GenerateMap(30);
    IOManager.SaveMap();
    
    minecraft::GameEngine gameEng;
    gameEng.SetCharacter(&player);
	gameEng.SetMap(&map);
    
     // Hide Cursor
	SDL_ShowCursor(SDL_DISABLE);
	// Prevent from leaving the screen
	SDL_WM_GrabInput(SDL_GRAB_ON);
    
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
    while(!done) {
        // Clean the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Drawing
        graphicEng.RefreshDisplay();

        // Refresh the display
        SDL_GL_SwapBuffers();
        
        
        
        // Events handling
        SDL_Event e;
        
        // Mouse inputs
			if(SDL_GetMouseState(NULL, NULL)) {
				
		}
        
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
		if(keyZ && keyQ){player.MoveFront(diagSpeed);player.MoveLeft(diagSpeed);}
		else if(keyZ && keyD){player.MoveFront(diagSpeed);player.MoveLeft(-diagSpeed);}
		else if(keyS && keyQ){player.MoveFront(-diagSpeed);player.MoveLeft(diagSpeed);}
		else if(keyS && keyD){player.MoveFront(-diagSpeed);player.MoveLeft(-diagSpeed);}
		else if(keyZ==1){player.MoveFront(speed);}
    	else if(keyQ==1){player.MoveLeft(speed);}
    	else if(keyS==1){player.MoveFront(-speed);}
    	else if(keyD==1){player.MoveLeft(-speed);}
    	
    	// Collider test
    	std::cout<< gameEng.collide()<<std::endl;

    }
    
	/// QUIT AND CLEAN (ALL IS AUTOMATIC BY NOW, MAYBE LATER)
    SDL_Quit();

	return EXIT_SUCCESS;
}
