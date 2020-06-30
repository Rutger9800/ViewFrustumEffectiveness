#include "glm.hpp"

#include "ADSColorMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"


ShaderProgram* ADSColorMaterial::_shader = NULL;

GLint ADSColorMaterial::_uMVPMatrix = 0;
GLint ADSColorMaterial::_aVertex = 0;
GLint ADSColorMaterial::_aNormal = 0;
GLint ADSColorMaterial::_aUV = 0;
GLint ADSColorMaterial::_lightIndex = 0;
GLint ADSColorMaterial::_modelMatIndex = 0;
GLint ADSColorMaterial::_cameraPosIndex = 0;
GLint ADSColorMaterial::_uLightCol = 0;
GLint ADSColorMaterial::_uSpecStrength = 0;
GLint ADSColorMaterial::_uShine = 0;
GLint ADSColorMaterial::_uAmbiStrength = 0;
GLint ADSColorMaterial::_uColor = 0;

ADSColorMaterial::ADSColorMaterial(glm::vec3 pColor, float pSpecStrength, float pShininess, float pAmbientStrength) {
	_initShader();
	color = pColor;
	specStrength = pSpecStrength;
	shininess = pShininess;
	ambientStrength = pAmbientStrength;
	lightColor = glm::vec3(1, 0.5f, 1);//if you dont set the color, or there is no light, it will be pink
}

ADSColorMaterial::~ADSColorMaterial() {}

void ADSColorMaterial::_initShader() {
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "ADSColor.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "ADSColor.fs");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		_lightIndex = _shader->getUniformLocation("lightPos");
		_modelMatIndex = _shader->getUniformLocation("modelMatrix");
		_cameraPosIndex = _shader->getUniformLocation("viewPos");
		_uLightCol = _shader->getUniformLocation("lightColor");
		_uSpecStrength = _shader->getUniformLocation("specularStrength");
		_uShine = _shader->getUniformLocation("shininess");
		_uAmbiStrength = _shader->getUniformLocation("ambientStrength");
		_uColor = _shader->getUniformLocation("fragment_color");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
	}
}


void ADSColorMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	/*if (mainCam == nullptr) */mainCam = pWorld->getMainCamera();

	ViewFrustum = Frustum(mainCam->getProjection());

	//TODO: get object position over here
	//if(!ViewFrustum.SphereIntersect())

	_shader->use();

	//Print the number of lights in the scene and the position of the first light.
	//It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
	if (pWorld->getLightCount() > 0) {
		glUniform3fv(_lightIndex, 1, glm::value_ptr(pWorld->getLightAt(0)->getWorldPosition()));
		//RUTGER: glm value ptr creates a pointer that behaves like a regular float but when copied, also copies the data
		lightColor = pWorld->getLightAt(0)->getColor();
	}
	camPos = mainCam->getWorldPosition();
	glUniform3fv(_cameraPosIndex, 1, glm::value_ptr(camPos));

	glUniform3fv(_uLightCol, 1, glm::value_ptr(lightColor));
	glUniform3fv(_uColor, 1, glm::value_ptr(color));
	glUniform1f(_uSpecStrength, specStrength);
	glUniform1f(_uShine, shininess);
	glUniform1f(_uAmbiStrength, ambientStrength);

	//pass in a precalculate mvp matrix (see texture material for the opposite)

	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	glUniformMatrix4fv(_modelMatIndex, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
