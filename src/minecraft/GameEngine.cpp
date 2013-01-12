#include <minecraft/GameEngine.hpp>
#include <iostream>
#include <minecraft/Sound.hpp>

namespace minecraft{
	
	GameEngine::GameEngine(){
		gravity=0.003;
		velocity=0;
	}
	
	
	
	bool GameEngine::collideBottom(){
		//For this version let's consider that the box's base is never bigger than a cube : 4 cubes to test only (vertices of the base square)
		glm::vec3 position=m_character->position();
		GLfloat width=m_character->getBox().getSize().x;
		GLfloat length=m_character->getBox().getSize().y;
		size_t count=0;
		
		count+=m_world->ExistsByPixel(position.x+width/2,position.y,position.z+length/2);
		count+=m_world->ExistsByPixel(position.x+width/2,position.y,position.z-length/2);
		count+=m_world->ExistsByPixel(position.x-width/2,position.y,position.z+length/2);
		count+=m_world->ExistsByPixel(position.x-width/2,position.y,position.z-length/2);
		
		if (count==0){
			return 0;
		}else{
			return 1;
		}
	}
	
	bool GameEngine::collideTop(){
		//For this version let's consider that the box's base is never bigger than a cube : 4 cubes to test only (vertices of the base square)
		glm::vec3 position=m_character->position()+glm::vec3(0,m_character->getBox().getSize().z,0);
		GLfloat width=m_character->getBox().getSize().x;
		GLfloat length=m_character->getBox().getSize().y;
		size_t count=0;
		
		count+=m_world->ExistsByPixel(position.x+width/2,position.y,position.z+length/2);
		count+=m_world->ExistsByPixel(position.x+width/2,position.y,position.z-length/2);
		count+=m_world->ExistsByPixel(position.x-width/2,position.y,position.z+length/2);
		count+=m_world->ExistsByPixel(position.x-width/2,position.y,position.z-length/2);

		if (count==0){
			return 0;
		}else{
			return 1;
		}
	}
	
	bool GameEngine::collideSides(){
		//For this version let's consider that the box's base is never bigger than a cube and never taller than 2 cubes : 8 cubes to test only (vertices of the base square)
		glm::vec3 position=m_character->position();
		GLfloat width=m_character->getBox().getSize().x;
		GLfloat length=m_character->getBox().getSize().y;
		size_t count=0;
		GLfloat cubeHeight=Cube::m_size;
		
		count+=m_world->ExistsByPixel(position.x+width/2,position.y+0.5*cubeHeight,position.z+length/2);
		count+=m_world->ExistsByPixel(position.x+width/2,position.y+0.5*cubeHeight,position.z-length/2);
		count+=m_world->ExistsByPixel(position.x-width/2,position.y+0.5*cubeHeight,position.z+length/2);
		count+=m_world->ExistsByPixel(position.x-width/2,position.y+0.5*cubeHeight,position.z-length/2);
		count+=m_world->ExistsByPixel(position.x+width/2,position.y+1.5*cubeHeight,position.z+length/2);
		count+=m_world->ExistsByPixel(position.x+width/2,position.y+1.5*cubeHeight,position.z-length/2);
		count+=m_world->ExistsByPixel(position.x-width/2,position.y+1.5*cubeHeight,position.z+length/2);
		count+=m_world->ExistsByPixel(position.x-width/2,position.y+1.5*cubeHeight,position.z-length/2);
	
		if (count==0){
			return 0;
		}else{
			return 1;
		}
		
	}
	
	void GameEngine::processGravity(bool formerCollide){
		if (collideBottom() && velocity>=0.0){
			if(formerCollide==0){
				velocity=0;
			}
		}
		else
		{
			velocity += gravity;
			m_character->setPosition(glm::vec3(m_character->position().x,m_character->position().y-velocity,m_character->position().z));
		}
		
		if(collideTop()){
			velocity=0;
		}
		
		if (velocity>0.22){
			if(!scream.playing()){
				scream.play();
			}
		}
		if (velocity>0.3){
			m_character->setPosition(glm::vec3(m_world->GetSizeW()/20,m_world->GetSizeH()/10-1,m_world->GetSizeD()/20));
			velocity=0;
		}
	}
	
	void GameEngine::jump(){
		if (collideBottom()){
			velocity = -0.03;
		}
	}
	
	bool GameEngine::aimCube(int mode){
		
		GLfloat step=0.00001;
		int found=0;
		GLfloat distance=0;
		GLfloat maxDistance=0.5;
		glm::vec3 directionVector=m_character->GetDirection();
		glm::vec3 currentPosition=m_character->HeadPosition();
		
		while (found==0){
			distance+=step;
			currentPosition+=step*directionVector;
			if (m_world->ExistsByPixel(currentPosition.x,currentPosition.y,currentPosition.z)){
				found=1;
			}
			if (distance>maxDistance){
				found=-1;
			}
		}
		if (found==1){
			if (mode==1){ // ADD
				//One step back
				currentPosition-=step*directionVector;
				// Place the cube
				m_world->FakeCreation(currentPosition.x,currentPosition.y,currentPosition.z);
				
				//Deletes immediately if it collides
				if (collideSides()){
					m_world->DelByPixel(currentPosition.x,currentPosition.y,currentPosition.z);
				}else{
					buildCube.play();
				}
				
			}else if (mode==0){ // DEL
				Cube* cube=m_world->GetByPixel(currentPosition.x,currentPosition.y,currentPosition.z);
				if (cube!=NULL){
					if(cube->GetBreakable()){
						std::cout<<cube->GetBreakable()<<std::endl;
						m_world->DelByPixel(currentPosition.x,currentPosition.y,currentPosition.z);
						breakCube.play();
					}
				}
			}
		}
		return 1;
	}

	void GameEngine::InitializeSound(){
		// Load sounds
		steps.load(1,"data/sounds/steps.ogg");
		buildCube.load(2,"data/sounds/build.ogg");
		breakCube.load(3,"data/sounds/break.wav");
		scream.load(4,"data/sounds/scream.wav");
		music.load(5,"data/sounds/music.ogg");
	}
	
	void GameEngine::ToggleMusic(){
		if(music.playing()){
			music.stop();
		}else{
			music.play(1);
		}
	}
	
	void GameEngine::WalkSound(){
		if (!steps.playing()){
			steps.play(1);//loop
		}
	}
	
	void GameEngine::WalkSoundStop(){
		steps.stop();
	}
}
