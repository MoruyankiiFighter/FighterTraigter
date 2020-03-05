#include "GameStateMachine.h"


GameStateMachine::GameStateMachine(){ }

GameStateMachine::~GameStateMachine()
{
	while (!states.empty()) {
		delete states.top();
		popState();
	}
}

GameState* GameStateMachine::getCurrentState() //if there is a state then returns the top of the stack
{
	if (!states.empty()) { 
		return states.top();
	}
	else {
		return nullptr;
	}
}
//
////Return second state
//GameState* GameStateMachine::getSecond() {
//	GameState* top = getCurrentState();
//	popState();
//	GameState* secondTop = getCurrentState();
//	pushState(top);
//	return secondTop;
//}