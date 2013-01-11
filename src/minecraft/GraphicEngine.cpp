#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <minecraft/shader_tools.hpp>
#include <minecraft/GraphicEngine.hpp>
#include <minecraft/Light.hpp>
#include <iostream>

namespace minecraft {
	GraphicEngine::~GraphicEngine() {
		typedef std::map<std::string,Cube*>::iterator ItType;
		for(ItType iterator = m_gameObjects.begin(); iterator != m_gameObjects.end(); iterator++) {
			delete iterator->second;
		}
	}
	
	void GraphicEngine::StartGL() throw(std::runtime_error) {		
		// OpenGL features
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		// Shaders
		GLuint program = minecraft::loadProgram("shaders/transform.vs.glsl", "shaders/onlyCoords.fs.glsl");
		if(!program)
			throw std::runtime_error("Can't load shaders");
		glUseProgram(program);
		
		m_uniformTransformLocation = glGetUniformLocation(program,"uMVPMatrix");
		m_uniform2dMode = glGetUniformLocation(program,"u2dMode");
		m_uniformInstanciated = glGetUniformLocation(program,"uInstanciated");
		m_uniformLightening = glGetUniformLocation(program,"uLightening"); // Whether enlightment need to be processed
		glUniform1i(glGetUniformLocation(program, "uTexture"), 0);
		
		// Sun
		m_uniformSunDirection = glGetUniformLocation(program,"sunDirection");
		m_uniformSunAmbient = glGetUniformLocation(program,"sunAmbient");
		m_uniformSunIntensity = glGetUniformLocation(program,"sunIntensity");
		
		// PointLight
		m_uniformLightPosition = glGetUniformLocation(program,"lightPosition");
		m_uniformLightIntensity = glGetUniformLocation(program,"lightIntensity");
		
		// Texture
		glActiveTexture(GL_TEXTURE0);
	}
	
	void GraphicEngine::Initialize(size_t windowWidth, size_t windowHeight) {
		// Relative to the camera
		m_perspectiveMatrix = glm::perspective(70.f, windowWidth / (float) windowHeight, 0.0001f, 1000.f);
		
		// Create sunlight
		struct DirectionalLight sun;
		sun.direction=glm::vec3(0.2,-1,-0.5);
		sun.ambient=0.2;
		sun.intensity=1;
		// Uniform variables linked to the sun
		glUniform3f(m_uniformSunDirection, sun.direction.x, sun.direction.y, sun.direction.z);
		glUniform1f(m_uniformSunAmbient, sun.ambient);
		glUniform1f(m_uniformSunIntensity, sun.intensity);
		
		// Create point light
		struct PointLight light;
		light.position=glm::vec3(0,500,0);
		light.intensity=1;
		light.decay=glm::vec3(0.5,0.5,0.5); // Decay : constant,linear,quadratic
		// Uniform variables linked to the light
		glUniform3f(m_uniformLightPosition, light.position.x, light.position.y, light.position.z);
		glUniform1f(m_uniformLightIntensity, light.intensity);
		glUniform3f(m_uniformLightDecay, light.decay.x, light.decay.y, light.decay.z);
		
		// Init the game objects
		m_gameObjects[std::string("SkyBoxCube")] = new SkyBoxCube();
		m_gameObjects[std::string("CloudCube")] = new CloudCube();
		m_gameObjects[std::string("CrystalCube")] = new CrystalCube();
		m_gameObjects[std::string("RockCube")] = new RockCube();
		m_gameObjects[std::string("GrassCube")] = new GrassCube();
		m_gameObjects[std::string("DirtCube")] = new DirtCube();
		m_gameObjects[std::string("DiamondCube")] = new DiamondCube();
		m_gameObjects[std::string("GoldCube")] = new GoldCube();

		// Init and assign the shapes
		m_shapeMgr.LoadShapes();
		//---- instanciated rendering object
		m_gameObjects[std::string("SkyBoxCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("SkyBox")));
		m_gameObjects[std::string("SkyBoxCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("SkyBox")));
		m_gameObjects[std::string("CloudCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("CloudCube")));
		m_gameObjects[std::string("CloudCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("CloudCube")));
		m_gameObjects[std::string("CrystalCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("CrystalCube")));
		m_gameObjects[std::string("CrystalCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("CrystalCube")));
		m_gameObjects[std::string("RockCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("RockCube")));
		m_gameObjects[std::string("RockCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("RockCube")));
		m_gameObjects[std::string("GrassCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("GrassCube")));
		m_gameObjects[std::string("GrassCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("GrassCube")));
		m_gameObjects[std::string("DirtCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("DirtCube")));
		m_gameObjects[std::string("DirtCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("DirtCube")));
		m_gameObjects[std::string("DiamondCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("DiamondCube")));
		m_gameObjects[std::string("DiamondCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("DiamondCube")));
		m_gameObjects[std::string("GoldCube")]->SetVAOId(m_shapeMgr.GetShapeVAO(std::string("GoldCube")));
		m_gameObjects[std::string("GoldCube")]->SetNbVertices(m_shapeMgr.GetShapeNbVertices(std::string("GoldCube")));

		//---- simple rendering
		m_shapeMgr.SetBuffer("Cursor");
		m_shapeMgr.SetBuffer("SkyBox");
		// Init and assign the textures
		m_textureMgr.LoadTexture("SkyBox","./skybox.jpg");
		m_textureMgr.LoadTexture("Cloud", "./data/textures/Cloud.jpg");
		m_textureMgr.LoadTexture("Crystal", "./data/textures/Cristal.jpg");
		m_textureMgr.LoadTexture("Rock", "./data/textures/Pierre1.jpg");
		m_textureMgr.LoadTexture("Grass", "./data/textures/herbe.jpg");
		m_textureMgr.LoadTexture("Dirt", "./data/textures/terre.jpg");
		m_textureMgr.LoadTexture("Diamond", "./data/textures/Cristal.jpg");
		m_textureMgr.LoadTexture("Gold", "./data/textures/Or.jpg");
		m_textureMgr.LoadTexture("Cursor","./cursor.png");
		m_gameObjects[std::string("SkyBoxCube")]->SetTexId(m_textureMgr.GetTextureId("SkyBox"));
		m_gameObjects[std::string("CloudCube")]->SetTexId(m_textureMgr.GetTextureId("Cloud"));
		m_gameObjects[std::string("CrystalCube")]->SetTexId(m_textureMgr.GetTextureId("Crystal"));
		m_gameObjects[std::string("RockCube")]->SetTexId(m_textureMgr.GetTextureId("Rock"));
		m_gameObjects[std::string("GrassCube")]->SetTexId(m_textureMgr.GetTextureId("Grass"));
		m_gameObjects[std::string("DirtCube")]->SetTexId(m_textureMgr.GetTextureId("Dirt"));
		m_gameObjects[std::string("DiamondCube")]->SetTexId(m_textureMgr.GetTextureId("Diamond"));
		m_gameObjects[std::string("GoldCube")]->SetTexId(m_textureMgr.GetTextureId("Gold"));

		std::cout << "End init of graphicEngine" << std::endl;
	}
	
	void GraphicEngine::RefreshDisplay() throw(std::logic_error) {
		if( NULL == m_character || NULL == m_world )
			throw std::logic_error("Can't display game without setting the map and the character");
		
		if(m_world->CheckForRefresh()) {
			std::cout << "dans setup buffer" << std::endl;
			std::vector<MapCoords> cloudCubes = m_world->GetPositions("CloudCube");
			std::vector<MapCoords> crystalCubes = m_world->GetPositions("CrystalCube");
			std::vector<MapCoords> rockCubes = m_world->GetPositions("RockCube");
			std::vector<MapCoords> grassCubes = m_world->GetPositions("GrassCube");
			std::vector<MapCoords> dirtCubes = m_world->GetPositions("DirtCube");
			std::vector<MapCoords> diamondCubes = m_world->GetPositions("DiamondCube");
			std::vector<MapCoords> goldCubes = m_world->GetPositions("GoldCube");


			m_shapeMgr.SetInstanciatedBuffer("CloudCube", cloudCubes);
			m_shapeMgr.SetInstanciatedBuffer("CrystalCube", crystalCubes);
			m_shapeMgr.SetInstanciatedBuffer("RockCube", rockCubes);
			m_shapeMgr.SetInstanciatedBuffer("GrassCube", grassCubes);
			m_shapeMgr.SetInstanciatedBuffer("DirtCube", dirtCubes);
			m_shapeMgr.SetInstanciatedBuffer("DiamondCube", diamondCubes);
			m_shapeMgr.SetInstanciatedBuffer("GoldCube", goldCubes);

			m_world->GetInstanceDatas().push_back(std::make_tuple(
				m_gameObjects[std::string("CloudCube")]->GetVAOId(),
				m_gameObjects[std::string("CloudCube")]->GetTexId(),
				cloudCubes.size()
			));

			//std::cout << "CloudCube" << std::endl;

			m_world->GetInstanceDatas().push_back(std::make_tuple(
				m_gameObjects[std::string("CrystalCube")]->GetVAOId(),
				m_gameObjects[std::string("CrystalCube")]->GetTexId(),
				crystalCubes.size()
			));

			//std::cout << "CrystalCube" << std::endl;

			m_world->GetInstanceDatas().push_back(std::make_tuple(
				m_gameObjects[std::string("RockCube")]->GetVAOId(),
				m_gameObjects[std::string("RockCube")]->GetTexId(),
				rockCubes.size()
			));

			//std::cout << "RockCube" << std::endl;

			m_world->GetInstanceDatas().push_back(std::make_tuple(
				m_gameObjects[std::string("GrassCube")]->GetVAOId(),
				m_gameObjects[std::string("GrassCube")]->GetTexId(),
				grassCubes.size()
			));

			//std::cout << "GrassCube" << std::endl;

			m_world->GetInstanceDatas().push_back(std::make_tuple(
				m_gameObjects[std::string("DirtCube")]->GetVAOId(),
				m_gameObjects[std::string("DirtCube")]->GetTexId(),
				dirtCubes.size()
			));

			//std::cout << "DirtCube" << std::endl;

			m_world->GetInstanceDatas().push_back(std::make_tuple(
				m_gameObjects[std::string("DiamondCube")]->GetVAOId(),
				m_gameObjects[std::string("DiamondCube")]->GetTexId(),
				diamondCubes.size()
			));

			//std::cout << "DiamondCube" << std::endl;

			m_world->GetInstanceDatas().push_back(std::make_tuple(
				m_gameObjects[std::string("GoldCube")]->GetVAOId(),
				m_gameObjects[std::string("GoldCube")]->GetTexId(),
				goldCubes.size()
			));

			//std::cout << "GoldCube" << std::endl;

			//std::cout << "Apres setup buffer" << std::endl;
			//exit(EXIT_SUCCESS);
			m_world->SetRefresh(false);
		}
		
		m_transformStack.Push();
			m_transformStack.Set(m_perspectiveMatrix*m_character->GetPointOfView());
			DrawSkyBox();
			glUniform1i(m_uniformLightening, 1);
			m_world->Draw(m_transformStack,m_uniformTransformLocation);
		m_transformStack.Pop();
		DrawCursor();
		DrawInventory();
	}
	
	void GraphicEngine::DrawCursor() {
		glUniform1i(m_uniform2dMode, 1); // Tell the shader it's 2D
		glUniform1i(m_uniformLightening, 0);
		
		glBindTexture(GL_TEXTURE_2D,m_textureMgr.GetTextureId("Cursor"));
		glBindVertexArray(m_shapeMgr.GetShapeVAO(std::string("Cursor")));
		glDrawArrays(GL_TRIANGLES, 0, m_shapeMgr.GetShapeNbVertices(std::string("Cursor")));
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D,0);
		
		glUniform1i(m_uniformLightening, 1);
		glUniform1i(m_uniform2dMode, 0);
	}
	
	void GraphicEngine::DrawInventory() {
		/*
		 Ok, donc le principe en étapes pour dessiner un objet 2d:
		 1) Charger tes textures dans Initialize de ce fichier avec le texture manager,
		  tu verras que j'ai chargé "cursor". Ca gère la transparance également et tous les types d'images ^^
		 2) Faire comme dans DrawCursor() juste au dessus : dire au shader que c'est de la 2D,
		  activer le slot de texture 0, bind ta texture en la récupérant avec le texture manager,
		 puis récupère ton VAO qui pointe vers les points de ta forme. Par exemple pour un carré, il faut que tu ailles
		 dans le shapeManager, définisse un nouvel objet comme on l'a fait pour Cube et Cursor, avec les coordonnées.
		 Enfin voila quoi, après la ou ça va être plus hardos, c'est genre pour afficher le nombre de cubes par exemple
		 (je pense qu'on peut écrire avec openGL */
	}
	
	void GraphicEngine::DrawSkyBox() {
		SkyBoxCube* skyBox = (SkyBoxCube*)m_gameObjects[std::string("SkyBoxCube")];
		glm::vec3 cameraPos = m_character->HeadPosition();
		
		glUniform1i(m_uniformLightening, 0);
		glUniform1i(m_uniformInstanciated, 0);
		m_transformStack.Push();
			m_transformStack.Translate(cameraPos);
			m_transformStack.Scale(glm::vec3(std::max(m_world->GetSizeW(),std::max(m_world->GetSizeH(),m_world->GetSizeD()))*2));
			glUniformMatrix4fv(m_uniformTransformLocation, 1, GL_FALSE, glm::value_ptr(m_transformStack.Top()));
			skyBox->Draw();
		m_transformStack.Pop();
		glUniform1i(m_uniformInstanciated, 1);
		glUniform1i(m_uniformLightening, 1);
	}
}
