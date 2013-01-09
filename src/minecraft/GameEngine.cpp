#include <minecraft/GameEngine.hpp>
#include <iostream>

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
		if (velocity>0.3){
			m_character->setPosition(glm::vec3(1.8,3,1.8));
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
			if (mode==1){
				//One step back
				currentPosition-=step*directionVector;
				// Place the cube
				m_world->FakeCreation(currentPosition.x,currentPosition.y,currentPosition.z);
				
				//Deletes immediately if it collides
				if (collideSides()){
					m_world->DelByPixel(currentPosition.x,currentPosition.y,currentPosition.z);
				}
				
			}else if (mode==0){
				AddInInventory(m_world->GetByPixel(currentPosition.x,currentPosition.y,currentPosition.z));
				m_world->DelByPixel(currentPosition.x,currentPosition.y,currentPosition.z);
				
				
			}
		}
		return 1;
	}


}
