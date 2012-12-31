#include <minecraft/GameIO.hpp>
#include <minecraft/shader_tools.hpp>
#include <iostream>
#include <fstream>
#include <string>
/*Parser JSON*/
#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h" // wrapper of C stream for prettywriter as output

namespace minecraft {
	void GameIO::LoadMap() throw(std::logic_error) {
		if( NULL == m_gameObjects || NULL == m_file )
			throw std::logic_error("Can't load map without game objects dictionary");
		
		/* Reading of the data file*/
    	std::ifstream file(m_file, std::ios::in);
    	size_t width;
		size_t height;
		size_t depth;
    	if (file) {
   			std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    		/*Parsing*/
    		rapidjson::Document document;
 			char* buffer = new char[json.size()+1];
			memcpy(buffer, json.c_str(), json.size()+1);
			if (document.ParseInsitu<0>(buffer).HasParseError()){
				std::cout << "can't parse the map file : " << document.ParseInsitu<0>(buffer).GetParseError() << std::endl;
			}else{
				std::cout << " Parsing to document succeeded. " << std::endl;
				
				printf("\nMap specifications:\n");
				assert(document.IsObject());

				assert(document.HasMember("name"));
				assert(document["name"].IsString());
				std::cout << " name = " << document["name"].GetString() << std::endl;

				assert(document["width"].IsNumber());
				assert(document["width"].IsInt());
				width = document["width"].GetInt();
				std::cout << " width = " << document["width"].GetInt() << std::endl;

				assert(document["height"].IsNumber());
				assert(document["height"].IsInt());
				height = document["height"].GetInt();
				std::cout << " height = " << document["height"].GetInt() << std::endl;

				assert(document["depth"].IsNumber());
				assert(document["depth"].IsInt());
				depth = document["depth"].GetInt();
				std::cout << " depth= " << document["depth"].GetInt() << std::endl;

				/*Generating the map*/
 				m_map->Resize(width, height, depth);
 				std::map<std::string,Cube*> dictionary = *m_gameObjects;

				const rapidjson::Value& cubes = document["cubes"];	// Using a reference
				assert(cubes.IsArray());
				for (rapidjson::SizeType i = 0; i < depth; i++){	// rapidjson uses SizeType instead of size_t.
					for (rapidjson::SizeType j = 1; j < width; j++){
						for (rapidjson::SizeType k = 0; k < height; k++){
							switch (cubes[i][j][k].GetInt()){
								case 0 :
									break;
								case 1 :
									m_map->Set(j,i,k,dictionary[std::string("RockCube")]);
									break;
								case 2 :
									m_map->Set(j,i,k,dictionary[std::string("CloudCube")]);
									break;
							}
						}
					}
				}
			}
    	}else{
    		std::cerr << "can't open the data file" << std::endl;
    	}

	}
}
