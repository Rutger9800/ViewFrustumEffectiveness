#pragma once
#include "glm.hpp"

class Plane
{
public:
	glm::vec3 n; //normal of this plane
	float d; //not really distance from the plane to origin

	void Normalize() {
		glm::normalize(n);
	}

};

