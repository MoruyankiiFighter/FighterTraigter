#include "MovementsMenu.h"
#include "Fight.h"
#include "OptionsMenu.h"
#include "Training.h"

#include "InputManager.h"

#include "Entity.h"

#include "RenderImage.h"
#include "Transform.h"
#include "Button.h"
#include "TextComponent.h"
#include "NavigationController.h"

#include "Font.h"

#include "App.h"
#include "consts.h"
#include "UIFactory.h"

MovementsMenu::MovementsMenu(App* app) : GameState(app)
{
	cout << "MovementsMenu" << endl;
	init();
}

MovementsMenu::~MovementsMenu()
{

}

void MovementsMenu::init()
{
	cout << "init" << endl;
	tuple < Entity*, Entity*> goBack = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(1), app_->getAssetsManager()->getFont(0), Vector2D(200, 150), WIDTH_BUTTON + 40, HEIGHT_BUTTON, 0, nullptr, GoBack, "Back", 150);

	Entity* movement = entManager_.addEntity();
	movement->addComponent<Transform>(Vector2D(700, 400), Vector2D(), WIDTH_BUTTON + 90, HEIGHT_BUTTON,0);
	movement->addComponent<TextComponent>("Movement ---> Arrows", app_->getAssetsManager()->getFont(0), 100);

	Entity* punch = entManager_.addEntity();
	punch->addComponent<Transform>(Vector2D(700,500), Vector2D(), WIDTH_BUTTON + 90, HEIGHT_BUTTON,0);
	punch->addComponent<TextComponent>("Punch ---> Q", app_->getAssetsManager()->getFont(0), 100);

	Entity* kick = entManager_.addEntity();
	kick->addComponent<Transform>(Vector2D(700, 600), Vector2D(), WIDTH_BUTTON + 90, HEIGHT_BUTTON,0);
	kick->addComponent<TextComponent>("Kick ---> W", app_->getAssetsManager()->getFont(0), 100);
	
	Entity* grab = entManager_.addEntity();
	grab->addComponent<Transform>(Vector2D(700, 700), Vector2D(), WIDTH_BUTTON + 90, HEIGHT_BUTTON, 0);
	grab->addComponent<TextComponent>("Grab ---> E", app_->getAssetsManager()->getFont(0), 100);

	Entity* block = entManager_.addEntity();
	block->addComponent<Transform>(Vector2D(700, 800), Vector2D(), WIDTH_BUTTON + 90, HEIGHT_BUTTON, 0);
	block->addComponent<TextComponent>("Block ---> D", app_->getAssetsManager()->getFont(0), 100);
}

void MovementsMenu::GoBack(App* app) {
	app->getStateMachine()->popState();
}