#include "Component.h"
#include "RenderImage.h"

using CallBackOnClick = void(App* app);

////callback para el juego
//void PauseCallback(App* app);


class Button : public Component {

public:
	//constructor
	Button(CallBackOnClick* call) : Component(ecs::Button) { callbackbutton = call; };
	//destructor
	virtual ~Button() {};

	void init() override;
	//handle the input of the mouse by the moment
	void handleInput() override;
	bool getSelect() { return select; };
	void setSelect(bool sel) { select = sel; };

private:
	Transform* trans_ = nullptr;
	CallBackOnClick* callbackbutton = nullptr;
	bool select = false;
};
