#include "glm.hpp"

#include "AssignmentMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* AssignmentMaterial::_shader;

GLint AssignmentMaterial::_uMVPMatrix = 0;
GLint AssignmentMaterial::_uDiffuseTexture = 0;
GLint AssignmentMaterial::_aVertex = 0;
GLint AssignmentMaterial::_aNormal = 0;
GLint AssignmentMaterial::_aUV = 0;
GLint AssignmentMaterial::_lightIndex = 0;
GLint AssignmentMaterial::_modelMatIndex = 0;
GLint AssignmentMaterial::_cameraPosIndex = 0;
GLint AssignmentMaterial::_uLightCol = 0;
GLint AssignmentMaterial::_uSpecStrength = 0;
GLint AssignmentMaterial::_uShine = 0;
GLint AssignmentMaterial::_uAmbiStrength = 0;

AssignmentMaterial::AssignmentMaterial(Texture * pDiffuseTexture, float pSpecStrength, float pShininess, float pAmbientStrength):_diffuseTexture(pDiffuseTexture) {
    _initShader();
    specStrength = pSpecStrength;
    shininess = pShininess;
    ambientStrength = pAmbientStrength;
    lightColor = glm::vec3(1, 0.5f, 1);//make pink so you know somehting is wrong if you don't set the color correctly
}

AssignmentMaterial::~AssignmentMaterial() {}

void AssignmentMaterial::_initShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"AssignmentShader.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"AssignmentShader.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
        _lightIndex = _shader->getUniformLocation("lightPos");
        _modelMatIndex = _shader->getUniformLocation("modelMatrix");
        _cameraPosIndex = _shader->getUniformLocation("viewPos");
        _uLightCol = _shader->getUniformLocation("lightColor");
        _uSpecStrength = _shader->getUniformLocation("specularStrength");
        _uShine = _shader->getUniformLocation("shininess");
        _uAmbiStrength = _shader->getUniformLocation("ambientStrength");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");


    }
}

void AssignmentMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void AssignmentMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;
    mainCam = pWorld->getMainCamera();

    _shader->use();

    if (pWorld->getLightCount() > 0) {

        glm::vec3 lightPos = pWorld->getLightAt(0)->getWorldPosition();
        glUniform3f(_lightIndex, lightPos.x,lightPos.y,lightPos.z); 
        lightColor = pWorld->getLightAt(0)->getColor();
    }
    camPos = mainCam->getWorldPosition();
    glUniform3fv(_cameraPosIndex, 1, glm::value_ptr(camPos)); //glm value ptr creates a pointer that behaves like a regular float but when copied, also copies the data
    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0

    glUniform1i (_uDiffuseTexture, 0);
    glUniform3fv(_uLightCol,1,  glm::value_ptr(lightColor));
    glUniform1f(_uSpecStrength, specStrength);
    glUniform1f(_uShine, shininess);
    glUniform1f(_uAmbiStrength, ambientStrength);

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
    glUniformMatrix4fv(_modelMatIndex, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
    //inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
