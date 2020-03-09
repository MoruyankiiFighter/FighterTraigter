#pragma once
#include "GameState.h"
#include "Texture.h"

class App;

void SetFullScreen(App* app);



class OptionsMenu:public GameState
{
public:
	OptionsMenu(App* app);
	virtual ~OptionsMenu();

	void init() override;
	virtual void update() override;
	virtual void render() override;
	void handleInput();

private:
	Texture* controls_ = nullptr;
};
