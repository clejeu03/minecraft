#include <minecraft/GraphicEngine.hpp>
#include <iostream>

namespace minecraft {
	void GraphicEngine::Initialize() {
		// Init the game objects
		std::cout << "miaou 1" << std::endl;
		m_gameObjects[(char*)"CloudCube"] = new CloudCube();
		m_gameObjects[(char*)"CrystalCube"] = new CrystalCube();
		m_gameObjects[(char*)"RockCube"] = new RockCube();
		std::cout << "miaou 2" << std::endl;
		// Init and assign the shapes
		m_shapeMgr.LoadShapes();
		m_gameObjects[(char*)"CloudCube"]->SetVAOId(m_shapeMgr.GetShapeVAO((char*)"Cube"));
		m_gameObjects[(char*)"CrystalCube"]->SetVAOId(m_shapeMgr.GetShapeVAO((char*)"Cube"));
		m_gameObjects[(char*)"RockCube"]->SetVAOId(m_shapeMgr.GetShapeVAO((char*)"Cube"));
		std::cout << "miaou 3" << std::endl;
		// Init and assign the textures
		/* EXAMPLE
		 * textureMgr.LoadTexture("Cloud","../blabal/illol.png");
		 * cloudCube.SetTexId(textureMgr.GetTextureId((char*)"Cloud"));*/
		 std::cout << "miaou 4" << std::endl;
		 m_world.Set(1,1,1,m_gameObjects[(char*)"CloudCube"]);
	}
	
	void GraphicEngine::Refresh() {
		m_world.Draw();
	}
}
