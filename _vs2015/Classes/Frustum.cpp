#include "Frustum.hpp"

Frustum::Frustum(const glm::mat4x4& m)
{
	//defines the planes of the frustrum as planes
	p[FRUSTUM_RIGHT].n.x = m[0][3] - m[0][0];
	p[FRUSTUM_RIGHT].n.y = m[1][3] - m[1][0];
	p[FRUSTUM_RIGHT].n.z = m[2][3] - m[2][0];
	p[FRUSTUM_RIGHT].d = m[3][3] - m[3][0];

	p[FRUSTUM_LEFT].n.x = m[0][3] + m[0][0];
	p[FRUSTUM_LEFT].n.y = m[1][3] + m[1][0];
	p[FRUSTUM_LEFT].n.z = m[2][3] + m[2][0];
	p[FRUSTUM_LEFT].d = m[3][3] + m[3][0];

	p[FRUSTUM_DOWN].n.x = m[0][3] + m[0][1];
	p[FRUSTUM_DOWN].n.y = m[1][3] + m[1][1];
	p[FRUSTUM_DOWN].n.z = m[2][3] + m[2][1];
	p[FRUSTUM_DOWN].d = m[3][3] + m[3][1];

	p[FRUSTUM_UP].n.x = m[0][3] - m[0][1];
	p[FRUSTUM_UP].n.y = m[1][3] - m[1][1];
	p[FRUSTUM_UP].n.z = m[2][3] - m[2][1];
	p[FRUSTUM_UP].d = m[3][3] - m[3][1];

	p[FRUSTUM_FAR].n.x = m[0][3] - m[0][2];
	p[FRUSTUM_FAR].n.y = m[1][3] - m[1][2];
	p[FRUSTUM_FAR].n.z = m[2][3] - m[2][2];
	p[FRUSTUM_FAR].d = m[3][3] - m[3][2];

	p[FRUSTUM_NEAR].n.x = m[0][3] + m[0][2];
	p[FRUSTUM_NEAR].n.y = m[1][3] + m[1][2];
	p[FRUSTUM_NEAR].n.z = m[2][3] + m[2][2];
	p[FRUSTUM_NEAR].d = m[3][3] + m[3][2];

	for (int i = 0; i < 6; i++)
		p[i].Normalize();//normalize the normals of the planes
}

bool Frustum::SphereIntersect(glm::vec3* vecCenter, float objRadius)
{

	for (int i = 0; i < 6; i++)//loop through the 6 planes that make up the view frustum
	{
		//testing the plane with a sphere by projecting the center vector onto the plane normals 
		// pointP dot normalN plus distance plus radius // if larger than 0 it's inside the plane
		if (glm::dot(*vecCenter, p[i].n) + p[i].d + objRadius <= 0) {
			return false;
		}
	}

	return true;
}
