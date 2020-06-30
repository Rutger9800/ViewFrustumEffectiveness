#include "WorldGen.hpp"

WorldGen::WorldGen(Mesh* meshToSpawn) :GameObject("WorldGen", glm::vec3(0,0,0))
{
	AbstractMaterial* orangeMaterial = new ADSColorMaterial(glm::vec3(1,0.5f,0), 1.0f, 32, 1.0f);
	int objRoot = glm::sqrt(576);// 576 is 24 squared, creating 576 objects
	int objAmountEachDir = objRoot / 2;
	int objectCounter = 0;
	// !! following code assumes the sqrt answer is an even number !!
	for (int x = -objAmountEachDir; x <= objAmountEachDir; x++)
	{
		if (x == 0) x += 1;//don't create a center row, since this would create more objects then asked for
		//std::cout << "WORLDGEN creating row " << x << std::endl;
		for (int z = -objAmountEachDir; z <= objAmountEachDir; z++) 
		{
			if (z == 0) z += 1;
			GameObject* spawnObj = new GameObject("spawnObj " + std::to_string(x)+ ", " + std::to_string(z), glm::vec3(x*2, 0, z*2), meshToSpawn, orangeMaterial);
			objectCounter++;
			this->add(spawnObj);
		}
	}
	std::cout << std::to_string(objectCounter) << " objects created by World Generator" << std::endl;
}

WorldGen::~WorldGen(){}