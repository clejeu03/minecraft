#include <minecraft/GameEngine.hpp>
#include <iostream>

namespace minecraft{
	
	GameEngine::GameEngine(){
		gravity=0.005;
		velocity=0;
	}
	
	bool GameEngine::collideBottom(){
		//For the first version let's consider that the box's base is never bigger than a cube : 4 cubes to test only (vertices of the base square)
		glm::vec3 position=m_character->position();
		GLfloat width=m_character->getBox().getSize().x;
		GLfloat length=m_character->getBox().getSize().y;
		size_t count=0;
		
		//std::cout<<m_world->ExistsByPixel(position.x+width/2,position.y,position.z+length/2)<<" ";
		//std::cout<<m_world->ExistsByPixel(position.x-width/2,position.y+length/2,position.z)<<" ";
		//std::cout<<m_world->ExistsByPixel(position.x+width/2,position.y-length/2,position.z)<<" ";
		//std::cout<<m_world->ExistsByPixel(position.x-width/2,position.y-length/2,position.z)<<" "<<std::endl;
		
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
		glm::vec3 position=m_character->position();
		//return m_world->ExistsByPixel(position.x,position.y,position.z);
		return 0;
	}
	
	void GameEngine::processGravity(){
		if (!collideBottom() || velocity<=0){
			std::cout<<"0"<<std::endl;
			velocity += gravity;
			m_character->setPosition(glm::vec3(m_character->position().x,m_character->position().y-velocity,m_character->position().z));
		}else{
			std::cout<<"1"<<std::endl;

		}
	}
	
	void GameEngine::jump(){
		if (collideBottom()){
					std::cout<<"jump !"<<std::endl;
			velocity = -0.05;
		}
	}


}
