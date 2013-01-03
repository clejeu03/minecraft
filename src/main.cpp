/* Standard */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
/* SDL & GL */
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>
/* Home-baked */
#include <minecraft/GraphicEngine.hpp>
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
    minecraft::Character player;
    minecraft::Map map;
    
	minecraft::GraphicEngine graphicEng;
	graphicEng.StartGL();
	graphicEng.Initialize(WINDOW_WIDTH,WINDOW_HEIGHT);
	graphicEng.SetCharacter(&player);
	graphicEng.SetMap(&map);
	
	minecraft::GameIO IOManager((char*)"bla bla position de ma map");
	IOManager.SetCharacter(&player);
	IOManager.SetMap(&map);
	IOManager.SetGameObjects(graphicEng.GetGameObjects());
	IOManager.LoadMap();
     
    /// RENDERING LOOP
    bool done = false;
    /*Keys pressed*/
	bool keyZ=0;
	bool keyQ=0;
	bool keyS=0;
	bool keyD=0;
    
    while(!done) {
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
            
            // Player inputs
			if(SDL_GetMouseState(NULL, NULL)) {
				if(e.type == SDL_MOUSEMOTION) {
					player.RotateLeft(-e.motion.xrel);
					player.LookUp(-e.motion.yrel);
				}
			}
			
			/* Move player */
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

		    	

		/*if(e.type ==  SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_WHEELUP) {
				player.MoveFront(0.1);
			}
			if(e.type ==  SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_WHEELDOWN) {
				player.MoveFront(-0.1);
			}*/
		}
		
		/* Acutally move the player */
		if(keyZ==1){player.MoveFront(0.0001);}
    	if(keyQ==1){player.MoveLeft(0.0001);}
    	if(keyS==1){player.MoveFront(-0.0001);}
    	if(keyD==1){player.MoveLeft(-0.0001);}

    }
    
	/// QUIT AND CLEAN (ALL IS AUTOMATIC BY NOW, MAYBE LATER)
    SDL_Quit();

	return EXIT_SUCCESS;
}
