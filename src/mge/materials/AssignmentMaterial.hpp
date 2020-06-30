#ifndef ASSIGNMAT_HPP
#define ASSIGNMAT_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"
#include "mge/core/Camera.hpp"

class ShaderProgram;
class Texture;

/**
 * This is a material class I created with help from a school assignment.
 */
class AssignmentMaterial : public AbstractMaterial
{
    public:
        AssignmentMaterial(Texture* pDiffuseTexture, float pSpecStrength, float pShininess, float pAmbientStrength);
        virtual ~AssignmentMaterial();

        virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        void setDiffuseTexture (Texture* pDiffuseTexture);

    protected:
    private:
        static ShaderProgram* _shader;
        static void _initShader();

        //cache all identifiers for uniforms & attributes
        static GLint _uMVPMatrix, _uDiffuseTexture, _aVertex
            , _aNormal, _aUV, _lightIndex
            , _modelMatIndex, _cameraPosIndex, _uLightCol
            , _uSpecStrength, _uShine, _uAmbiStrength;
        
        Camera* mainCam;
        glm::vec3 camPos;
        glm::vec3 lightColor;
        Texture* _diffuseTexture;
        float specStrength, shininess, ambientStrength;

        AssignmentMaterial(const AssignmentMaterial&);
        AssignmentMaterial& operator=(const AssignmentMaterial&);

};

#endif // TEXTUREMATERIAL_HPP
