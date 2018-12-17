#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include <vector>

struct Vector3
{
	float X;
	float Y;
	float Z;

	Vector3()
	{
	}

	Vector3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	//Calculates the Cross product of a Vector3
	static Vector3 Cross(Vector3 vec1, Vector3 vec2)
	{
		Vector3 newVec = Vector3();

		newVec.X = vec1.Y * vec2.Z - vec1.Z * vec2.Y;
		newVec.Y = vec1.Z * vec2.X - vec1.X * vec2.Z;
		newVec.Z = vec1.X * vec2.Y - vec1.Y * vec2.X;

		return newVec;
	}

	//Normalizes a Vector3
	static Vector3 Normalize(Vector3 vec)
	{
		float magnitudeS = (vec.X * vec.X) + (vec.Y * vec.Y) + (vec.Z * vec.Z);
		float magnitude = sqrt(magnitudeS);

		Vector3 newVec;
		newVec.X = vec.X / magnitude;
		newVec.Y = vec.Y / magnitude;
		newVec.Z = vec.Z / magnitude;

		return newVec;
	}
};

struct Vector2
{
	GLfloat X;
	GLfloat Y;

	Vector2()
	{
	}

	Vector2(float x, float y)
	{
		X = x;
		Y = y;
	}

	//Normalizes a Vector2
	static Vector2 Normalize(Vector2 vec)
	{
		float magnitudeS = (vec.X * vec.X) + (vec.Y * vec.Y);
		float magnitude = sqrt(magnitudeS);

		Vector2 newVec;
		newVec.X = vec.X / magnitude;
		newVec.Y = vec.Y / magnitude;

		return newVec;
	}
};

struct Vector4
{
	GLfloat X;
	GLfloat Y;
	GLfloat Z;
	GLfloat W;

	Vector4()
	{
	}

	Vector4(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
};

struct Lighting
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
};

struct Material
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
};

struct Color
{
	GLfloat R;
	GLfloat G;
	GLfloat B;
};

struct TexCoord
{
	GLfloat U;
	GLfloat V;
};

struct Vertex
{
	int vertice;
	int texCoord;
	int normal;
};

//The mesh Struct that holds all information about a Struct
struct Mesh
{
	std::vector<Vector3> vertices;
	std::vector<TexCoord> texCoords;
	std::vector<Vector3> normals;
	GLushort* indices;

	int vertexCount;
	int texCoordCount;
	int normalCount;
	int indiceCount;

	bool hasTexCoords;
	bool hasNormals;

	~Mesh()
	{
		//delete[] vertices;
		//delete[] texCoords;
		//delete[] normals;
		delete[] indices;
	}
};
