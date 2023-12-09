#include "Scene.h"

Scene::Scene() {};

ID Scene::AddInstance(ID& MeshID, ID& TransformID)
{
	Instance newInstance;
	newInstance.MeshID = MeshID;
	newInstance.TransformID = TransformID;
	ID instanceID;
	instanceID = this->Instances.add(newInstance);
	this->InstanceIDs.push_back(instanceID);

	RenderMesh newMesh;
	newMesh = this->Meshes.lookup(MeshID);

	std::cout << newMesh.MeshVAO;
	this->InstanceCount++;

	return instanceID;
}

ID Scene::AddInstance(RenderMesh& mesh, Transform& transform)
{
	ID newMeshID = this->Meshes.add(mesh);
	ID newTransformID = this->Transforms.add(transform);

	Instance newInstance;
	newInstance.MeshID = newMeshID;
	newInstance.TransformID = newTransformID;
	
	

	ID newInstanceID = this->Instances.add(newInstance);
	this->InstanceCount++;

	this->InstanceIDs.push_back(newInstanceID);

	return newInstanceID;
}

//test function for meshes
ID Scene::createMesh(std::vector <glm::vec3>& vertices, std::vector <glm::vec3>& colors, Shader& shader) 
{
	RenderMesh newMesh;
	//create VAO for the mesh
	unsigned int VAO,VBO,VBO1;

	newMesh.hasTextures = false;
	newMesh.numTextures = 0;

	glGenVertexArrays(1, &newMesh.MeshVAO);
	glBindVertexArray(newMesh.MeshVAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * (3 * sizeof(float)), &vertices[0], GL_STATIC_DRAW); //this is how the vector should be done
	//store position vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * (3*sizeof(float)), &colors[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	//create the mesh object
	std::cout << newMesh.MeshVAO << std::endl;
	
	//newMesh.MeshVAO = VAO;
	newMesh.Meshshader = &shader;
	
	ID newMeshID;
	newMeshID = this->Meshes.add(newMesh);
	glBindVertexArray(0);

	return newMeshID;
}

ID Scene::createMesh(MeshData mesh,Shader& shader) 
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

	newMesh.hasTextures = (mesh.diffuseTextures.size() >= 1);
	newMesh.numTextures = mesh.diffuseTextures.size();

	if (newMesh.hasTextures == true)
	{
		newMesh.meshTextures = mesh.diffuseTextures;
	

		/*for(unsigned int i = 0;mesh.diffuseTextures.size(); i++)
		{
			newMesh.meshTextures.push_back(mesh.diffuseTextures[i]);
		}*/
	}

	//create the mesh object
	std::cout << newMesh.MeshVAO << std::endl;

	//newMesh.MeshVAO = VAO;
	newMesh.Meshshader = &shader;

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