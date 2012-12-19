#include <iostream>
#include <cstdlib>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imac2gl3/shapes/Sphere.hpp"
#include "imac2gl3/shapes/Plane.hpp"
#include "imac2gl3/shapes/GLShapeInstance.hpp"
#include "imac2gl3/shader_tools.hpp"
#include "imac2gl3/MatrixStack.hpp"
#include "imac2gl3/camera/TrackBallCamera.hpp"

static const size_t WINDOW_WIDTH = 512, WINDOW_HEIGHT = 512, BYTES_PER_PIXEL = 32;

#define NOMBRE_DE_PICS 100  

const GLvoid* bufferOffset(size_t offset) {
    return (const GLvoid*) offset;
}

int main(int argc, char** argv) {
    /********************************************************************
     * INITIALISATION DU PROGRAMME
     ********************************************************************/
    
    // Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // Creation de la fenêtre et d'un contexte OpenGL
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BYTES_PER_PIXEL, SDL_OPENGL);
    
    // Initialisation de GLEW
    GLenum error;
    if(GLEW_OK != (error = glewInit())) {
        std::cerr << "Impossible d'initialiser GLEW: " << glewGetErrorString(error) << std::endl;
        return EXIT_FAILURE;
    }

    GLShapeInstance Terre(imac2gl3::Sphere(1.f,50,50));
    GLShapeInstance Plan(imac2gl3::Plane(50.0f));
    TrackBallCamera camera;
    camera.moveFront(-5.f);

    float i=0.05;

    /* Chargement des shaders dans la variable "program" */
    GLuint program = imac2gl3::loadProgram("shaders/transform.vs.glsl", "shaders/normalcolor.fs.glsl");
    //GLuint program = imac2gl3::loadProgram("shaders/transform.vs.glsl", "shaders/normalcolor.fs.glsl");
    if(!program){
        return EXIT_FAILURE;
    }
    glUseProgram(program);
    //glUniform1i(glGetUniformLocation(program, "uTexture"), 0);

    // MVPMatrix est la matrice ModelViewProjection dans le vertex shader
    GLint MVPLocation = glGetUniformLocation(program, "uMVPMatrix");

    //Test de profondeur
        glEnable(GL_DEPTH_TEST);
    
        MatrixStack matrixStack;
        matrixStack.set(glm::perspective(70.f, WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 1000.f));
    
        int mouseX, mouseY;
        // Boucle principale
        bool done = false;
        while(!done) 
        {
            //i+=0.4;
            // Nettoyage de la fenêtre
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            matrixStack.push();
                matrixStack.mult(camera.getViewMatrix());
                 
                //Terre
                matrixStack.push();
                    //matrixStack.translate(glm::vec3(0, 0, -5));
                    matrixStack.rotate(45, glm::vec3(-1, 0, 0));
                    glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(matrixStack.top()));
                    
                    Terre.draw();
                    //Terre.draw();
                    
            
                matrixStack.pop();

            matrixStack.pop();
        
            
            // Mise à jour de l'affichage
            SDL_GL_SwapBuffers();
            
            // Boucle de gestion des évenements
            if(SDL_GetRelativeMouseState(&mouseX, &mouseY) & SDL_BUTTON(3))
            {
                camera.rotateLeft(0.1*mouseX);
                camera.rotateUp(0.1*mouseY);
                //std::cout << "mouseX = " << mouseX << std::endl << " mouseY = " << mouseY << std::endl;
                //camera.toString();
            }
            SDL_Event e;
            while(SDL_PollEvent(&e)) 
            {
                // Traitement de l'évenement fermeture de fenêtre
                if(e.type == SDL_QUIT) 
                {
                    done = true;
                    break;
                }
                if(e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case SDLK_z:
                            camera.moveFront(0.5);
                            break;
                        case SDLK_s:
                            camera.moveFront(-0.5);
                            break;
                        case SDLK_q:
                            camera.rotateLeft(0.5);
                            break;
                        case SDLK_d:
                            camera.rotateUp(-0.5);
                            break;
                        default:
                            break;
                    }

                }
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    // Traitement des autres évenements:
                    if (e.button.button == SDL_BUTTON_WHEELUP)
                    {
                        camera.moveFront(0.5);
                    }
                    if (e.button.button == SDL_BUTTON_WHEELDOWN)
                    {
                        camera.moveFront(-0.5);
                    }
                }
            }

        }
        
        // Destruction des ressources OpenGL
    SDL_Quit();
        
    return EXIT_SUCCESS;
}
