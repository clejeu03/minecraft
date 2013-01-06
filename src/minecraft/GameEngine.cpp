#include <minecraft/GameEngine.hpp>
#include <iostream>

namespace minecraft{
	
	GameEngine::GameEngine(){
		gravity=0.005;
		velocity=0;
	}
	
	bool GameEngine::collide(){
		glm::vec3 position=m_character->position();
		//std::cout<<position.x<<" "<<position.y<<" "<<position.z<<" ";
		/*if(m_world->GetByPixel(position.x,position.y,position.z)==NULL){
			return 0;
		}else{
			return 1;
		}*/
		return m_world->ExistsByPixel(position.x,position.y,position.z);
	}
	
	void GameEngine::processGravity(){
		if (!collide() || velocity<=0){
			std::cout<<"0"<<std::endl;
			velocity += gravity;
			m_character->setPosition(glm::vec3(m_character->position().x,m_character->position().y-velocity,m_character->position().z));
		}else{
			std::cout<<"1"<<std::endl;
			//velocity=0;
		}
	}
	
	void GameEngine::jump(){
		if (collide()){
					std::cout<<"jump !"<<std::endl;
			velocity = -0.05;
		}
	}


}
