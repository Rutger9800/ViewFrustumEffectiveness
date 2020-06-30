#ifndef SPECIALSCENE_HPP
#define SPECIALSCENE_HPP

#include "mge/core/AbstractGame.hpp"
#include"mge/materials/ADSColorMaterial.hpp"

class DebugHud;
class ShaderUtil;

class SpecialScene: public AbstractGame
{

public:
	SpecialScene();
	virtual ~SpecialScene();

	virtual void initialize();

protected:
	virtual void _initializeScene();

	virtual void _render();

private: 
	DebugHud* _hud;

	void _updateHud();

	SpecialScene(const SpecialScene&);
	SpecialScene& operator=(const SpecialScene&);

};


#endif