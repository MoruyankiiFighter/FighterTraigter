#include "TextComponent.h"
#include "Entity.h"

TextComponent::TextComponent(std::string text, Font* font, int size) : Component(ecs::TextComponent),
text_(nullptr), transform_(nullptr), textString_(text), textSize_(size), font_(font)
{
}

void TextComponent::init()
{
	transform_ = entity_->getComponent<Transform>(ecs::Transform);
	font_->setFontSize(textSize_);
	text_ = new Text(app_->getRenderer(), textString_, font_);
}

void TextComponent::render()
{
	SDL_Rect dest = SDL_Rect();
	dest.x = transform_->getPosition().getX();
	dest.y = transform_->getPosition().getY();
	dest.w = textString_.length() * font_->getSymbolWidth() * transform_->getWMult();
	dest.h = textSize_ * transform_->getHMult();
	text_->render(dest);
}

void TextComponent::setText(std::string text)
{
	if (text != textString_) {
		text_->setText(text);
		textString_ = text;
	}
}

void TextComponent::setSize(int size)
{
	if (size != textSize_) {
		text_->setSize(size);
		textSize_ = size;
	}
}

void TextComponent::setFont(Font* font)
{
	if (font != font_) {
		text_->setFont(font);
		font_ = font;
	}
}

TextComponent::~TextComponent()
{
	delete text_;
}
