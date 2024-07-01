#include "renderer.h"

renderer::renderer()
{
	//create the screen quad vao,vbo for rendering effects and such
	createScreenQuad();
	generateDepthMap(&depthMap, &depthMapFBO);
	//generateScreenEffectBuffer(&this->hdrFBO,&this->depthBuffer,&this->colorBuffer); // doesnt work as of right now idk why

	glEnable(GL_DEPTH_TEST);

}

renderer::~renderer()
{

}

void renderer::drawModel(renderInfo* model, scene* currentScene, Shader* shader)
{
	std::vector <unsigned int> modelVAOs = currentScene->getModelVAOs(model->id);

	for (unsigned int i = 0; i < modelVAOs.size(); i++)
	{
		Material* material = &model->model->meshes[i].material;
		glBindVertexArray(modelVAOs[i]);

		//this is why i couldnt load multiple textures on one object
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(glGetUniformLocation(shader->ID, "Material.diffuse_texture0"), 1);
		glBindTexture(GL_TEXTURE_2D, material->diffuse0->id);

		//check for specular textures and bind them if they exist if not bind the diffuse again
		if (material->specular0)
		{
			glActiveTexture(GL_TEXTURE2);
			glUniform1i(glGetUniformLocation(shader->ID, "Material.specular_texture0"), 2);
			glBindTexture(GL_TEXTURE_2D, material->specular0->id);
		}
		if (!material->specular0)
		{
			glActiveTexture(GL_TEXTURE2);
			glUniform1i(glGetUniformLocation(shader->ID, "Material.specular_texture0"), 2);
			glBindTexture(GL_TEXTURE_2D, material->diffuse0->id);
		}
		//check for normal texture and bind them if they exist if not bind diffse again (again)
		if (material->normalMap0)
		{
			glActiveTexture(GL_TEXTURE3);
			glUniform1i(glGetUniformLocation(shader->ID, "Material.normal_texture0;"), 3);
			glBindTexture(GL_TEXTURE_2D, material->normalMap0->id);
			shader->SetBool("hasNormalTextures", true);

		}
		if (!material->normalMap0)
		{
			glActiveTexture(GL_TEXTURE3);
			glUniform1i(glGetUniformLocation(shader->ID, "Material.normal_texture0;"), 3);
			glBindTexture(GL_TEXTURE_2D, material->diffuse0->id);
			shader->SetBool("hasNormalTextures", false);
		}

		shader->SetFloat("Material.shininess", material->shininess);
		animator::setAnimationMatrices(model->model, shader);

		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(model->model->meshes[i].indices.size()), GL_UNSIGNED_INT, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(0);
	}
}

void renderer::generateDepthMap(unsigned int* depthMapTex, unsigned int* depthMapFBO)
{
	glGenFramebuffers(1, depthMapFBO);

	glGenTextures(1, depthMapTex);
	glBindTexture(GL_TEXTURE_2D, *depthMapTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->SHADOW_WIDTH, this->SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f,1.0f,1.0f,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, *depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *depthMapTex, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE0, 0);
}

glm::mat4 renderer::renderDirectionalShadowMap(scene* scene, unsigned int* depthMapFBO)
{
	glm::vec3 lightPos = (scene->getDirectionalLight()->direction * glm::vec3(-50));
	Shader* simpleDepthShader = scene->getDepthShader();
	std::vector <renderInfo*> data = scene->getRenderingInfo();

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	//float near_plane = 1.0f, far_plane = 100.0f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, this->near_plane, this->far_plane);
	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	simpleDepthShader->use();
	simpleDepthShader->SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);

	glViewport(0, 0, this->SHADOW_WIDTH, this->SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, *depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	//render everything here
	glCullFace(GL_FRONT);
	for (unsigned int i = 0; i < data.size(); i++)
	{
		setModelUniforms(*simpleDepthShader, *data[i]->transf);
		drawModel(data[i], scene, simpleDepthShader);
	}
	glCullFace(GL_BACK);

	return lightSpaceMatrix;
}

glm::mat4 renderer::renderSpotShadowMap(scene* scene, unsigned int* depthMapFBO)
{
	glm::vec3 lightPos = scene->getSpotLights()[0]->position;
	Shader* simpleDepthShader = scene->getDepthShader();
	std::vector <renderInfo*> data = scene->getRenderingInfo();

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	//float near_plane = 1.0f, far_plane = 100.0f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, this->near_plane, this->far_plane);
	lightView = glm::lookAt(lightPos, scene->getSpotLights()[0]->direction, glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	simpleDepthShader->use();
	simpleDepthShader->SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);

	glViewport(0, 0, this->SHADOW_WIDTH, this->SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, *depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	//render everything here
	glCullFace(GL_FRONT);
	for (unsigned int i = 0; i < data.size(); i++)
	{
		setModelUniforms(*simpleDepthShader, *data[i]->transf);
		drawModel(data[i], scene, simpleDepthShader);
	}
	glCullFace(GL_BACK);

	return lightSpaceMatrix;
}

void renderer::renderCubeShadowMap(scene* scene, glm::vec3 lightPos, unsigned int* depthCubeMapFBO)
{
	Shader* cubedepthShader = scene->getDepthCubeShader();
	std::vector <renderInfo*> data = scene->getRenderingInfo();

	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)this->SHADOW_WIDTH / (float)this->SHADOW_HEIGHT, near_plane, far_plane);
	std::vector <glm::mat4> shadowTransforms;

	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, *depthCubeMapFBO);

	glClear(GL_DEPTH_BUFFER_BIT);
	cubedepthShader->use();
	for (unsigned int i = 0; i < 6; ++i)
	{
		cubedepthShader->SetMatrix4(("shadowMatrices[" + std::to_string(i) + "]").c_str(), shadowTransforms[i]);
	}
	cubedepthShader->SetFloat("far_plane", far_plane);
	cubedepthShader->SetVector3f("lightPos", lightPos);

	//render everything here
	glCullFace(GL_FRONT);
	for (unsigned int i = 0; i < data.size(); i++)
	{
		setModelUniforms(*cubedepthShader, *data[i]->transf);
		drawModel(data[i], scene, cubedepthShader);
	}
	glCullFace(GL_BACK);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void renderer::drawScene(scene* scene)
{
	std::vector <renderInfo*> data = scene->getRenderingInfo();

	glm::mat4 lightSpaceMatrix = renderDirectionalShadowMap(scene, &this->depthMapFBO);//directional shadow map


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//render everything again
	for (unsigned int i = 0; i < data.size(); i++)
	{
		glActiveTexture(GL_TEXTURE4);
		glUniform1i(glGetUniformLocation(data[i]->shader->ID, "shadowMap"), 4);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		data[i]->shader->SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);
		data[i]->shader->SetFloat("far_plane", this->far_plane);

		addLightUniformsToShader(scene, data[i]->shader);

		setCommonShaderUniforms(*data[i]->shader, scene->getCurrentCamera());
		setModelUniforms(*data[i]->shader, *data[i]->transf);
		drawModel(data[i], scene, data[i]->shader);
	}


	//shadow debug 
	/*this->debugDepthQuad->use();
	this->debugDepthQuad->SetFloat("near_plane",near_plane);
	this->debugDepthQuad->SetFloat("far_plane",far_plane);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	renderScreenQuad();*/

	/*glBindBuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->screenEffectShader->use();
	this->screenEffectShader->SetBool("hdr",false);
	this->screenEffectShader->SetFloat("exposure", 10.0);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(this->screenEffectShader->ID, "hdrBuffer"), 0);
	glBindTexture(GL_TEXTURE_2D, colorBuffer);
	renderScreenQuad();*/

}

void renderer::renderScene(scene* currentScene)
{
	std::vector <renderInfo*> data = currentScene->getRenderingInfo(); //dumps rendering info into a vector for use in renderings
	Camera* camera = currentScene->getCurrentCamera();

	//render objects in scene
	for (unsigned int i = 0; i < data.size(); i++)
	{
		Shader* shader = data[i]->shader;
		Model* model = data[i]->model;

		shader->use();
		shader->SetVector3f("viewPos", camera->Position);

		setShaderMatrices(*data[i]->transf, *shader, camera);
		addLightUniformsToShader(currentScene, shader);

		std::vector <unsigned int> modelVAOs = currentScene->getModelVAOs(data[i]->id);
		for (unsigned int j = 0; j < modelVAOs.size(); j++)
		{
			Material* material = &model->meshes[j].material;
			glBindVertexArray(modelVAOs[j]);

			//this is why i couldnt load multiple textures on one object
			glActiveTexture(GL_TEXTURE1);
			glUniform1i(glGetUniformLocation(shader->ID, "Material.diffuse_texture0"), 1);
			glBindTexture(GL_TEXTURE_2D, material->diffuse0->id);

			//check for specular textures and bind them if they exist if not bind the diffuse again
			if (material->specular0)
			{
				glActiveTexture(GL_TEXTURE2);
				glUniform1i(glGetUniformLocation(shader->ID, "Material.specular_texture0"), 2);
				glBindTexture(GL_TEXTURE_2D, material->specular0->id);
			}
			if (!material->specular0)
			{
				glActiveTexture(GL_TEXTURE2);
				glUniform1i(glGetUniformLocation(shader->ID, "Material.specular_texture0"), 2);
				glBindTexture(GL_TEXTURE_2D, material->diffuse0->id);
			}
			//check for normal texture and bind them if they exist if not bind diffse again (again)
			if (material->normalMap0)
			{
				glActiveTexture(GL_TEXTURE3);
				glUniform1i(glGetUniformLocation(shader->ID, "Material.specular_texture0"), 3);
				glBindTexture(GL_TEXTURE_2D, material->normalMap0->id);
			}
			if (!material->normalMap0)
			{
				glActiveTexture(GL_TEXTURE3);
				glUniform1i(glGetUniformLocation(shader->ID, "Material.specular_texture0"), 3);
				glBindTexture(GL_TEXTURE_2D, material->diffuse0->id);
			}

			shader->SetFloat("Material.shininess", material->shininess);

			glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(data[i]->model->meshes[j].indices.size()), GL_UNSIGNED_INT, 0);

			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(0);
		}

	}

}

void renderer::addLightUniformsToShader(scene* currentScene, Shader* shader)
{
	shader->use();
	//std::vector <pointLight*> pointLights = currentScene->getPointLights();
	//std::vector <spotLight*> spotLights = currentScene->getSpotLights();
	directionalLight* dirLight = currentScene->getDirectionalLight();
	//set point light uniforms
	//for(unsigned int i = 0; i < pointLights.size(); i++)
	//{
	//	std::string pointLightsStr;
	//	pointLightsStr = "pointLight[" + std::to_string(i) + "]";
	//	shader->SetVector3f((pointLightsStr + ".position").c_str(), pointLights[i]->position);
	//	shader->SetVector3f((pointLightsStr + ".ambient").c_str(),  pointLights[i]->ambient);
	//	shader->SetVector3f((pointLightsStr + ".diffuse").c_str(),  pointLights[i]->diffuse);
	//	shader->SetVector3f((pointLightsStr + ".specular").c_str(), pointLights[i]->specular);
	//	shader->SetFloat(	(pointLightsStr + ".constant").c_str(), pointLights[i]->constant);
	//	shader->SetFloat(   (pointLightsStr + ".linear").c_str(),	 pointLights[i]->linear);
	//	shader->SetFloat(   (pointLightsStr + ".quadratic").c_str(),pointLights[i]->quadratic);
	//}
	////set spotlight uniforms
	//for (unsigned int i = 0; i < spotLights.size(); i++)
	//{
	//	std::string pointLightsStr;
	//	pointLightsStr = "spotLight[" + std::to_string(i) + "]";
	//	shader->SetVector3f((pointLightsStr + ".position").c_str(), spotLights[i]->position);
	//	shader->SetVector3f((pointLightsStr + ".direction").c_str(), spotLights[i]->direction);
	//	shader->SetVector3f((pointLightsStr + ".ambient").c_str(),  spotLights[i]->ambient);
	//	shader->SetVector3f((pointLightsStr + ".diffuse").c_str(),  spotLights[i]->diffuse);
	//	shader->SetVector3f((pointLightsStr + ".specular").c_str(), spotLights[i]->specular);
	//	shader->SetFloat(	(pointLightsStr + ".constant").c_str(), spotLights[i]->constant);
	//	shader->SetFloat(   (pointLightsStr + ".linear").c_str(),   spotLights[i]->linear);
	//	shader->SetFloat(   (pointLightsStr + ".quadratic").c_str(),spotLights[i]->quadratic);

	//	shader->SetFloat((pointLightsStr + ".cutOff").c_str(), glm::cos(glm::radians(12.5f)));
	//	shader->SetFloat((pointLightsStr + ".outerCutOff").c_str(), glm::cos(glm::radians(35.0f)));

	//}
	//set directional light uniform
	shader->SetVector3f("dirLight.direction", dirLight->direction);
	shader->SetVector3f("dirLight.ambient", dirLight->ambient);
	shader->SetVector3f("dirLight.diffuse", dirLight->diffuse);
	shader->SetVector3f("dirLight.specular", dirLight->specular);
}

void renderer::setShaderMatrices(transform transf, Shader& shader, Camera* camera)
{
	shader.use();

	glm::mat4 model(1.0f);

	model = glm::translate(model, transf.position);
	model = model * glm::toMat4(transf.orientation);
	model = glm::scale(model, transf.scale);

	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);

	projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	shader.SetMatrix4("projection", projection);

	view = camera->GetViewMatrix();
	shader.SetMatrix4("view", view);

	shader.SetMatrix4("modelMatrix", model);
}

void renderer::setModelUniforms(Shader& shader, transform transf)
{
	shader.use();
	glm::mat4 model(1.0f);

	model = glm::translate(model, transf.position);
	model = model * glm::toMat4(transf.orientation);
	model = glm::scale(model, transf.scale);

	shader.SetMatrix4("modelMatrix", model);
}

void renderer::setCommonShaderUniforms(Shader& shader, Camera* camera)
{
	shader.use();
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	shader.SetVector3f("viewPos", camera->Position);

	projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	shader.SetMatrix4("projection", projection);

	view = camera->GetViewMatrix();
	shader.SetMatrix4("view", view);
}

void renderer::createScreenQuad()
{
	// setup plane VAO
	glGenVertexArrays(1, &this->screenQuadVAO);
	glGenBuffers(1, &this->screenQuadVBO);
	glBindVertexArray(this->screenQuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->screenQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->quadVertices), &this->quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void renderer::renderScreenQuad()
{
	glBindVertexArray(this->screenQuadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void renderer::setDebugDepthQuadShader(Shader* shader)
{
	this->debugDepthQuad = shader;
}

void renderer::generateCubeDepthMap(unsigned int* depthCubeMap, unsigned int* depthCubeMapFBO)
{
	glGenFramebuffers(1, depthCubeMapFBO);

	glGenTextures(1, depthCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *depthCubeMap);
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindFramebuffer(GL_FRAMEBUFFER, *depthCubeMapFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, *depthCubeMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE0, 0);
}

void renderer::generateScreenEffectBuffer(unsigned int* hdrFBO, unsigned int* depthRBO, unsigned int* colorBuffer)
{
	glGenFramebuffers(1, hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, *hdrFBO);

	glGenTextures(1, &this->colorBuffer);
	glBindTexture(GL_TEXTURE_2D, this->colorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->SCR_WIDTH, this->SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *colorBuffer, 0);

	glGenRenderbuffers(1, depthRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, *depthRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->SCR_WIDTH, this->SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *depthRBO);


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAME::BUFFER::NOT::COMPLETE\n";

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void renderer::setScreenEffectShader(Shader* shader)
{
	this->screenEffectShader = shader;
	this->screenEffectShader->SetInteger("hdrBuffer", 0);
}

void renderer::renderPhysicsWorldDebugger(Shader* shader, PhysicsWorld* world, scene* scene)
{
	std::vector <debugTriangles> triangles;
	triangles = world->debugRenderer();
	if(triangles.size() > 0)
	{

		unsigned int vao, vbo;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), &triangles[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		shader->use();

		glBindVertexArray(vao);

		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);

		view = scene->getCurrentCamera()->GetViewMatrix();
		projection = glm::perspective(glm::radians(scene->getCurrentCamera()->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, near_plane, far_plane);

		shader->SetMatrix4("view", view);
		shader->SetMatrix4("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, sizeof(triangles) * 3);
		glBindVertexArray(0);
		//std::cout << "triangles drawing:" << std::endl;
	}
}
