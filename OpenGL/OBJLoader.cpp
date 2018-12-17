#include "OBJLoader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

Mesh* OBJLoader::LoadModel(const char* path)
{
	Mesh* mesh = new Mesh(); //New Mesh

	std::vector<Vector3> vertices; //Holds Vertice Data
	std::vector<TexCoord> textureCoords; //Holds Texture Coordinate Data
	std::vector<Vector3> normals; //Holds Normal Data

	std::vector<Vertex> vertexes; //Vector of every Vertex on the model
	std::map<std::tuple<GLushort, GLushort, GLushort>, GLushort> indices; //Map containing indices from OBJ file as well as a single indice for each vertex

	//Loads OBJ file from path
	std::ifstream file;
	file.open(path);
	if (!file.good())
	{
		std::cout << "Can't open texture file " << path << std::endl;
		return nullptr;
	}

	std::string text; //Holds the Text gathered from the file
	while (!file.eof())
	{
		file >> text;
		//If the current line in file contains Vertice Data
		if (text == "v")
		{
			//Read in each number on the line and puts in into a variable and then into the right vector
			Vector3 vertice;
			file >> vertice.X;
			file >> vertice.Y;
			file >> vertice.Z;

			vertices.push_back(vertice);
		}

		//If the current line in file contains Texture Coordinate Data
		if (text == "vt")
		{
			mesh->hasTexCoords = true; //Says if the Model has Texture Coordinates

			//Read in each number on the line and puts in into a variable and then into the right vector
			TexCoord texCoord;
			file >> texCoord.U;
			file >> texCoord.V;

			textureCoords.push_back(texCoord);
		}

		//If the current line in file contains Normal Data
		if(text == "vn")
		{
			mesh->hasNormals = true; //Says if the Model has Normals

			//Read in each number on the line and puts in into a variable and then into the right vector
			Vector3 normal;
			file >> normal.X;
			file >> normal.Y;
			file >> normal.Z;

			normals.push_back(normal);
		}

		//If the current line in file contains Indice Data
		if (text == "f")
		{
			//Strings that hold the 3 sets of indices on each line
			std::string vertex1;
			std::string vertex2;
			std::string vertex3;

			//Strings that hold the individual indices for the vertices, texture coordinates and normals
			std::string vertexString;
			std::string texCoordString;
			std::string normalString;

			Vertex mainVertex; //Holds indice data for each Vertex

			//Checks if the Model has both Texture Coordinates and not Normals
			//Then does appropriate code for just the Vertices and Texture Coordinate indices
			if (mesh->hasTexCoords && !mesh->hasNormals) 
			{
				file >> vertex1;
				file >> vertex2;

				//Seperates the numbers by /
				std::stringstream ss(vertex1);
				std::getline(ss, vertexString, '/');
				std::getline(ss, texCoordString);
				
				//Converts the strings holding the indice data to integers and assigns the appropriate vertex indice data to the appropriate variables in the vertex variable
				mainVertex.vertice = std::stoi(vertexString);
				mainVertex.texCoord = std::stoi(texCoordString);
				mainVertex.normal = 0;

				vertexes.push_back(mainVertex); //Adds the Vertex to the Vertex Vector

				//Does the exact thing for the next set of 2 indices
				ss.str("");
				ss.clear();
				ss << vertex2;
				std::getline(ss, vertexString, '/');
				std::getline(ss, texCoordString);

				mainVertex.vertice = std::stoi(vertexString);
				mainVertex.texCoord = std::stoi(texCoordString);
				mainVertex.normal = 0;

				vertexes.push_back(mainVertex); //Adds the Vertex to the Vertex Vector
			}
			else if(mesh->hasTexCoords && mesh->hasNormals)
			{
				file >> vertex1;
				file >> vertex2;
				file >> vertex3;

				//Seperates the numbers by /
				std::stringstream ss(vertex1);
				std::getline(ss, vertexString, '/');
				std::getline(ss, texCoordString, '/');
				std::getline(ss, normalString);

				//Converts the strings holding the indice data to integers and assigns the appropriate vertex indice data to the appropriate variables in the vertex variable
				mainVertex.vertice = std::stoi(vertexString);
				mainVertex.texCoord = std::stoi(texCoordString);
				mainVertex.normal = std::stoi(normalString);

				vertexes.push_back(mainVertex); //Adds the Vertex to the Vertex Vector

				//Does the exact thing for the next set of 3 indices
				ss.str("");
				ss.clear();
				ss << vertex2;
				std::getline(ss, vertexString, '/');
				std::getline(ss, texCoordString, '/');
				std::getline(ss, normalString);

				mainVertex.vertice = std::stoi(vertexString);
				mainVertex.texCoord = std::stoi(texCoordString);
				mainVertex.normal = std::stoi(normalString);

				vertexes.push_back(mainVertex); //Adds the Vertex to the Vertex Vector

				//Finally does the thing for the last set of 3 indices
				ss.str("");
				ss.clear();
				ss << vertex3;
				std::getline(ss, vertexString, '/');
				std::getline(ss, texCoordString, '/');
				std::getline(ss, normalString);

				mainVertex.vertice = std::stoi(vertexString);
				mainVertex.texCoord = std::stoi(texCoordString);
				mainVertex.normal = std::stoi(normalString);

				vertexes.push_back(mainVertex); //Adds the Vertex to the Vertex Vector
			}
		}
	}

	file.close(); //Closes File

	mesh->indiceCount = vertexes.size();
	mesh->indices = new GLushort[mesh->indiceCount]; //Creates array of shorts
	int indexNumber = 0; //Indice Number

	//For Loop goes through each vertex put into the vertex vector
	for (int i = 0; i < mesh->indiceCount; i++)
	{
		Vertex vertex = vertexes[i]; //Gets Vertex
		std::tuple<GLushort, GLushort, GLushort> indice = std::make_tuple(vertex.vertice, vertex.texCoord, vertex.normal); //Create map element using Vertex indice data

		std::map<std::tuple<GLushort, GLushort, GLushort>, GLushort>::iterator it; //Map Iterator to search through the map

		it = indices.find(indice); //Searches through the indices map to find a indice exactly the same as the speicifed indice from the vertex data
		if (it != indices.end())
		{
			//If a same vertex is found in the vertexes vector then add that Vertexes indice (The key in the map) to the indices array
			mesh->indices[i] = it->second; 
			continue; //Contuines the for loop
		}

		//Inserts new vertex if not found in the indices map already into the map using the vertex data from the vertexes vector
		//The added vertexes key is specified by the indexNumber variable. The indice number specified by indexNumber is then added to the indices array
		//And then incremented by one for the next unique vetex not found in the map
		indices.insert(std::pair<std::tuple<GLushort, GLushort, GLushort>, GLushort>(std::make_tuple(vertex.vertice, vertex.texCoord, vertex.normal), indexNumber));
		mesh->indices[i] = indexNumber;
		indexNumber++;

		//Passes the Vertex Data from the vectors into the vectors found in the mesh
		//It as well orders the vertex data (Vertices, TexCoords and Normals) passed into the vectors using the gathered indices from the vertexes vector
		mesh->vertices.push_back(vertices[vertex.vertice - 1]);
		if (mesh->hasTexCoords)
		{
			mesh->texCoords.push_back(textureCoords[vertex.texCoord - 1]);
		}
		if (mesh->hasNormals)
		{
			mesh->normals.push_back(normals[vertex.normal - 1]);
		}

	}

	return mesh; //Returns the mesh
}
