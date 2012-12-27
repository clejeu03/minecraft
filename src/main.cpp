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
#include <minecraft/Math.hpp>
#include <minecraft/Cube.hpp>
#include <minecraft/Map.hpp>

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
    
    /// Creation of the ressources
    minecraft::Map world(100,100,100);
    world.Set(2,2,2,new minecraft::CloudCube()); /* Must be cube pointer. Destruction is handled */
    world.Set(3,5,1,new minecraft::CrystalCube());
    
    world.Draw();
    
    /* Or to access (give a reference) : */
    world.Get(2,2,2).Draw();
    
    /// RENDERING LOOP
    bool done = false;
    while(!done) {
        // Clean the window
        glClear(GL_COLOR_BUFFER_BIT);

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
