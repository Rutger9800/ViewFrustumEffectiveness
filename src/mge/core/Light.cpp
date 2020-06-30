#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/materials/ADSColorMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

Light::Light(const std::string& pName, const glm::vec3& pPosition, glm::vec3& aColor) :GameObject(pName, pPosition)
{
	color = aColor;
	_setVisibleCube(aColor);
}

glm::vec3 Light::getColor()
{
	return color;
}

Light::~Light() {
}

//Override setWorldRecursively to make sure we are registered
//to the world we are a part of.
void Light::_setWorldRecursively(World* pWorld) {

	//store the previous and new world before and after storing the given world
	World* previousWorld = _world;
	GameObject::_setWorldRecursively(pWorld);
	World* newWorld = _world;

	//check whether we need to register or unregister
	if (previousWorld != nullptr) previousWorld->unregisterLight(this);
	if (newWorld != nullptr) newWorld->registerLight(this);

}

void Light::_setVisibleCube(glm::vec3& pColor) {
	AbstractMaterial* colormat = new ADSColorMaterial(pColor, 0.1,0.1,1);//color of light with no reflections or something to cause distractions
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube.obj");
	GameObject* lightcube = new GameObject("lightcube", glm::vec3(0, 0, 0));

	lightcube->scale(glm::vec3(0.5, 0.5, 0.5));
	lightcube->setMesh(cubeMesh);
	lightcube->setMaterial(colormat);
	this->add(lightcube);
}



