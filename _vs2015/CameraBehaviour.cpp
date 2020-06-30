#include "CameraBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/AbstractGame.hpp"


CameraBehaviour::CameraBehaviour(float pDistance, float pMaxTilt, float degPerSecond, GameObject* pTarget, sf::RenderWindow* pWindow) :AbstractBehaviour()
{
	assert(pTarget != nullptr);//make sure a target is set
	distance = pDistance;
	maxTilt = pMaxTilt;
	rotationSpeed = degPerSecond;
	target = pTarget;
	_window = pWindow;
	mouseControlOffset = 200;//this allows the user to control the axis seperately if they should want to
}


CameraBehaviour::~CameraBehaviour()
{
}

void CameraBehaviour::update(float pStep)
{
	float windowCenterX = _window->getPosition().x + (config::SCREENX / 2.0f);
	float windowCenterY = _window->getPosition().y + (config::SCREENY / 2.0f);
	targetPos = target->getWorldPosition();

	//move in a direction here, later on correct it with lookat function
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (sf::Mouse::getPosition().x < windowCenterX - mouseControlOffset) {//left side of screen
			_owner->translate(glm::vec3(-rotationSpeed *pStep, 0.0f, 0.0f));
		}
		if (sf::Mouse::getPosition().x > windowCenterX + mouseControlOffset) {
			_owner->translate(glm::vec3(rotationSpeed * pStep, 0.0f, 0.0f));
		}
		if (sf::Mouse::getPosition().y > windowCenterY + mouseControlOffset) {//bottom of screen
			_owner->translate(glm::vec3(0.0f, -rotationSpeed * pStep, 0.0f));
		}
		if (sf::Mouse::getPosition().y < windowCenterY -  mouseControlOffset) {
			_owner->translate(glm::vec3(0.0f, rotationSpeed * pStep, 0.0f));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		rotationSpeed /= 1.5000f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		rotationSpeed *= 1.5000f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		distance -= rotationSpeed * pStep;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		distance += rotationSpeed * pStep;
	}

	glm::mat4 lookat = glm::lookAt(_owner->getWorldPosition(), targetPos, glm::vec3(0, 1, 0));//orient the camera back to the target
	_owner->setTransform(glm::inverse(lookat));//since the mge uses the inverse of the transform as viewmatrix
	//now inversing the produced matrix to create the transform. Which the engine then uses inversed again as view matrix //NOTE: not very efficient

	//this makes the camera keep the correct distance to the target
	_owner->setLocalPosition(targetPos);//set position of camera itself to target
	_owner->translate(glm::vec3(0, 0, distance));//put the camera back at the right distance
}
