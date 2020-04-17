#pragma once

#include "GameState.h"
#include "Texture.h"
#include <vector>
class App;

class ControlsMenu:public GameState
{
public:
	//constructor
	ControlsMenu(App* app);
	//destructor
	virtual ~ControlsMenu();

	//methods overrided from GameState where we create the entitys
	void init() override;
	void handleInput() override;

	//callback
	static void GoBack(App* app);

};
