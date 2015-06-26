#include <api/Window.h>
#include <debug.h>
#include <SDL2/SDL.h>
#include <gl.h>


void Window::SetTitle(const char *title) {
	log("title: [%s]", title);
	//SDL_SetWindowTitle(sdlwin, title);
}


void Window::Destroy() {
	log("destroying window");

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(sdlwin);
    SDL_Quit();
}


void Window::Create() {
	log("creating window");

	SDL_Init(SDL_INIT_VIDEO);

	int err = 0;

	err |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	err |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	err |= SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	err |= SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 	16);

	err |= SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	err |= SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 	8);
	err |= SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 	8);
	err |= SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 	8);
	err |= SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 	0);

	err |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
		SDL_GL_CONTEXT_DEBUG_FLAG |
		SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

	err |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	log("attr err: %d", err);

	sdlwin = SDL_CreateWindow(
		"rigby",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	context = SDL_GL_CreateContext(sdlwin);

	if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		log("*** couldn't load GL");
	} else {
		log("GL funcs loaded");
	}

	//vsync
	SDL_GL_SetSwapInterval(1);

	SDL_SetWindowTitle(sdlwin, "Rigby");
}


void Window::ConsumeInput() {

	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_KEYDOWN:
				if (e.key.keysym.sym != SDLK_ESCAPE)
					break;
			case SDL_QUIT:
				//running = false;
				break;
		}
	}
}