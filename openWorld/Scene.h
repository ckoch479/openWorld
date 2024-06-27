#pragma once

#include "renderingInfoDefinitions.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "camera.h"

#include <unordered_map>
#include <vector>

#define MAX_NR_SPOT_LIGHTS 6;

#ifndef SCENE_H
#define SCENE_H

struct renderInfo
{
	Model* model;
	transform* transf;
	Shader* shader;
	std::string id;
};

struct renderInfo2D
{
	shape2D* screenShape;
	glm::vec2 screenPos;//these will be in a range between -500 - +500 both in the x and y directions instead of the normal -1 - 1 of opengl
};

//scene is a database of all objects that need to be drawn. Each object is placed in a table. 
// All parts of each object are contained within tables as well.
//VAOS are stored in the Scene class, basic data such as Vertices, indices, and textures/materials are stored in ResourceManager
class scene
{
public:

	scene();

	~scene();

	//add object to scene for rendering
	std::string addObjectToScene(Model* model, transform transf, Shader* shader);

	//remove object from scene when done using it
	void removeObjectFromScene(std::string id);

	//update object transform given its id
	void updateTransform(std::string id, transform transform);

	//dumps all rendering info into a vector to be sent to the renderer
	std::vector <renderInfo*> getRenderingInfo();

	void generateModelRenderData(Mesh* mesh);

	std::vector <unsigned int> getModelVAOs(std::string modelID);

	Camera* getCurrentCamera();

	void setCamera(Camera* camera);

	void addPointLight(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, int index);

	void addSpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, int index);

	void setDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

	std::vector <pointLight*> getPointLights();

	std::vector <spotLight*> getSpotLights();

	directionalLight* getDirectionalLight();

	void setDepthShader(Shader* depthShader);

	Shader* getDepthShader();

	void setDepthCubeShader(Shader* depthShader);

	Shader* getDepthCubeShader();

private:

	std::string createUniqueID();

	//map of active models in this scene
	std::unordered_map <std::string, renderInfo> activeModels;

	std::unordered_map <std::string, transform> sceneTransforms;

	std::vector <std::string> modelIds;

	unsigned int idCounter = 0; //counter for scene objects allows all objects to be referenced for rendering

	//scene settings
	int maxLights = 5; //max number of point/spot lights allowed per scene
	//only one directional light per scene as of right now

	std::unordered_map<int, pointLight> pointLights;
	std::unordered_map<int, spotLight> spotLights;
	directionalLight mainLight;

	Camera* sceneCamera;
	Shader* depthShader;
	Shader* depthCubeShader;

	int maxBones = 100;

};

#endif

//things to add:
// light objects
// textures
// bone and bone transformations
// shadows?
// 2d Graphics?

