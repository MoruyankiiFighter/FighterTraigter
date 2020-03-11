#include "MainMenu.h"

#include "InputManager.h"

#include "Entity.h"

#include "RenderImage.h"
#include "Transform.h"
#include "Button.h"
#include "TextComponent.h"

#include "Font.h"

#include "App.h"
#include "consts.h"

MainMenu::MainMenu(App* app): GameState(app)
{
	
	cout << "Menu principal" << endl;
	init();
}

MainMenu::~MainMenu()
{

}

//void MainMenu::OnButtClick(string text) { std::cout << "Bot�n activado: "<< text << endl; };

void MainMenu::init()
{

	cout << "init" << endl;

	Entity* logo = new Entity();
	
	Transform* transform=logo->addComponent<Transform>();
	transform->setWidthHeight(WIDTH_LOGO, HEIGHT_LOGO);
	transform->setPosition(WINDOW_WIDTH_/2, POS_Y_LOGO);
	
	RenderImage* img = logo->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(2));
	scene.push_back(logo);

	arcade = new Entity();
	arcade->setApp(app_);
	Transform* t=arcade->addComponent<Transform>();
	t->setPosition(POS_X_ARCADE, POS_Y_ARCADE);
	t->setWidth(WIDTH_BUTTON); 
	t->setHeight(HEIGHT_BUTTON);
	t->setRotation(0);
	arcade->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(1));
	arcade->addComponent<TextComponent>("ARCADE", app_->getAssetsManager()->getFont(0), 20);
	arcade->addComponent<Button>(ArcadeCallback);
	scene.push_back(arcade);
}
