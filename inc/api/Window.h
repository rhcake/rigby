#pragma once


#include <string>
#include <SDL2/SDL.h>


class Window {
public:
	void SetTitle(const char *title);
	void Create();
	void Destroy();
	void ConsumeInput();
private:
	SDL_Window *sdlwin;
	SDL_GLContext context;
};
