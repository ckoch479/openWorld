#include "npcEntity.h"

npcEntity::npcEntity(std::string npcFilePath, std::string name)
{
	this->name = name;
	this->filePath = npcFilePath;

	this->Model = ResourceManager::loadModel(npcFilePath, this->name);

	transform newTransform;
	newTransform.position = glm::vec3(0, 2, 0);
	newTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	newTransform.scale = glm::vec3(1.0f);

	this->currentTransform = newTransform;//default transform for now
	relTransform newTransf;
	newTransf.front = glm::vec3(0, 0, -1);
	newTransf.up = glm::vec3(0, 1, 0);
	newTransf.right = glm::vec3(1, 0, 0);
	this->relativeTransf = newTransf;
	calculateRelTransform();

	//all set to new since its a new player being made (born if you will)
	this->meshChange = true;
	this->actionChange = true;
	this->animationChange = true;

	this->animator = new objAnimator(this->Model);
	this->animator->setSkeleton(this->Model->skeleton);

	loadAnimations(filePath);

	this->activeAnim = "idle";
	this->animator->playAnimation(this->activeAnim);

	updateEntity();
}

npcEntity::~npcEntity()
{

}

void npcEntity::setNPCaction(npcActions action)
{
	if (this->currentAction != action)
	{
		this->currentAction = action;
		this->actionChange = true;
		updateEntity();
	}
}

npcActions npcEntity::getNPCaction()
{
	return this->currentAction;
}

void npcEntity::setNPCtransform(transform newTransform)
{
	this->currentTransform = newTransform;
}

transform* npcEntity::getTransform()
{
	return &this->currentTransform;
}

relTransform* npcEntity::getRelativeTransform()
{
	return &this->relativeTransf;
}

Model* npcEntity::getNPCmodel()
{
	return this->Model;
}

void npcEntity::calculateRelTransform()
{
	glm::quat tempQuat = this->currentTransform.orientation;

	glm::vec3 front;
	//front.x = 2 * (tempQuat.x * tempQuat.z + tempQuat.w * tempQuat.y);
	//front.y = 2 * (tempQuat.y * tempQuat.z - tempQuat.w * tempQuat.x);
	//front.z = 1 - 2 * (tempQuat.x * tempQuat.x + tempQuat.y + tempQuat.y);

	front = tempQuat * glm::vec3(0, 0, 1);

	glm::vec3 right = glm::vec3(0, 0, 0);
	glm::vec3 up = glm::vec3(0, 0, 0);

	//std::cout << "player front: " << glm::to_string(front) << std::endl;

	this->relativeTransf.front = glm::normalize(front);

	//std::cout << "player fron normalized: " << glm::to_string(glm::normalize(front)) << std::endl;
	this->relativeTransf.up = up;
	this->relativeTransf.right = right;
}

void npcEntity::addToScene(scene* scene, Shader* shader)
{
	this->sceneID = scene->addObjectToScene(this->Model, this->currentTransform, shader);
}

void npcEntity::updateScene(scene* scene)
{
	scene->updateTransform(this->sceneID, this->currentTransform);
}

objAnimator* npcEntity::getAnimator()
{
	return this->animator;
}

void npcEntity::updateEntity()
{
	if (meshChange)
	{
		//update meshes in the scene or whatever
	}

	if (actionChange)
	{
		//update action parameters
		updateActions();
		actionChange = false;
	}

	if (animationChange)
	{
		//update to the new animation, after action change check because thats what should set new animations and nothing else
		this->animator->playAnimation(this->activeAnim);
		animationChange = false;
	}

	this->Model->animationMatrices = *this->animator->getAnimationTransforms();
}

void npcEntity::loadAnimations(std::string filePath)
{
	std::string name = "idle";
	std::string Path = "resources/NPC/Animations/standingIdle.gltf"; //for some reason i have to do it this way

	this->animator->loadAnimation(name, Path, true);
	
	name = "idleSearching";
	Path = "resources/NPC/Animations/idleSearch.gltf";
	this->animator->loadAnimation(name, Path, true);

	/*name = "walkingForward";
	Path = "resources/NPC/Animations/standingIdle.gltf";
	this->animator->loadAnimation(name, Path, true);*/

	name = "shambleForward";
	Path = "resources/NPC/Animations/shambleForward.gltf";
	this->animator->loadAnimation(name, Path, true);

	name = "stumbleForward";
	Path = "resources/NPC/Animations/walkingForwardReach.gltf";
	this->animator->loadAnimation(name, Path, true);

	name = "crawlForward";
	Path = "resources/NPC/Animations/crawling.gltf";
	this->animator->loadAnimation(name, Path, true);

	/*name = "lungeForward";
	Path = "resources/NPC/Animations/standingIdle.gltf";
	this->animator->loadAnimation(name, Path, true);*/

	/*name = "grabForward";
	Path = "resources/NPC/Animations/standingIdle.gltf";
	this->animator->loadAnimation(name, Path, true);*/

	name = "grabBite";
	Path = "resources/NPC/Animations/reachBite.gltf";
	this->animator->loadAnimation(name, Path, true);

	name = "swipe";
	Path = "resources/NPC/Animations/swipeAttack.gltf";
	this->animator->loadAnimation(name, Path, true);

	name = "dying";
	Path = "resources/NPC/Animations/dying.gltf";
	this->animator->loadAnimation(name, Path, true);

}

void npcEntity::updateActions()
{
	switch (this->currentAction)
	{
	case(npcIdle):
		this->activeAnim = "idle";
		this->animationChange = true;
		break;

	case(idleSearching):
		this->activeAnim = "idleSearching";
		this->animationChange = true;
		break;

	case(walkingForward):
		this->activeAnim = "walkingForward";
		this->animationChange = true;
		break;

	case(shambleForward):
		this->activeAnim = "shambleForward";
		this->animationChange = true;
		break;

	case(stumbleForward):
		this->activeAnim = "stumbleForward";
		this->animationChange = true;
		break;

	/*case(walkRight):
		this->activeAnim = "walkRight";
		this->animationChange = true;
		break;

	case(walkLeft):
		this->activeAnim = "walkLeft";
		this->animationChange = true;
		break;*/

	case(shambleLeft):
		this->activeAnim = "shambleLeft";
		this->animationChange = true;
		break;

	case(shambleRight):
		this->activeAnim = "shambleRight";
		this->animationChange = true;
		break;

	case(stumbleLeft):
		this->activeAnim = "stumbleLeft";
		this->animationChange = true;
		break;

	case(stumbleRight):
		this->activeAnim = "stumbleRight";
		this->animationChange = true;
		break;

	case(crawlForward):
		this->activeAnim = "crawlForward";
		this->animationChange = true;
		break;

	case(lungeForward):
		this->activeAnim = "lungeForward";
		this->animationChange = true;
		break;

	case(grabForward):
		this->activeAnim = "grabForward";
		this->animationChange = true;
		break;

	case(grabBite):
		this->activeAnim = "grabBite";
		this->animationChange = true;
		break;

	case(swipe):
		this->activeAnim = "swipe";
		this->animationChange = true;
		break;

	/*case(falling):
		this->activeAnim = "falling";
		this->animationChange = true;
		break;*/

	case(npcDying):
		this->activeAnim = "dying";
		this->animationChange = true;
		//die, thats pretty much it
		break;

	}
}