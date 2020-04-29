﻿#include "Training.h"
#include "Entity.h"
#include "PlayerController.h"
#include "RenderImage.h"
#include "Jump.h"
#include "PauseMenu.h"
#include "Crouch.h"
#include "SacoTimer.h"
#include "FactoryMk.h"
#include "PunchingBagOnHit.h"
#include "FloorOnHit.h"
#include "UITransform.h"
#include "UITimer.h"
#include "UIHealthbar.h"
#include "SacoFunction.h"
Training::Training(App* app) : GameState(app)
{
	init();
}

void Training::init()
{
	world = new b2World(b2Vec2(0.0f, 9.81f));//inicializamos el mundo para las f�sicas de b2D
	//---------Debuggear hitbox-------------------------------------------
	debugInstance = new SDLDebugDraw(app_->getRenderer());
	world->SetDebugDraw(debugInstance);
	debugInstance->SetFlags(b2Draw::e_aabbBit);
	resJumpListener = new ResetJumpListener();
	world->SetContactListener(resJumpListener);
	
	FactoryMk::addMkToGame(app_, this, world, 1, { SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_Q, SDL_SCANCODE_E, SDL_SCANCODE_Z, SDL_SCANCODE_X,
		SDL_SCANCODE_SPACE, SDL_SCANCODE_R, SDL_SCANCODE_1, SDL_SCANCODE_2 }, PLAYER_1, PLAYER_2 | BOUNDARY | P_BAG);
	FactoryMk::addMkToGame(app_, this, world, -1, { SDL_SCANCODE_J, SDL_SCANCODE_L, SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_U, SDL_SCANCODE_O, SDL_SCANCODE_N, SDL_SCANCODE_M,
		SDL_SCANCODE_0, SDL_SCANCODE_H, SDL_SCANCODE_8, SDL_SCANCODE_9 }, PLAYER_2, PLAYER_1 | WALL | BOUNDARY);

	saco = entManager_.addEntity();
	PhysicsTransform* pBpT = saco->addComponent<PhysicsTransform>(Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h - 455), Vector2D(10, 10), 150, 500, 0, world, P_BAG, PLAYER_1 | PLAYER_2, false);
	app_->getHitboxMng()->addMainHitbox(pBpT->getMainFixture());
	saco->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::Player));
	saco->addComponent<PunchingBagOnHit>();
	Health* sacoHealth = saco->addComponent<Health>(200);
	saco->addComponent<SacoFunction>(saco);
	//saco->addComponent<SacoTimer>(5000);


	Entity* timer = entManager_.addEntity();
	timer->addComponent<UITransform>(Vector2D(0, 120), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(200, 50), Vector2D(400, 100));
	timer->addComponent<TextComponent>("0000", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 45, TextComponent::Center);
	timer->addComponent<UITimer>(UITimer::Minutes);
	

	Entity* healthbarBack = entManager_.addEntity();
	healthbarBack->addComponent<UITransform>(Vector2D(0, 40), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(850, 20), Vector2D(1700, 40));
	healthbarBack->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::HealthbarBack));

	Entity* healthbarL = entManager_.addEntity();
	healthbarL->addComponent<UITransform>(Vector2D(0, 40), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(0, 20), Vector2D(850, 40));
	healthbarL->addComponent<UIHealthbar>(sacoHealth, app_->getAssetsManager()->getTexture(AssetsManager::HealthbarSaco));
	Entity* healthbarR = entManager_.addEntity();
	healthbarR->addComponent<UITransform>(Vector2D(0, 40), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(850, 20), Vector2D(850, 40));
	healthbarR->addComponent<UIHealthbar>(sacoHealth, app_->getAssetsManager()->getTexture(AssetsManager::HealthbarSaco), true);

	Entity* character1 = entManager_.addEntity();
	character1->addComponent<UITransform>(Vector2D(100, 70), Vector2D(), Vector2D(70, 70), Vector2D(140, 140));
	character1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection))->setFrame(2, 0);
	Entity* character2 = entManager_.addEntity();
	character2->addComponent<UITransform>(Vector2D(-100, 70), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(70, 70), Vector2D(140, 140));
	character2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection))->setFrame(2, 0);

	Entity* floor = entManager_.addEntity();
	PhysicsTransform* FpT = floor->addComponent<PhysicsTransform>(Vector2D(960, 1100), Vector2D(0, 0), 1920, 450, 0, world, BOUNDARY, EVERYTHING, false);
	floor->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::Player));
	//floor->addComponent<FloorOnHit>();
	app_->getHitboxMng()->addFloorHitbox(FpT->getMainFixture());

	//Walls
	Entity* wall1 = entManager_.addEntity();
	PhysicsTransform* W1pT = wall1->addComponent<PhysicsTransform>(Vector2D(-50, 540), Vector2D(0, 0), 100, 1080, 0, world, WALL, EVERYTHING, false);
	app_->getHitboxMng()->addFloorHitbox(W1pT->getMainFixture());

	Entity* wall2 = entManager_.addEntity();
	PhysicsTransform* W2pT = wall2->addComponent<PhysicsTransform>(Vector2D(1970, 540), Vector2D(0, 0), 100, 1080, 0, world, WALL, EVERYTHING, false);
	app_->getHitboxMng()->addFloorHitbox(W2pT->getMainFixture());
}

void Training::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getStateMachine()->pushState(new PauseMenu(app_));
	}
	GameState::handleInput();
}

void Training::update()
{
	
		app_->getHitboxMng()->update();		//es posible que esto sea un sistema
		GameState::update();
		world->Step(1.0 / 30, 8, 3);//update box2d
	
}


void Training::render() {
	SDL_RenderClear(app_->getRenderer());
	for (auto it = entManager_.getScene().begin(); it != entManager_.getScene().end(); ++it) {
		(*it)->render();
	}
	world->DrawDebugData();
	SDL_RenderPresent(app_->getRenderer());
}

Training::~Training()
{
	for (auto vec : vecMov) {
		delete vec;

	}
	app_->getHitboxMng()->clear();

	delete world;
	delete debugInstance;
	delete resJumpListener;
}