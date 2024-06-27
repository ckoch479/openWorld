#pragma once

#include <iostream>
#include <vector>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "ResourceManager.h"


//requires a start position, its size, and a color
//ModelData createTestModel(glm::vec3 position, glm::vec3 size, glm::vec3 color)
//{
//	float xsizeFactor = size.x / 2;
//	float ysizeFactor = size.y / 2;
//	float zsizeFactor = size.z / 2;
//
//	ModelData newModel;
//	MeshData newMesh;
//	Vertex vertex1, vertex2, vertex3, vertex4, vertex5,vertex6,vertex7,vertex8;
//
//	//front
//	vertex1.vertexPosition = glm::vec3(position.x - xsizeFactor, position.y - ysizeFactor, position.z - zsizeFactor);
//	vertex2.vertexPosition = glm::vec3(position.x + xsizeFactor, position.y - ysizeFactor, position.z - zsizeFactor);
//	vertex3.vertexPosition = glm::vec3(position.x + xsizeFactor, position.y + ysizeFactor, position.z - zsizeFactor);
//	vertex4.vertexPosition = glm::vec3(position.x - xsizeFactor, position.y + ysizeFactor, position.z - zsizeFactor);
//	//back
//	vertex5.vertexPosition = glm::vec3(position.x - xsizeFactor, position.y - ysizeFactor, position.z + zsizeFactor);
//	vertex6.vertexPosition = glm::vec3(position.x + xsizeFactor, position.y - ysizeFactor, position.z + zsizeFactor);
//	vertex7.vertexPosition = glm::vec3(position.x + xsizeFactor, position.y + ysizeFactor, position.z + zsizeFactor);
//	vertex8.vertexPosition = glm::vec3(position.x - xsizeFactor, position.y + ysizeFactor, position.z + zsizeFactor);
//
//	vertex1.texCoords = glm::vec2(0, 0);
//	vertex1.Normal = color;
//	vertex2.texCoords = glm::vec2(0, 0);
//	vertex2.Normal = color;
//	vertex3.texCoords = glm::vec2(0, 0);
//	vertex3.Normal = color;
//	vertex4.texCoords = glm::vec2(0, 0);
//	vertex4.Normal = color;
//	vertex5.texCoords = glm::vec2(0, 0);
//	vertex5.Normal = color;
//	vertex6.texCoords = glm::vec2(0, 0);
//	vertex6.Normal = color;
//	vertex7.texCoords = glm::vec2(0, 0);
//	vertex7.Normal = color;
//	vertex8.texCoords = glm::vec2(0, 0);
//	vertex8.Normal = color;
//
//	vertex1.BoneIds[0] = -1.0;
//	vertex1.BoneIds[1] = -1.0;
//	vertex1.BoneIds[2] = -1.0;
//	vertex1.BoneIds[3] = -1.0;
//	vertex1.boneWeights[0] = 0.0;
//	vertex1.boneWeights[1] = 0.0;
//	vertex1.boneWeights[2] = 0.0;
//	vertex1.boneWeights[3] = 0.0;
//
//	vertex2.BoneIds[0] = -1.0;
//	vertex2.BoneIds[1] = -1.0;
//	vertex2.BoneIds[2] = -1.0;
//	vertex2.BoneIds[3] = -1.0;
//	vertex2.boneWeights[0] = 0.0;
//	vertex2.boneWeights[1] = 0.0;
//	vertex2.boneWeights[2] = 0.0;
//	vertex2.boneWeights[3] = 0.0;
//
//	vertex3.BoneIds[0] = -1.0;
//	vertex3.BoneIds[1] = -1.0;
//	vertex3.BoneIds[2] = -1.0;
//	vertex3.BoneIds[3] = -1.0;
//	vertex3.boneWeights[0] = 0.0;
//	vertex3.boneWeights[1] = 0.0;
//	vertex3.boneWeights[2] = 0.0;
//	vertex3.boneWeights[3] = 0.0;
//
//	vertex4.BoneIds[0] = -1.0;
//	vertex4.BoneIds[1] = -1.0;
//	vertex4.BoneIds[2] = -1.0;
//	vertex4.BoneIds[3] = -1.0;
//	vertex4.boneWeights[0] = 0.0;
//	vertex4.boneWeights[1] = 0.0;
//	vertex4.boneWeights[2] = 0.0;
//	vertex4.boneWeights[3] = 0.0;
//
//	vertex5.BoneIds[0] = -1.0;
//	vertex5.BoneIds[1] = -1.0;
//	vertex5.BoneIds[2] = -1.0;
//	vertex5.BoneIds[3] = -1.0;
//	vertex5.boneWeights[0] = 0.0;
//	vertex5.boneWeights[1] = 0.0;
//	vertex5.boneWeights[2] = 0.0;
//	vertex5.boneWeights[3] = 0.0;
//
//	vertex6.BoneIds[0] = -1.0;
//	vertex6.BoneIds[1] = -1.0;
//	vertex6.BoneIds[2] = -1.0;
//	vertex6.BoneIds[3] = -1.0;
//	vertex6.boneWeights[0] = 0.0;
//	vertex6.boneWeights[1] = 0.0;
//	vertex6.boneWeights[2] = 0.0;
//	vertex6.boneWeights[3] = 0.0;
//
//	vertex7.BoneIds[0] = -1.0;
//	vertex7.BoneIds[1] = -1.0;
//	vertex7.BoneIds[2] = -1.0;
//	vertex7.BoneIds[3] = -1.0;
//	vertex7.boneWeights[0] = 0.0;
//	vertex7.boneWeights[1] = 0.0;
//	vertex7.boneWeights[2] = 0.0;
//	vertex7.boneWeights[3] = 0.0;
//
//	vertex8.BoneIds[0] = -1.0;
//	vertex8.BoneIds[1] = -1.0;
//	vertex8.BoneIds[2] = -1.0;
//	vertex8.BoneIds[3] = -1.0;
//	vertex8.boneWeights[0] = 0.0;
//	vertex8.boneWeights[1] = 0.0;
//	vertex8.boneWeights[2] = 0.0;
//	vertex8.boneWeights[3] = 0.0;
//
//	newMesh.vertices.push_back(vertex1);
//	newMesh.vertices.push_back(vertex2);
//	newMesh.vertices.push_back(vertex3);
//	newMesh.vertices.push_back(vertex4);
//	newMesh.vertices.push_back(vertex5);
//	newMesh.vertices.push_back(vertex6);
//	newMesh.vertices.push_back(vertex7);
//	newMesh.vertices.push_back(vertex8);
//
//	newMesh.indices = std::vector <unsigned int> {0,1,2, 0,2,3, 1,6,2, 1,5,6, 3,2,6, 3,6,7, 4,0,3, 4,3,7, 5,4,7, 7,6,5 };
//
//	newModel.meshes.push_back(newMesh);
//
//	return newModel;
//}
