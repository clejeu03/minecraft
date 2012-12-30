#include <glm/gtc/matrix_transform.hpp>
#include <minecraft/GraphicEngine.hpp>

namespace minecraft {
	void GraphicEngine::Initialize(GLuint uniformLocation, size_t windowWidth, size_t windowHeight) {
		// Relative to the camera
		m_uniformTransformLocation = uniformLocation;
		m_perspectiveMatrix = glm::perspective(50.f, windowWidth / (float) windowHeight, 0.1f, 1000.f);
		
		// Init the game objects
		m_gameObjects[std::string("CloudCube")] = new CloudCube();
		m_gameObjects[std::string("CrystalCube")] = new CrystalCube();
		m_gameObjects[std::string("RockCube")] = new RockCube();
		// Init and assign the shapes
		m_shapeMgr.LoadShapes();
		m_gameObjects[std::string("CloudCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("cube")));
		m_gameObjects[std::string("CloudCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("cube")));
		m_gameObjects[std::string("CrystalCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("cube")));
		m_gameObjects[std::string("CrystalCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("cube")));
		m_gameObjects[std::string("RockCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("cube")));
		m_gameObjects[std::string("RockCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("cube")));
		// Init and assign the textures
		/* EXAMPLE
		 * textureMgr.LoadTexture("Cloud","../blabal/illol.png");
		 * cloudCube.SetTexId(textureMgr.GetTextureId((char*)"Cloud"));*/
		m_world.Set(1,1,2,m_gameObjects[std::string("CloudCube")]);
		m_world.Set(0,0,5,m_gameObjects[std::string("CloudCube")]);
		m_world.Set(0,1,2,m_gameObjects[std::string("CloudCube")]);
		m_world.Set(1,2,5,m_gameObjects[std::string("CloudCube")]);
		m_world.Set(2,4,9,m_gameObjects[std::string("CloudCube")]);
		m_world.Set(25,0,5,m_gameObjects[std::string("CloudCube")]);
		m_world.Set(0,1,1,m_gameObjects[std::string("CloudCube")]);
		 
		 /* Just an example, the character must be managed and created by the game engine... */
		 m_character = new Character();
	}
	
	void GraphicEngine::RefreshDisplay() {
		m_transformStack.Push();
		m_transformStack.Set(m_perspectiveMatrix*m_character->GetPointOfView());
		m_world.Draw(m_transformStack,m_uniformTransformLocation);
		m_transformStack.Pop();
	}
}
