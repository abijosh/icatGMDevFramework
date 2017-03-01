#include "Header.h"


Renderer::Renderer()
	: m_red(50 / 256.0f)
	, m_green(50 / 256.0f)
	, m_blue(50 / 256.0f)
	, m_alpha(1)
{
}


Renderer::~Renderer()
{
	delete m_pCamera;
}

void Renderer::setWindowPointer(GLFWwindow* windowPointer){
	mp_window = windowPointer;
}

void Renderer::prepare(){

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(m_red, m_green, m_blue, m_alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::updateShaderLocationValues(Entity* EntityPointer){
	Shader* ShaderPtr = EntityPointer->getModelPointer()->getMaterial()->getShaderPointer();
	
	glUniform1i(ShaderPtr->gettextureLocation(), 0);
	
	glUniformMatrix4fv(ShaderPtr->getViewMatrixLocation(), 1, GL_FALSE,
		glm::value_ptr(m_pCamera->mvpMatrix()));
	
	glUniformMatrix4fv(ShaderPtr->getTransformMatrixLocation(), 1, GL_FALSE,
		glm::value_ptr(EntityPointer->getTransformMatrix()));

}

void Renderer::renderEntity(Entity* EntityPointer){

		if (EntityPointer->isActive()) {
			TexturedModel *modelPointer = EntityPointer->getModelPointer();
			modelPointer->getMaterial()->getShaderPointer()->start();
			updateShaderLocationValues(EntityPointer);

			glActiveTexture(0);
			glBindTexture(GL_TEXTURE_2D, modelPointer->getMaterial()->getTextureID());

			glBindVertexArray(modelPointer->getRawModel()->getVaoID());

			glDrawElements(GL_TRIANGLES, modelPointer->getRawModel()->getFaceCount() * 3, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);

			modelPointer->getMaterial()->getShaderPointer()->stop();

			auto children = EntityPointer->getChildren();
			for (Entity* child : children){
				renderEntity(child);
			}
		}
}

void Renderer::renderScene(Scene* scenePointer)
{
	auto entities = scenePointer->getEntities();
	/*
	std::vector<Entity*>::iterator itrCurr, itrEnd;
	itrCurr = entities.begin();
	itrEnd = entities.end();
	for (; itrCurr < itrEnd; itrCurr++){
		renderEntity(*itrCurr);
	}
	*/
	for (Entity* EntityPointer : entities){
		renderEntity(EntityPointer);
	}
}


void Renderer::postRender(){
	glfwSwapBuffers(mp_window);
}

void Renderer::initializeCamera(int windowWidth, int windowHeight){
	m_pCamera = new Camera(windowWidth, windowHeight);
}

void Renderer::setAspectRatio(float aspectRatio) {
    m_pCamera->setAspectRatio(aspectRatio);
}

Camera* Renderer::getCamera(){
	return m_pCamera;
}