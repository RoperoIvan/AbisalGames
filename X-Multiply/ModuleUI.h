#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleUI :public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* u_interface = nullptr;
	//SDL_Rect ui;
	int font_score = -1;
	uint score = 0;
	int points = 0;
	char text[10];
};

#endif // MODULE_UI