#include "image.h"
#include "constants.h"


image::image(int x, int y, int w, int h) {
	rect.w = w;
	rect.h = h;
	rect.x = x;
	rect.y = y;

	//texture = NULL;
	drawornot = true;
}

image::image(int x, int y) {
	rect.x = x;
	rect.y = y;
}

image::image() {};
image::~image() {}

void image::set_image(SDL_Texture* img) {
	if (img == NULL) std::cout << "what happened???" << std::endl;
	texture = img;
	set_blendmode();
	//get_settings();        causing image to not load?
}
void image::set_imagepos(SDL_Rect& imgpos) {
	rect = imgpos;
}
void image::get_settings() {
	SDL_QueryTexture(texture, NULL, NULL, &(rect.w), &rect.y);
}
void image::set_blendmode() {
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void image::set_alpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}

void image::autorender() {
	SDL_RenderCopy(gameM::renderer, texture, NULL, &rect);
	if (texture == NULL) printf("cannot copy texture! error: %s", SDL_GetError());
}

void image::render(SDL_Rect dst) {
	if (texture == NULL) printf("cannot copy texture! error: %s", SDL_GetError());
	else SDL_RenderCopy(gameM::renderer, texture, NULL, &dst);
	
}

void image::renderscrolling(int offset) {
	rect.x = offset;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;
	SDL_RenderCopy(gameM::renderer, texture, NULL, &rect);
	rect.x = offset + SCREEN_WIDTH;
	SDL_RenderCopy(gameM::renderer, texture, NULL, &rect);
}

bool image::inside() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Rect mousenow = { x,y,1,1 };
	bool inside = SDL_HasIntersection(&mousenow, &rect);
	return inside;
}
void image::flick_if_needed() {
	if (!inside()) {
		set_alpha(100);
	}
	else set_alpha(255);
}
void image::clean() {
	SDL_DestroyTexture(texture);
	texture = NULL;
}
