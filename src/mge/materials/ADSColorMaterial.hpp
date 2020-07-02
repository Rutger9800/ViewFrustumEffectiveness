#ifndef ADSCOLMAT_HPP
#define ADSCOLMAT_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"
#include "mge/core/Camera.hpp"
#include "../_vs2015/Classes/Frustum.hpp"
#include "mge/core/GameObject.hpp"


class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class ADSColorMaterial : public AbstractMaterial
{
    public:
        ADSColorMaterial(glm::vec3 pColor, float pSpecStrength, float pShininess, float pAmbientStrength);
        virtual ~ADSColorMaterial();

        virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
        GameObject* GetObject();
        void SetObject(GameObject* object);

    protected:
    private:
        static ShaderProgram* _shader;
        static void _initShader();
        Frustum ViewFrustum;
        GameObject* gameObject;

        //in this example we cache all identifiers for uniforms & attributes
        static GLint _uMVPMatrix, _uColor, _aVertex
            , _aNormal, _aUV,_lightIndex
            , _modelMatIndex, _cameraPosIndex, _uLightCol
            , _uSpecStrength, _uShine, _uAmbiStrength;
        
        Camera* mainCam;
        glm::vec3 camPos, color, lightColor;
        float specStrength, shininess, ambientStrength;

        ADSColorMaterial(const ADSColorMaterial&);
        ADSColorMaterial& operator=(const ADSColorMaterial&);

};

#endif // TEXTUREMATERIAL_HPP
