#pragma once
#include "baseState.h"
class mainMenu : public baseState
{
public:
	mainMenu();
	~mainMenu();

	void loadMedia() override;

	//handle mouse events
	void eventHandler(SDL_Event e) override;

	void update() override;
	void render() override;
	void clean() override;
	SDL_Texture* bg;
private:

	int alpha;
	//image* button;
};
