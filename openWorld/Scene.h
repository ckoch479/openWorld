#pragma once

#include "renderingInfoDefinitions.h"

#include "Model.h"
#include "Mesh.h"
#include "material.h"

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
	shape2D screenShape;
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

	std::string addStaticSceneObj(Model* model, transform& transf, Shader* shader); //static obj shader baked in to scene object

	std::string add2DScreenShape(shape2D screenShape);

	//remove object from scene when done using it
	void removeObjectFromScene(std::string id);

	void removeStaticObject(std::string id);

	void remove2DsceenShape(std::string id);

	//update object transform given its id
	void updateTransform(std::string id, transform transform);

	void update2Dshape(std::string id, glm::vec2 pos, glm::vec2 scale);

	//dumps all rendering info into a vector to be sent to the renderer
	std::vector <renderInfo*> getRenderingInfo();

	std::vector <renderInfo*> getStaticRenderingInfo();

	std::vector <shape2D*> getScreenShapes(); //also for renderer

	void generateModelRenderData(Mesh* mesh);

	void generate2DShapeData(shape2D* shape);

	std::vector <unsigned int> getModelVAOs(std::string modelID);

	std::vector <unsigned int> getStaticModelVAOs(std::string modelID);

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

	void setFocusPos(glm::vec3 pos);

	glm::vec3 getFocusPos();

	//for drawing 3D shapes (mainly for debug purposes should all use the same shader)
	//3D shapes use the normal 3d rendering i.e. they have a model* that will be rendered normally, the shader for 3d shapes is stored in the scene object

	//std::string addBoxToScene(glm::vec3 pos, glm::quat orient, glm::vec3 halfExtents); 

	//std::string addCapsuleToScene(glm::vec3 pos, glm::quat orient, float radius, float height);

	////no orientation due to a sphere being a sphere and ya know being equal in all directions
	//std::string addSphereToScene(glm::vec3 pos, float radius);

private:

	std::string createUniqueID();

	//map of active models in this scene
	std::unordered_map <std::string, renderInfo> activeModels;
	std::unordered_map <std::string, renderInfo> staticModels;

	std::unordered_map <std::string, transform> sceneTransforms;

	std::unordered_map <std::string, renderInfo2D> Objects2D;

	std::vector <std::string> modelIds;
	std::vector <std::string> staticModelIds;

	std::vector <std::string> model2Dids;

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

	Shader* genericShapeShader; //for rendering generic shapes (cube, sphere, capsule)

	int maxBones = 100;

	Shader* staticShader; //either set it from simulation manager or load it into the scene itself, by default will be loaded in with the option to overwrite it

	glm::vec3 sceneFocusPosition = glm::vec3(0,0,0);

};

#endif

//things to add:
// light objects
// textures
// bone and bone transformations
// shadows?
// 2d Graphics?

