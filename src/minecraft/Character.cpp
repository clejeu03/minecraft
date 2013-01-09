#include <minecraft/Character.hpp>
#include <minecraft/GameEngine.hpp>

namespace minecraft {
	
	Character::Character(glm::vec3 position){
		povHeight=0.15;
		m_box.setBase(position);
		m_camera.setPosition(position+povHeight);
	}
	
	Box& Character::getBox(){
		// May want to shorten this
		Box& boxref=m_box;
		return boxref;
	}
	
	glm::vec3 Character::position(){
		return m_box.getBase();
	}
			
	void Character::setPosition(glm::vec3 position){
		m_box.setBase(position);
		m_camera.setPosition(glm::vec3 (position.x,position.y+povHeight,position.z));
	}
	
	void Character::setBoxSize(glm::vec3 size){
		m_box.setSize(size);
	}
	
	glm::vec3 Character::GetDirection(){
		return m_camera.GetDirection();
	}
	
	void Character::MoveFront(GLfloat distance) {
			m_camera.MoveFront(distance);
			m_box.setBase(glm::vec3 (m_camera.Position().x,m_camera.Position().y-povHeight,m_camera.Position().z));
	}
	
	void Character::MoveLeft(GLfloat distance) {
			m_camera.MoveLeft(distance);
			m_box.setBase(glm::vec3 (m_camera.Position().x,m_camera.Position().y-povHeight,m_camera.Position().z));
	}

	void Character::MoveVector(GLfloat distance, glm::vec3 vec) {
			m_camera.MoveVector(distance, vec);
			m_box.setBase(glm::vec3 (m_camera.Position().x,m_camera.Position().y-povHeight,m_camera.Position().z));
	}

	void Character::RotateLeft(GLfloat angle) {
		m_camera.RotateLeft(angle/2);
	}

	void Character::LookUp(GLfloat angle) {
		if(!(m_camera.GetDirection().y>0.99 && angle>0) && !(m_camera.GetDirection().y<(-0.99) && angle<0)){
			m_camera.RotateUp(angle/2);
		}
	}
		
	glm::mat4 Character::GetPointOfView() {
		return m_camera.GetViewMatrix();
	}
}
