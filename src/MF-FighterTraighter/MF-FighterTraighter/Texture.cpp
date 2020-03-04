#include "Texture.h"
#include <exception>
#include <assert.h>

void Texture::cleanTexture() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture); // delete current texture
		texture = nullptr;
		width = 0;
		height = 0;
	}
}

void Texture::load(string filename, int cols, int rows) {
	SDL_Surface* tempSurface;
	tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr)
		std::cout << ("Me cago en Dios") << endl; // TODO: change to proper exception
	else {
		cleanTexture();
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		//assert(texture == nullptr); // For debugging

		nCols = cols;
		nRows = rows;
		width = tempSurface->w;
		height = tempSurface->h;
		fWidth = width / cols;
		fHeight = height / rows;

		SDL_FreeSurface(tempSurface);
	}
}

// Render whole image, or first frame
void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const{
	render(destRect, 0, 0, 0, flip);
}

void Texture::render(Vector2D pos, int widthMul, int heightMult, SDL_RendererFlip flip) const
{
	SDL_Rect rect = { pos.getX(), pos.getY(), width * widthMul, height *  heightMult };
	render(rect, 0, 0, 0, flip);
}

// Render only a frame, or at an angle
void Texture::render(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fWidth * col; srcRect.y = fHeight * row;
	srcRect.w = fWidth; srcRect.h = fHeight;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}

// Clip:
void Texture::render(const SDL_Rect& dest, double angle, const SDL_Rect& clip) const {
	if (texture) {
		SDL_RenderCopyEx(renderer, texture, &clip, &dest, angle, nullptr,
			SDL_FLIP_NONE);
	}
}

// Destino + rotaci�n:
void Texture::render(const SDL_Rect& dest, double angle) const {
	SDL_Rect clip = { 0, 0, width, height };
	render(dest, angle, clip);
}