#include "WorldGen.hpp"
/**
	 Renders a specific game object in the world.
	@param meshToSpawn the mesh you want to spawn
	@param amountToSpawn amount of this mesh you want to spawn, highly recommend checking if the sqrt of this is even
	
*/
WorldGen::WorldGen(Mesh* meshToSpawn, int amountToSpawn) :GameObject("WorldGen", glm::vec3(0,0,0))
{
	
	AbstractMaterial* orangeMaterial = new ADSColorMaterial(glm::vec3(1,0.5f,0), 0.8f, 32, 1.0f);
	int objRoot = glm::sqrt(amountToSpawn);// 576 is 24 squared, creating 576 objects
	int objAmountEachDir = objRoot / 2;
	int objectCounter = 0;
	bool even = false;
	if (objRoot % 2 == 0) even = true;//if its even

	// !! following code assumes the sqrt answer is an even number !!
	for (int x = -objAmountEachDir; x <= objAmountEachDir; x++)
	{
		if (even)
		{
			if (x == 0) x += 1;//don't create a center row, since this would create more objects then asked for
		}
		//std::cout << "WORLDGEN creating row " << x << std::endl;
		for (int z = -objAmountEachDir; z <= objAmountEachDir; z++) 
		{
			if (even)//if its even
			{
				if (z == 0) z += 1;
			}
			GameObject* spawnObj = new GameObject("spawnObj " + std::to_string(x)+ ", " + std::to_string(z), glm::vec3(x*2, 0, z*2), meshToSpawn, orangeMaterial);
			objectCounter++;
			this->add(spawnObj);
		}
	}
	std::cout << std::to_string(objectCounter) << " objects created by World Generator" << std::endl;
}

WorldGen::~WorldGen(){}