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
			std::cout<<"collide = 1"<<std::endl;
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
		
		
		/*std::cout<<" "<<m_world->ExistsByPixel(position.x+width/2,position.y+0.5*cube_height,position.z+length/2);
		std::cout<<" "<<m_world->ExistsByPixel(position.x+width/2,position.y+0.5*cube_height,position.z-length/2);
		std::cout<<" "<<m_world->ExistsByPixel(position.x-width/2,position.y+0.5*cube_height,position.z+length/2);
		std::cout<<" "<<m_world->ExistsByPixel(position.x-width/2,position.y+0.5*cube_height,position.z-length/2);
		std::cout<<" "<<m_world->ExistsByPixel(position.x+width/2,position.y+1.5*cube_height,position.z+length/2);
		std::cout<<" "<<m_world->ExistsByPixel(position.x+width/2,position.y+1.5*cube_height,position.z-length/2);
		std::cout<<" "<<m_world->ExistsByPixel(position.x-width/2,position.y+1.5*cube_height,position.z+length/2);
		std::cout<<" "<<m_world->ExistsByPixel(position.x-width/2,position.y+1.5*cube_height,position.z-length/2)<<std::endl;*/
	
		if (count==0){
			return 0;
		}else{
			return 1;
		}
		
	}
	
	void GameEngine::processGravity(){
		if (!collideBottom() || velocity<=0){
			velocity += gravity;
			m_character->setPosition(glm::vec3(m_character->position().x,m_character->position().y-velocity,m_character->position().z));
		}else{

		}
	}
	
	void GameEngine::jump(){
		if (collideBottom()){
					std::cout<<"jump !"<<std::endl;
			velocity = -0.04;
		}
	}


}
