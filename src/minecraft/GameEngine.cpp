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
		if (velocity>0.22){
			if(!scream.playing()){
				scream.play();
			}
		}
		if (velocity>0.3){
			m_character->setPosition(glm::vec3(1.8,3.5,1.8));
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
				}else{
					buildCube.play();
				}
				
			}else if (mode==0){			
				AddInInventory(GetCubeType(currentPosition.x, currentPosition.y, currentPosition.z));
				m_world->DelByPixel(currentPosition.x,currentPosition.y,currentPosition.z);
				breakCube.play();

			}
		}
		return 1;
	}

	std::string GameEngine::GetCubeType(GLfloat x,GLfloat y,GLfloat z)throw(std::invalid_argument){
		std::string type = "notype";
		Cube* tmp = m_world->GetForType(x,y,z);
		if(tmp == (*m_gameObjects)[std::string("RockCube")]){
			type = "RockCube";
		}
		else if(tmp == (*m_gameObjects)[std::string("CloudCube")]){
			type = "CloudCube";
		}
		return type;
	}

	void GameEngine::AddInInventory(std::string cubeType) throw(std::invalid_argument){
		if (cubeType.empty()==true)
			throw std::invalid_argument("Inventory : Non recognized type of cube");

		/*If there's not corresponding cube	*/	
		if(m_inventory.find(cubeType) == m_inventory.end()){
			m_inventory.insert ( std::pair<std::string,int>(cubeType,1) );
			std::cout << m_inventory.begin()->first << m_inventory.begin()->second << std::endl;
		}
		/*If there is already the same type of cube */
		else{
			m_inventory.find(cubeType)->second ++;
			std::cout << m_inventory.find(cubeType)->second << std::endl;
		}
	}

	void Inventory::RemoveFromInventory(std::string cubeType) throw(std::invalid_argument){

		if(m_inventory.find(cubeType) == m_inventory.end()){
			throw std::invalid_argument("Your inventory doesn't contain this sort of cube");
		}
		/*Case there are many elements in the inventory*/
		else if(m_inventory.find(cubeType)->second != 1 ){
			m_inventory.find(cubeType)->second --;	

		/*Case it's the last one of this type*/
		}else{
			m_inventory.erase(m_inventory.find(CubeType));
		}
	}

	void GameEngine::InitializeSound(){
		// Load sounds
		steps.load(1,"data/sounds/steps.ogg");
		buildCube.load(2,"data/sounds/build.ogg");
		breakCube.load(3,"data/sounds/break.wav");
		scream.load(4,"data/sounds/scream.wav");
	}
	
	void GameEngine::walkSound(){
		if (!steps.playing()){
			steps.play(1);//loop
		}
	}
	
	void GameEngine::walkSoundStop(){
		steps.stop();
	}


}
