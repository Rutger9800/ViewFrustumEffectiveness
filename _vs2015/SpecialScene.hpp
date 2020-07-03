#ifndef SPECIALSCENE_HPP
#define SPECIALSCENE_HPP

#include "mge/core/AbstractGame.hpp"
#include"mge/materials/ADSColorMaterial.hpp"
#include "Classes/CSVwriter.hpp"

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
	CSVwriter* _csv;
	int objCreatedByGen= 66;
	bool VFCbool = false;

	void _updateHud();

	SpecialScene(const SpecialScene&);
	SpecialScene& operator=(const SpecialScene&);

};


#endif