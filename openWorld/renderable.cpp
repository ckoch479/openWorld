#include "renderable.h"

renderable::renderable(std::string uniqueID)
{
	this->uniqueID = uniqueID;
}

renderable::~renderable()
{

}

void renderable::loadModel(std::string filePath)
{
	this->objModel = ResourceManager::loadModel(filePath, this->uniqueID);
}

void renderable::addToScene(Shader* shader, scene* sceneObj)
{
	if(this->objModel)
	{
		if (this->animated)
		{
			transform newTransform;
			newTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);
			newTransform.orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			newTransform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

			this->objShader = shader;
			this->sceneID = this->sceneObj->addObjectToScene(this->objModel, newTransform, shader);
		}
		else
		{
			transform newTransform;
			newTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);
			newTransform.orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			newTransform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

			this->objShader = shader;
			this->sceneID = this->sceneObj->addStaticSceneObj(this->objModel, newTransform, shader);
		}
	}
	else
	{
		std::cout << "ERROR::NO::MODEL::ATTACHED::TO::COMPONENT::" << this->uniqueID << std::endl;
	}
}

void renderable::addToScene(Shader* shader, scene* sceneObj, bool isAnimated)
{
	this->animated = isAnimated;
	if (this->objModel)
	{
		if (this->animated)
		{
			transform newTransform;
			newTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);
			newTransform.orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			newTransform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

			this->objShader = shader;
			this->sceneID = this->sceneObj->addObjectToScene(this->objModel, newTransform, shader);
		}
		else
		{
			transform newTransform;
			newTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);
			newTransform.orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			newTransform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

			this->objShader = shader;
			this->sceneID = this->sceneObj->addStaticSceneObj(this->objModel, newTransform, shader);
		}
	}
	else
	{
		std::cout << "ERROR::NO::MODEL::ATTACHED::TO::COMPONENT::" << this->uniqueID << std::endl;
	}
}

void renderable::removeFromScene()
{
	if (this->sceneObj)
	{
		if(this->animated)
		{
			this->sceneObj->removeObjectFromScene(this->sceneID);
		}
		else
		{
			this->sceneObj->removeStaticObject(this->sceneID);
		}
	}
	else
	{
		std::cout << "ERROR::NO::SCENE::OBJECT::ATTACHED::TO::COMPONENT::" << this->uniqueID << std::endl;
	}
}

void renderable::setIsAnimated(bool setter)
{
	this->animated = setter;
}

void renderable::updateSceneTransform(glm::vec3 position, glm::quat orientation, glm::vec3 scale)
{
	if(this->sceneObj)
	{
		transform newTransform;
		newTransform.position = position;
		newTransform.orientation = orientation;
		newTransform.scale = scale;

		this->sceneObj->updateTransform(this->sceneID, newTransform);
	}
	else
	{
		std::cout << "ERROR::NO::SCENE::OBJECT::ATTACHED::TO::COMPONENT::" << this->uniqueID << std::endl;
	}
}