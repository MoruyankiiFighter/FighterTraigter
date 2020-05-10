#pragma once
#include "Component.h"
#include "Slider.h"
#include "TextComponent.h"

class OptionsLogic :
	public Component
{
public:
	OptionsLogic(Slider* resolutionsSlider, TextComponent* resolutionsText, Slider* brightnessSlider, TextComponent* brightnessText,
		Slider* musicSlider, TextComponent* musicText, Slider* SFXSlider, TextComponent* SFXText) :
		Component(ecs::OptionsLogic), resolutionsSlider_(resolutionsSlider), resolutionsText_(resolutionsText), brightnessSlider_(brightnessSlider),
		brightnessText_(brightnessText), musicSlider_(musicSlider), musicText_(musicText), SFXSlider_(SFXSlider), SFXText_(SFXText)  {};
	void init() override;
	void SetElements();
	void update() override;
protected:
	Slider* resolutionsSlider_;
	TextComponent* resolutionsText_;
	Slider* brightnessSlider_;
	TextComponent* brightnessText_;
	
	Slider* musicSlider_;
	TextComponent* musicText_;
	Slider* SFXSlider_;
	TextComponent* SFXText_;

};

