#include "Scene.h"

scene::scene()
{
	//generate 10 placeholder point lights and spot lights;
	//generate 1 placeholder directional light;

	for (unsigned int i = 0; i < 5; i++)
	{
		glm::vec3 pos(0.0, 10.0, 0.0);
		glm::vec3 direction(0, -1, 0);
		glm::vec3 color(0.0f);

		addPointLight(pos, color, color, color, i);
		addSpotLight(pos, direction, color, color, color, i);
	}
	setDirectionalLight(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f));
}

scene::~scene()
{

}


std::string scene::addObjectToScene(Model* model, transform transf, Shader* shader)
{
	std::string Modelid = createUniqueID();

	modelIds.push_back(Modelid);

	transform newTransform;
	newTransform = transf;

	sceneTransforms[Modelid] = newTransform;

	renderInfo newInfo;
	newInfo.model = model;
	newInfo.transf = &sceneTransforms[Modelid];
	newInfo.shader = shader;
	newInfo.id = Modelid;

	activeModels[Modelid] = newInfo;

	for (unsigned int i = 0; i < activeModels[Modelid].model->meshes.size(); i++)
	{
		generateModelRenderData(&activeModels[Modelid].model->meshes[i]); //this function generates a VAO and VBO for each mesh in the model
	}

	return Modelid;
}

void scene::removeObjectFromScene(std::string id)
{

}

void scene::updateTransform(std::string id, transform transform)
{
	sceneTransforms[id] = transform;
}

std::vector <renderInfo*> scene::getRenderingInfo()
{
	std::vector <renderInfo*> renderDump;

	for (unsigned int i = 0; i < modelIds.size(); i++)
	{
		renderDump.push_back(&activeModels[modelIds[i]]);
	}

	return renderDump;
}

void scene::generateModelRenderData(Mesh* mesh)
{
	unsigned int* VAO = &mesh->VAO;
	unsigned int* VBO = &mesh->VBO;
	unsigned int* EBO = &mesh->EBO;
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), &mesh->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int), &mesh->indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	// vertex bit tangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitTangent));
	// vertex boneids
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIDs));
	// vertex boneWeights
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, boneWeights));
}

std::vector <unsigned int> scene::getModelVAOs(std::string modelID)
{
	std::vector <unsigned int> VAOs;

	Model* model = activeModels[modelID].model;
	for (unsigned int i = 0; i < model->meshes.size(); i++)
	{
		VAOs.push_back(model->meshes[i].VAO);
	}

	return VAOs;
}

std::string scene::createUniqueID()
{
	std::string newId;

	newId = "Model:" + std::to_string(idCounter);
	idCounter++;

	return newId;
}

Camera* scene::getCurrentCamera()
{
	return this->sceneCamera;
}

void scene::setCamera(Camera* camera)
{
	this->sceneCamera = camera;
}

std::vector <pointLight*> scene::getPointLights()
{
	std::vector <pointLight*> lights;
	for (unsigned int i = 0; i < 5; i++)
	{
		lights.push_back(&this->pointLights[i]);
	}

	return lights;
}

std::vector <spotLight*> scene::getSpotLights()
{
	std::vector <spotLight*> lights;
	for (unsigned int i = 0; i < 5; i++)
	{
		lights.push_back(&this->spotLights[i]);
	}

	return lights;
}

directionalLight* scene::getDirectionalLight()
{
	return &this->mainLight;
}

void scene::addPointLight(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, int index)
{
	if (index > 5)
	{
		std::cout << "ERROR::SCENE pointlight index out of range\n";
	}
	if (index < 5)
	{
		pointLight newLight;
		newLight.ambient = ambient;
		newLight.diffuse = diffuse;
		newLight.specular = specular;
		newLight.position = pos;
		newLight.constant = 1.0f;
		newLight.linear = 0.009;
		newLight.quadratic = 0.0032f;

		pointLights[index] = newLight;
	}
}

void scene::addSpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, int index)
{
	if (index > 5)
	{
		std::cout << "ERROR::SCENE spotLight index out of range\n";
	}
	if (index < 5)
	{
		spotLight newLight;
		newLight.ambient = ambient;
		newLight.diffuse = diffuse;
		newLight.specular = specular;
		newLight.position = pos;
		newLight.direction = dir;
		newLight.constant = 1.0f;
		newLight.linear = 0.09f;
		newLight.quadratic = 0.032f;
		newLight.cutoff;
		newLight.outerCutoff;

		spotLights[index] = newLight;
	}
}

void scene::setDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->mainLight.direction = direction;
	this->mainLight.ambient = ambient;
	this->mainLight.diffuse = diffuse;
	this->mainLight.specular = specular;
}

void scene::setDepthShader(Shader* depthShader)
{
	this->depthShader = depthShader;
}

Shader* scene::getDepthShader()
{
	return this->depthShader;
}

void scene::setDepthCubeShader(Shader* depthShader)
{
	this->depthCubeShader = depthShader;
}

Shader* scene::getDepthCubeShader()
{
	return this->depthCubeShader;
}

//2d rendering

std::string scene::add2DScreenShape(shape2D screenShape)
{
	std::string newId = createUniqueID();

	renderInfo2D newInfo;
	newInfo.screenShape = screenShape;
	
	this->Objects2D[newId] = newInfo;
	this->model2Dids.push_back(newId);

	generate2DShapeData(&this->Objects2D[newId].screenShape);

	return newId;
}

void scene::remove2DsceenShape(std::string id)
{

}

void scene::update2Dshape(std::string id, glm::vec2 pos, glm::vec2 scale)
{
	this->Objects2D[id].screenShape.position = glm::vec3(pos.x, pos.y, 0.0f);
	this->Objects2D[id].screenShape.scale = glm::vec3(scale.x, scale.y, 1.0f);
}

//returns a vector of pointers of shape2D for rendering
std::vector <shape2D*> scene::getScreenShapes()
{
	std::vector <shape2D*> renderDump;

	for (unsigned int i = 0; i < model2Dids.size(); i++)
	{
		renderDump.push_back(&Objects2D[model2Dids[i]].screenShape);
	}

	return renderDump;
}

void scene::generate2DShapeData(shape2D* shape)
{
	unsigned int* VAO = &shape->VAO;
	unsigned int* VBO = &shape->VBO;

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);

	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, shape->vertices.size() * sizeof(Vertex2D), &shape->vertices[0], GL_STATIC_DRAW);

	//vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)0);
	// vertex colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, color));
}

//void Scene::MoveCamera(Camera_Movement direction, float deltaTime) 
//{
//	this->MainCamera->ProcessKeyboard(direction, deltaTime);
//}
//
//void Scene::MouseAimCamera(float xoffset, float yoffset) 
//{
//	this->MainCamera->ProcessMouseMovement(xoffset, yoffset);
//}
//
//void Scene::setCameraPosition(glm::vec3 target, glm::vec3 position, float pitch, float yaw)
//{
//	this->MainCamera->updateCamera(target,position, pitch, yaw);
//}