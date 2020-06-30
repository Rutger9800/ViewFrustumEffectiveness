#pragma once
#include "glm.hpp"
#include "plane.hpp"

#define FRUSTUM_NEAR  0
#define FRUSTUM_FAR   1
#define FRUSTUM_LEFT  2
#define FRUSTUM_RIGHT 3
#define FRUSTUM_UP    4
#define FRUSTUM_DOWN  5

class Frustum
{
public: 
	Frustum(const glm::mat4x4& m);
	bool SphereIntersect(const glm::vec3 vecCenter, float flRadius);

	Plane p[6];

};

