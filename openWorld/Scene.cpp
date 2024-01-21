#include "Scene.h"

Scene::Scene() {};

ID Scene::AddInstance(ID& MeshID, ID& TransformID)
{
	Instance newInstance;
	newInstance.ModelID = MeshID;
	newInstance.TransformID = TransformID;
	ID instanceID;
	instanceID = this->Instances.add(newInstance);
	this->InstanceIDs.push_back(instanceID);

	RenderMesh newMesh;
	newMesh = this->Meshes.lookup(MeshID);

	this->InstanceCount++;

	return instanceID;
}

ID Scene::AddInstance(RenderModel& Model, Transform& transform)
{
	ID newModelID = this->Models.add(Model);
	ID newTransformID = this->Transforms.add(transform);

	Instance newInstance;
	newInstance.ModelID = newModelID;
	newInstance.TransformID = newTransformID;
	
	ID newInstanceID = this->Instances.add(newInstance);
	this->InstanceCount++;

	this->InstanceIDs.push_back(newInstanceID);

	return newInstanceID;
}

ID Scene::createModel(ModelData model, Shader& shader)
{
	RenderModel newModel;

	//create mesh IDs for rendering and push them back
	for(int i = 0; i < model.meshes.size(); i++)
	{
		ID newID;

		newID = createMesh(model.meshes[i]);
		newModel.renderMeshIDs.push_back(newID);
	}

	//create a bone map for animation for this model
	for (unsigned int i = 0; i < model.skeleton.size(); i++)
	{
		BoneData newbone;
		newbone.BoneId = model.skeleton[i].BoneId;
		newbone.boneMatrix = model.skeleton[i].boneMatrix;
		newbone.boneName = model.skeleton[i].boneName;

		newModel.boneMap[model.skeleton[i].boneName] = newbone;
	}

	//set the shader used for this model and meshes
	newModel.Modelshader = &shader;

	//no animation was added with this mode so animation ID remains null 
	//newModel.animationID;
	
	//no animations were loaded with this model so this is set to false
	newModel.hasActiveAnimation = false;

	ID newModelID;
	newModelID = Models.add(newModel);

	return newModelID;
}

ID Scene::createModel(ModelData model, Shader& shader, AnimationData* animation)
{
	RenderModel newModel;

	//create mesh IDs for rendering and push them back
	for (int i = 0; i < model.meshes.size(); i++)
	{
		ID newID;

		newID = createMesh(model.meshes[i]);
		newModel.renderMeshIDs.push_back(newID);
	}

	//create a bone map for animation for this model
	for (unsigned int i = 0; i < model.skeleton.size(); i++)
	{
		BoneData newbone;
		newbone.BoneId = model.skeleton[i].BoneId;
		newbone.boneMatrix = model.skeleton[i].boneMatrix;
		newbone.boneName = model.skeleton[i].boneName;

		newModel.boneMap[model.skeleton[i].boneName] = newbone;
	}

	//set the shader used for this model and meshes
	newModel.Modelshader = &shader;

	//add active animation ID to the model
	newModel.animationID = createAnimation(animation);

	//animations were loaded with this model so this is set to true
	newModel.hasActiveAnimation = true;

	ID newModelID;
	newModelID = Models.add(newModel);

	return newModelID;
}

void Scene::removeModelFromScene(ID modelID)
{
	RenderModel* tempModel;
	tempModel = &this->Models.lookup(modelID);

	for(int i = 0; i < tempModel->renderMeshIDs.size(); i++) //free the memory of the meshes linked to this model first
	{
		this->Meshes.remove(tempModel->renderMeshIDs[i]);
	}
	
	this->Models.remove(modelID); //free the memory of the model
}

void Scene::UpdateAnimation(ID modelID, ID animationID)
{
	RenderModel* tempModel;
	
	tempModel = &Models.lookup(modelID);

	tempModel->animationID = animationID;

	tempModel->hasActiveAnimation = true;
}

void Scene::UpdateShader(ID modelID, Shader& shader)
{
	RenderModel* tempModel;
	tempModel = &this->Models.lookup(modelID);
	tempModel->Modelshader = &shader;
}


ID Scene::createMesh(MeshData mesh) 
{
	RenderMesh newMesh;

	glGenVertexArrays(1, &newMesh.MeshVAO);
	glGenBuffers(1, &newMesh.MeshVBO);
	glGenBuffers(1, &newMesh.MeshEBO);

	glBindVertexArray(newMesh.MeshVAO);

	
	glBindBuffer(GL_ARRAY_BUFFER, newMesh.MeshVBO);

	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW); //this is how the vector should be done

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newMesh.MeshEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);

	//store position vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	//store normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	//store texcoords
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);
	//store BoneIds;
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, BoneIds));
	//store Bone weights;
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, boneWeights));

	//Add textures to the render mesh object
	newMesh.hasDiffuseTextures = (mesh.diffuseTextures.size() >= 1);
	newMesh.numDiffuseTextures = mesh.diffuseTextures.size();

	if (newMesh.hasDiffuseTextures == true)
	{
		newMesh.meshDiffuseTextures = mesh.diffuseTextures;
	}

	newMesh.hasSpecularTextures = (mesh.specularTextures.size() >= 1);
	newMesh.numSpecularTextures = mesh.specularTextures.size();

	if (newMesh.hasSpecularTextures == true)
	{
		newMesh.meshSpecularTextures = mesh.specularTextures;
	}

	newMesh.IndexCount = mesh.indices.size();

	ID newMeshID;
	newMeshID = this->Meshes.add(newMesh);
	glBindVertexArray(0);

	return newMeshID;
}

//test function for transforms
ID Scene::createTransform(glm::vec3 position, glm::vec3 rotationOrigin, glm::quat rotation, glm::vec3 scale) 
{
	Transform newTransform;
	newTransform.Translation = position;
	newTransform.RotationOrigin = rotationOrigin;
	newTransform.rotation = rotation;
	newTransform.Scale = scale;

	ID newTransformID;

	newTransformID = this->Transforms.add(newTransform);
	return newTransformID;
}

void Scene::updateTransform(ID transformID, glm::vec3 position, glm::vec3 rotationOrigin, glm::quat rotation, glm::vec3 scale)
{
	Transform* tempTransform;
	tempTransform = &this->Transforms.lookup(transformID);
	tempTransform->Translation = position;
	tempTransform->RotationOrigin = rotationOrigin;
	tempTransform->rotation = rotation;
	tempTransform->Scale = scale;

	if(!tempTransform)
	{
		std::cout << "transform ID not valid!\n";
	}

}

void Scene::DebugFunction() 
{
	std::cout << "instance count:" << this->InstanceCount << std::endl;
	std::cout << "instances size: " << this->Instances.size() << std::endl;
	std::cout << "instance ids size:" << this->InstanceIDs.size() << std::endl;
}

void Scene::Init() 
{
	this->MainCamera = new Camera;
}

void Scene::MoveCamera(Camera_Movement direction, float deltaTime) 
{
	this->MainCamera->ProcessKeyboard(direction, deltaTime);
}

void Scene::MouseAimCamera(float xoffset, float yoffset) 
{
	this->MainCamera->ProcessMouseMovement(xoffset, yoffset);
}

ID Scene::createAnimation(AnimationData* animation)
{
	RenderAnimation newAnimation;

	newAnimation.animationData = *animation;
	newAnimation.name = "noName!";
	newAnimation.currentPoint = 0.0f;

	ID animationID;
	animationID = animations.add(newAnimation);

	return animationID;
}

ID Scene::createAnimation(AnimationData* animation, std::string name)
{
	RenderAnimation newAnimation;

	newAnimation.animationData = *animation;
	newAnimation.name = name;
	newAnimation.currentPoint = 0.0f;

	ID animationID;
	animationID = animations.add(newAnimation);

	return animationID;
}

//ID Scene::createMesh(MeshData mesh, Shader& shader, AnimationData* animation)
//{
//	RenderMesh newMesh;
//
//	glGenVertexArrays(1, &newMesh.MeshVAO);
//	glGenBuffers(1, &newMesh.MeshVBO);
//	glGenBuffers(1, &newMesh.MeshEBO);
//
//	glBindVertexArray(newMesh.MeshVAO);
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, newMesh.MeshVBO);
//
//	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW); //this is how the vector should be done
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newMesh.MeshEBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);
//
//	//store position vertices
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//	glEnableVertexAttribArray(0);
//	//store normals
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Normal));
//	glEnableVertexAttribArray(1);
//	//store texcoords
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
//	glEnableVertexAttribArray(2);
//	//store BoneIds;
//	glEnableVertexAttribArray(3);
//	glVertexAttribIPointer(3, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, BoneIds));
//	//store Bone weights;
//	glEnableVertexAttribArray(4);
//	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, boneWeights));
//
//	//Add textures to the render mesh object
//	newMesh.hasDiffuseTextures = (mesh.diffuseTextures.size() >= 1);
//	newMesh.numDiffuseTextures = mesh.diffuseTextures.size();
//
//	if (newMesh.hasDiffuseTextures == true)
//	{
//		newMesh.meshDiffuseTextures = mesh.diffuseTextures;
//	}
//
//	newMesh.hasSpecularTextures = (mesh.specularTextures.size() >= 1);
//	newMesh.numSpecularTextures = mesh.specularTextures.size();
//
//	if (newMesh.hasSpecularTextures == true)
//	{
//		newMesh.meshSpecularTextures = mesh.specularTextures;
//	}
//
//	//newMesh.MeshVAO = VAO;
//	newMesh.Meshshader = &shader;
//
//	newMesh.IndexCount = mesh.indices.size();
//
//	newMesh.hasActiveAnimation = true;
//
//	newMesh.animationID = createAnimation(animation);
//
//	for (unsigned int i = 0; i < mesh.skeleton.size(); i++)
//	{
//		BoneData newbone;
//		newbone.BoneId = mesh.skeleton[i].BoneId;
//		newbone.boneMatrix = mesh.skeleton[i].boneMatrix;
//		newbone.boneName = mesh.skeleton[i].boneName;
//
//		newMesh.boneMap[mesh.skeleton[i].boneName] = newbone;
//	}
//
//	ID newMeshID;
//	newMeshID = this->Meshes.add(newMesh);
//	glBindVertexArray(0);
//
//	return newMeshID;
//}

ID Scene::createLight(DirectionalLight directionalLight)
{
	DirectionalLight newLight;

	newLight.ambient = directionalLight.ambient;
	newLight.diffuse = directionalLight.diffuse;
	newLight.direction = directionalLight.direction;
	newLight.specular = directionalLight.specular;

	ID newLightID;
	newLightID = directionalLights.add(newLight);
	this->directionLightID = newLightID;
	return newLightID;
}

ID Scene::createLight(Pointlight pointLight)
{
	Pointlight newLight;
	newLight.ambient = pointLight.ambient;
	newLight.constant = pointLight.constant;
	newLight.diffuse = pointLight.diffuse;
	newLight.linear = pointLight.linear;
	newLight.position = pointLight.position;
	newLight.quadratic = pointLight.quadratic;
	newLight.specular = pointLight.specular;

	ID newLightID;
	newLightID = pointLights.add(newLight);
	this->numPointLights++;
	this->pointLightIDs.push_back(newLightID);

	return newLightID;
}

ID Scene::createLight(SpotLight spotLight)
{
	SpotLight newLight;

	newLight.ambient = spotLight.ambient;
	newLight.constant = spotLight.constant;
	newLight.cutoff = spotLight.cutoff;
	newLight.diffuse = spotLight.diffuse;
	newLight.direction = spotLight.direction;
	newLight.linear = spotLight.linear;
	newLight.outerCutoff = spotLight.outerCutoff;
	newLight.position = spotLight.position;
	newLight.quadratic = spotLight.quadratic;
	newLight.specular = spotLight.specular;

	ID newLightID;
	newLightID = spotLights.add(newLight);
	this->spotLightID = newLightID;
	return newLightID;
}

ID Scene::createPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
{
	Pointlight newLight;
	newLight.ambient = ambient;
	newLight.constant = constant;
	newLight.diffuse = diffuse;
	newLight.linear = linear;
	newLight.position = position;
	newLight.quadratic = quadratic;
	newLight.specular = specular;

	ID newLightID;
	newLightID = createLight(newLight);
	
	return newLightID;
}

ID Scene::createDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	DirectionalLight newLight;

	newLight.ambient = ambient;
	newLight.diffuse = diffuse;
	newLight.direction = direction;
	newLight.specular = specular;

	ID newLightID;
	newLightID = createLight(newLight);
	return newLightID;
}

ID Scene::createSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float innerCutoff, float outerCutoff)
{
	SpotLight newLight;

	newLight.ambient = ambient;
	newLight.constant = constant;
	newLight.cutoff = innerCutoff;
	newLight.diffuse = diffuse;
	newLight.direction = direction;
	newLight.linear = linear;
	newLight.outerCutoff = outerCutoff;
	newLight.position = position;
	newLight.quadratic = quadratic;
	newLight.specular = specular;

	ID newLightID;
	newLightID = createLight(newLight);
	return newLightID;
}

void Scene::MovePointLight(ID pointLightID, glm::vec3 translation)
{
	pointLights.lookup(pointLightID).position = translation;
}
