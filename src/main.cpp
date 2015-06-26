#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <lua.hpp>
#include <debug.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <gl.h>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

using std::string;

static void game_loop();

SDL_Window *win = 0;
static SDL_Renderer *ren = 0;
static TTF_Font *font = 0;

static const SDL_Color WHITE = { 255, 255, 240, SDL_ALPHA_OPAQUE }; 

//function Label.renderText(x, y, text)
static int renderText(lua_State *lua) {

	int x = (int)lua_tonumber(lua, 1);
	int y = (int)lua_tonumber(lua, 2);
	const char *text = lua_tostring(lua, 3);

	SDL_Surface *surface = TTF_RenderText_Blended(
		font, text, WHITE);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(
		ren, surface);

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = surface->w;
	rect.h = surface->h;

	SDL_FreeSurface(surface);

	SDL_RenderCopy(ren, texture, 0, &rect);

	SDL_DestroyTexture(texture);

	return 0;
}

static const luaL_Reg LABEL_FUNCTIONS[] = {

    { "renderText", renderText},
    { 0, 0 }
};

static const char *config_str(lua_State *lua, const char *name) {
	lua_getglobal(lua, name);
	const char *tmp = lua_tostring(lua, 1);
	lua_pop(lua, 1);
	return tmp;
}

static MonoMethod *method_UpdateScripts;

int main(int argc, char **argv) {
	MonoDomain *domain = mono_jit_init("RigbyDomain");

	MonoAssembly *assembly = 
		mono_domain_assembly_open(domain, "Rigby.dll");

	MonoAssembly *game_assembly = 
		mono_domain_assembly_open(domain, "Demo.dll");

	MonoImage *image = mono_assembly_get_image(assembly);

	MonoClass *engine_class = 
		mono_class_from_name(image, "Rigby", "Engine");

	MonoMethodDesc *desc = 
		mono_method_desc_new(":Main", false);

	MonoMethod *method = 
			mono_method_desc_search_in_class(desc, engine_class);

	mono_method_desc_free(desc);

	MonoArray *mono_args =
		mono_array_new(domain, mono_get_string_class(), argc);

	for (int i = 0; i < argc; i++) {
		MonoString *str = mono_string_new(domain, argv[i]);
		mono_array_set(mono_args, MonoString *, i, str);
	}

	void *params[1] = { (void *)mono_args };

	mono_runtime_invoke(method, 0, params, 0);

    mono_jit_cleanup(domain);

	return 0;
}

int mainx(int argc, char **argv) {

	log("sizeof(char *): %d", sizeof(char *));

	MonoDomain *domain = domain = mono_jit_init("rigby");

	MonoAssembly *rigby_assembly = 
		mono_domain_assembly_open(domain, "Rigby.dll");

	{
		MonoImage *image = mono_assembly_get_image(rigby_assembly);

		MonoClass *my_class = 
			mono_class_from_name(image, "Rigby", "Engine");

		MonoMethodDesc *desc = 
			mono_method_desc_new(":UpdateScripts", false);

		method_UpdateScripts = 
			mono_method_desc_search_in_class(desc, my_class);
	}

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

	win = SDL_CreateWindow(
			"rigby",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640,
			480,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(win);

	if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		log("*** couldn't load GL");
	}

	log("GL funcs loaded");

	//vsync
	SDL_GL_SetSwapInterval(1);

	SDL_SetWindowTitle(win, "Rigby");

	ren = SDL_CreateRenderer(
		win,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	TTF_Init();

	font = TTF_OpenFont("fonts/Consolas.ttf", 18);

	if (font == 0) {
		log("** font not loaded");
	}

	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);

	//read config and load initial lua state
	luaL_loadfile(lua, "config.lua");
	lua_call(lua, 0, 0);

	const char *game_dll = config_str(lua, "game_dll");
	log("game_dll: [%s]", game_dll);

	MonoAssembly *game_assembly = 
		mono_domain_assembly_open(domain, game_dll);

	string first_level = string(config_str(lua, "first_level"));
	log("first_level: [%s]", first_level.c_str());

	int last = first_level.rfind(".");
	string ns = first_level.substr(0, last);
	log("namespace: [%s]", ns.c_str());

	string name = first_level.substr(last + 1);
	log("name: [%s]", name.c_str());

	/* we usually get the class we need during initialization */
	MonoImage *image = mono_assembly_get_image(game_assembly);
	MonoClass *my_class = mono_class_from_name(image, ns.c_str(), name.c_str());
	
	/* allocate memory for the object */
	MonoObject *my_class_instance = mono_object_new(domain, my_class);
	/* execute the default argument-less constructor */
	mono_runtime_object_init(my_class_instance);

	MonoMethodDesc *desc = mono_method_desc_new(":Load", false);

	MonoMethod *method = mono_method_desc_search_in_class(
		desc, my_class);

	mono_runtime_invoke(method, my_class_instance, 0, 0);

	//main loop
	game_loop();

	lua_close(lua);

	SDL_DestroyRenderer(ren);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);

	TTF_CloseFont(font);

	TTF_Quit();

    SDL_Quit();

    mono_jit_cleanup(domain);

	return EXIT_SUCCESS;
}

static void update_scripts(float delta);

static void game_loop() {

	bool running = true;
	Uint32 time = SDL_GetTicks();

	while (running) {

		Uint32 curr = SDL_GetTicks();
		Uint32 delta = curr - time;

		if (delta < 1)
			continue;

		// TODO: run queued tasks

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_KEYDOWN:
					if (e.key.keysym.sym != SDLK_ESCAPE)
						break;
				case SDL_QUIT:
					running = false;
					break;
			}
		}

		float secs = delta / 1000.f;

		// TODO: update
		update_scripts(secs);

		SDL_SetRenderDrawColor(
			ren,
			100,
			100,
			120,
			SDL_ALPHA_OPAQUE);

		SDL_RenderClear(ren);

		glClearColor(0.3f, 0.4f, 0.5f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// TODO: render

		//SDL_GL_SwapWindow(win);
		SDL_RenderPresent(ren);

		time = curr;
	}
}

static void update_scripts(float delta) {

	void *params[] = { (void *)&delta };

	mono_runtime_invoke(
		method_UpdateScripts,
		0,		//this
		params,	//params
		0);		//exception handler
}