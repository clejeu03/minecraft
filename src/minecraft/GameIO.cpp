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
		
		/* Reading the data file*/
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

	void GameIO::GenerateMap(size_t width, size_t height, size_t depth){
		m_map->Resize(width, height, depth);
		std::map<std::string,Cube*> dictionary = *m_gameObjects;
		
		for (size_t i = 0; i < depth; i++){
			for (size_t j = 1; j < width; j++){
				for (size_t k = 0; k < height; k++){
					m_map->Set(j,i,k,dictionary[std::string("RockCube")]);
				}
			}
		}
	}

	void GameIO::SaveMap(){
		/*Creating or overwriting backup file*/
		FILE* file;//use the C library "stdio" to write to the file cause rapidjson need a FILE* instead of a char*
		file = fopen ("data/autoMap.json", "w");
		if (file == NULL)
			std::cout << "Can't create backup file" << std::endl;
		else
		{
			size_t width = m_map->GetSizeW();
			size_t height = m_map->GetSizeH();
			size_t depth = m_map->GetSizeD();

			if(file){
			   	
				rapidjson::FileStream s(file);
				rapidjson::PrettyWriter<rapidjson::FileStream> writer(s);	
				writer.StartObject();

				writer.String("name");
				writer.String("autoMap");

				writer.String("width");
				writer.Uint(width);

				writer.String("height");
				writer.Uint(height);

				writer.String("depth");
				writer.Uint(depth);

				writer.String("cubes");
				writer.StartArray();
				for (size_t i = 0; i < depth+1; i++){
					writer.StartArray();
					for (size_t j = 0; j < width+1; j++){
						writer.StartArray();
						for (size_t k = 0; k < height+1; k++){
							writer.Uint(1);
						}
						writer.EndArray();
					}
					writer.EndArray();
				}
				writer.EndArray();

				writer.EndObject();
			}
		}
		fclose (file);

	}
}
