#pragma once
#ifndef WORLDGEN_HPP
#define WORLDGEN_HPP

#include "../SpecialScene.hpp"


/**
Class that generates the objects in the world so we're able to test the view frustum culling
*/
class WorldGen : public GameObject
{
public:
	WorldGen(Mesh* objectToSpawn, int amountToSpawn);
	~WorldGen();


};

#endif

