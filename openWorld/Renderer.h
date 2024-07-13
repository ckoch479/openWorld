#pragma once

#include "renderingInfoDefinitions.h"

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/type_ptr.hpp"
#include "includes/glm/gtc/quaternion.hpp"
#include "includes/glm/gtx/quaternion.hpp"

#include "Shader.h"

#include <vector>

#include "scene.h"
#include "camera.h"
#include "resourceManager.h"
#include "animator.h"
#include "PhysicsWorld.h"

#ifndef RENDERER_H
#define RENDERER_H

class renderer
{
public:
	renderer();

	~renderer();

	void renderScene(scene* currentScene);

	void drawScene(scene* scene);

	void drawModel(renderInfo* model, scene* currentScene, Shader* shader);

	void setDebugDepthQuadShader(Shader* shader);

	void setScreenEffectShader(Shader* shader);

	void renderPhysicsWorldDebugger(Shader* shader, PhysicsWorld* world, scene* scene);

private:

	//sets view, projection, and model matrices
	void setShaderMatrices(transform transf, Shader& shader, Camera* camera);

	void addLightUniformsToShader(scene* currentScene, Shader* shader);

	void createScreenQuad();

	void renderScreenQuad();

	void setCommonShaderUniforms(Shader& shader, Camera* camera); //view and projection matrices

	void setModelUniforms(Shader& shader, transform transf);

	void generateDepthMap(unsigned int* depthMapTex, unsigned int* depthMapFBO);

	glm::mat4 renderDirectionalShadowMap(scene* scene, unsigned int* depthMapFBO);

	void renderCubeShadowMap(scene* scene, glm::vec3 lightPos, unsigned int* depthCubeMapFBO);

	void generateCubeDepthMap(unsigned int* depthCubeMap, unsigned int* depthCubeMapFBO); //generate cube texture for point light depth maps

	glm::mat4 renderSpotShadowMap(scene* scene, unsigned int* depthMapFBO);

	void generateScreenEffectBuffer(unsigned int* hdrFBO, unsigned int* depthRBO, unsigned int* colorBuffer);

	

	//used for rendering hud objects or menu objects
	void load2DRenderShader();

	void render2DScreenObjects(scene* scene);

	const unsigned int SCR_WIDTH = 1600;
	const unsigned int SCR_HEIGHT = 800;

	unsigned int screenQuadVAO;
	unsigned int screenQuadVBO;

	float quadVertices[20]{
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};

	Shader* debugDepthQuad;
	Shader* screenEffectShader;
	Shader* screenShapeShader;

	//shadow data:

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	//const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048; //for better shadows

	//depth map for the directional light in the scene
	unsigned int depthMap;
	unsigned int depthMapFBO;

	//five cube depth maps one for each point light allowed in a scene
	unsigned int depthCubeMapFBO;
	unsigned int depthCubeMap;
	unsigned int depthCubeMapFBO1;
	unsigned int depthCubeMap1;
	unsigned int depthCubeMapFBO2;
	unsigned int depthCubeMap2;
	unsigned int depthCubeMapFBO3;
	unsigned int depthCubeMap3;
	unsigned int depthCubeMapFBO4;
	unsigned int depthCubeMap4;

	float near_plane = 0.01f;
	float far_plane = 100.0f;

	unsigned int hdrFBO;
	unsigned int depthBuffer;
	unsigned int colorBuffer;
};



#endif