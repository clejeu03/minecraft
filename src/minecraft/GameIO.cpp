#include <minecraft/GameIO.hpp>
#include <minecraft/shader_tools.hpp>
#include <iostream>
#include <fstream>
#include <string>
/*Parser JSON*/
#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h" // wrapper of C stream for prettywriter as output


#define foreach_xyz(start, end) \
    int x, y, z;\
    float xf, yf, zf;\
    for(x=(start); x<(end); x++){\
        for(y=(start); y<(end); y++){\
            for(z=(start); z<(end); z++){\
                xf=(float)x/(float)size;\
                yf=(float)y/(float)size;\
                zf=(float)z/(float)size;

#define put(x, y, z, value)\
    data[\
        (x)+\
        (y)*size+\
        (z)*size*size\
    ] = value

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

	float grad[12][3] = {
    {1.0,1.0,0.0},{-1.0,1.0,0.0},{1.0,-1.0,0.0},{-1.0,-1.0,0.0},
    {1.0,0.0,1.0},{-1.0,0.0,1.0},{1.0,0.0,-1.0},{-1.0,0.0,-1.0},
    {0.0,1.0,1.0},{0.0,-1.0,1.0},{0.0,1.0,-1.0},{0.0,-1.0,-1.0}
	};

	int perm[512] = {151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180, 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180};

	float GameIO::dot(float x, float y, float z, float* g){
	    return x*g[0] + y*g[1] + z*g[2];
	}

	float GameIO::noise(float xin, float yin, float zin){
	    float F3, G3, t, X0, Y0, Z0, x0, y0, z0, s, x1, y1, z1, x2, y2, z2, x3, y3, z3, t0, t1, t2, t3, n0, n1, n2, n3;
	    int i, j, k, ii, jj, kk, i1, j1, k1, i2, j2, k2, gi0, gi1, gi2, gi3;
	    
	    F3 = 1.0/3.0;
	    s = (xin+yin+zin)*F3;
	    i = xin+s;
	    j = yin+s;
	    k = zin+s;
	    G3 = 1.0/6.0;
	    t = (i+j+k)*G3;
	    X0 = i-t;
	    Y0 = j-t;
	    Z0 = k-t;
	    x0 = xin-X0;
	    y0 = yin-Y0;
	    z0 = zin-Z0;
	    
	    if(x0 >= y0){
	        if(y0 >= z0){
	            i1=1; j1=0; k1=0; i2=1; j2=1; k2=0;
	        }
	        else if(x0 >= z0){
	             i1=1; j1=0; k1=0; i2=1; j2=0; k2=1;
	        }
	        else{
	            i1=0; j1=0; k1=1; i2=1; j2=0; k2=1;
	        }
	    }
	    else{
	        if(y0 < z0){
	            i1=0; j1=0; k1=1; i2=0; j2=1; k2=1;
	        }
	        else if(x0 < z0){ 
	            i1=0; j1=1; k1=0; i2=0; j2=1; k2=1;
	        }
	        else{
	            i1=0; j1=1; k1=0; i2=1; j2=1; k2=0;
	        }
	    }

	    x1 = x0 - i1 + G3;
	    y1 = y0 - j1 + G3;
	    z1 = z0 - k1 + G3;
	    x2 = x0 - i2 + 2.0*G3;
	    y2 = y0 - j2 + 2.0*G3;
	    z2 = z0 - k2 + 2.0*G3;
	    x3 = x0 - 1.0 + 3.0*G3;
	    y3 = y0 - 1.0 + 3.0*G3;
	    z3 = z0 - 1.0 + 3.0*G3;

	    ii = i & 255;
	    jj = j & 255;
	    kk = k & 255;
	    
	    gi0 = perm[ii+perm[jj+perm[kk]]] % 12;
	    gi1 = perm[ii+i1+perm[jj+j1+perm[kk+k1]]] % 12;
	    gi2 = perm[ii+i2+perm[jj+j2+perm[kk+k2]]] % 12;
	    gi3 = perm[ii+1+perm[jj+1+perm[kk+1]]] % 12;
	    
	    t0 = 0.6 - x0*x0 - y0*y0 - z0*z0;
	    if(t0<0){
	         n0 = 0.0;
	    }
	    else{
	        t0 *= t0;
	        n0 = t0 * t0 * dot(x0, y0, z0, grad[gi0]);
	    }

	    t1 = 0.6 - x1*x1 - y1*y1 - z1*z1;
	    if(t1<0){
	         n1 = 0.0;
	    }
	    else{
	        t1 *= t1;
	        n1 = t1 * t1 * dot(x1, y1, z1, grad[gi1]);
	    }

	    t2 = 0.6 - x2*x2 - y2*y2 - z2*z2;
	    if(t2<0){
	         n2 = 0.0;
	    }
	    else{
	        t2 *= t2;
	        n2 = t2 * t2 * dot(x2, y2, z2, grad[gi2]);
	    }

	    t3 = 0.6 - x3*x3 - y3*y3 - z3*z3;
	    if(t3<0){
	         n3 = 0.0;
	    }
	    else{
	        t3 *= t3;
	        n3 = t3 * t3 * dot(x3, y3, z3, grad[gi3]);
	    }

	    return 16.0*(n0 + n1 + n2 + n3)+1.0;
	}

	float GameIO::simplex_noise(int octaves, float x, float y, float z){
	    float value = 0.0;
	    int i;
	    for(i=0; i<octaves; i++){
	        value += GameIO::noise(
	            x*pow(2, i),
	            y*pow(2, i),
	            z*pow(2, i)
	        );
	    }

	    return value;
	}

	void GameIO::GenerateMap(size_t size){
		m_map->Resize(size, size, size);
		float caves, center_falloff, plateau_falloff, density;
	    foreach_xyz(1, size-1)
	        if(yf <= 0.8){
	            plateau_falloff = 1.0;
	        }
	        else if(0.8 < yf && yf < 0.9){
	            plateau_falloff = 1.0-(yf-0.8)*10.0;
	        }
	        else{
	            plateau_falloff = 0.0;
	        }
	        
	        center_falloff = 0.1/(
	            pow((xf-0.5)*1.5, 2) +
	            pow((yf-1.0)*0.8, 2) +
	            pow((zf-0.5)*1.5, 2)
	        );
	        caves = pow(simplex_noise(1, xf*5, yf*5, zf*5), 3);
	        density = (
	            simplex_noise(5, xf, yf*0.5, zf) *
	            center_falloff *
	            plateau_falloff
	        );
	        density *= pow(
	            noise((xf+1)*3.0, (yf+1)*3.0, (zf+1)*3.0)+0.4, 1.8
	        );
	        if(caves<0.5){
	            density = 0;
	        }
	        std::map<std::string,Cube*> dictionary = *m_gameObjects;
	        if(density >3.1) {m_map->Set(x,y,z,dictionary[std::string("RockCube")]);}
	    }}}
	    
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
							/*switch (cubeType){
								case NULL :
									writer.Uint(0);
									break;
								case RockCube :
									writer.Uint(1);
									break;
								case CloudCube :
									writer.Uint(2);
									break;
							}*/
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
