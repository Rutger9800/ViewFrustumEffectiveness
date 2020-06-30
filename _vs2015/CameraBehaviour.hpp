#ifndef CAMERABEHAVIOUR_HPP
#define CAMERABEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/graphics.hpp"
#include <assert.h>
#include "glm.hpp"
class CameraBehaviour : public AbstractBehaviour
{
public:
	CameraBehaviour(float pDistance, float pMaxTilt, float rotateSpeed, GameObject* pTarget, sf::RenderWindow* pWindow);
	virtual ~CameraBehaviour();

	virtual void update(float pStep);
private:
	int mouseControlOffset;
	float distance, maxTilt, rotationSpeed;
	GameObject* target;
	sf::RenderWindow* _window;
	glm::vec3 targetPos;
};
#endif

