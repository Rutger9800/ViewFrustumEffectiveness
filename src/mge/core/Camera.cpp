#include "glm.hpp"
#include "mge/core/Camera.hpp"

Camera::Camera( std::string pName, glm::vec3 pPosition, glm::mat4 pProjectionMatrix )
:	GameObject(pName, pPosition), _projection(pProjectionMatrix)
{
}

Camera::~Camera()
{
	//dtor
}

glm::mat4& Camera::getProjection() {
    return _projection;
}

glm::mat4& Camera::getViewMat() {
	return _view;
}

void Camera::setViewMat(glm::mat4 viewMatrix) {
	_view = viewMatrix;
}

