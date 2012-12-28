/* Standard */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
/* SDL & GL */
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>
/* Home-baked */
#include <minecraft/shader_tools.hpp>
#include <minecraft/GraphicEngine.hpp>

/* GAME PARAMETERS */
static const size_t WINDOW_WIDTH = 512, WINDOW_HEIGHT = 512;
static const size_t BYTES_PER_PIXEL = 32;

int main(int argc, char* argv[]) {
	/// Initialization
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
    
    // OpenGL features
    glEnable(GL_DEPTH_TEST);
    
    /// Creation of the ressources
	minecraft::GraphicEngine graphicEng;
	graphicEng.Initialize();
     
    /// RENDERING LOOP
    bool done = false;
    while(!done) {
        // Clean the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Drawing
        graphicEng.Refresh();

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
            
            // Traitement des autres évenements:
		}
    }
    
	/// CLEAN THE RESSOURCES
	
    SDL_Quit();
	
	return EXIT_SUCCESS;
}
