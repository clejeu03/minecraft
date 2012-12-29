#include <minecraft/GraphicEngine.hpp>

namespace minecraft {
	void GraphicEngine::Initialize() {
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
		 m_world.Set(1,1,1,m_gameObjects[std::string("CloudCube")]);
	}
	
	void GraphicEngine::RefreshDisplay() {
		m_world.Draw();
	}
}
