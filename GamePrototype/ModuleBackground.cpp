#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleIntroScene.h"


ModuleBackground::ModuleBackground()
{
	// Background 
	background.x = 54;
	background.y = 492;
	background.w = 4961;
	background.h = 513;

	

	wall.x = 250;
	wall.y = 1000;
	wall.w = 4961;
	wall.h = 513;

}

bool ModuleBackground::Init()
{

	//Spaceship drop animation
	injectionanim.PushBack({ 28,24,48,102 });
	injectionanim.PushBack({ 107,24,48,105 });
	injectionanim.PushBack({ 188,24,48,103 });
	injectionanim.PushBack({ 266,24,48,113 });
	injectionanim.PushBack({ 335,24,48,121 });
	injectionanim.PushBack({ 414,24,48,123 });
	injectionanim.PushBack({ 414,157,48,122 });
	injectionanim.PushBack({ 335,157,48,120 });
	injectionanim.PushBack({ 266,157,48,112 });
	injectionanim.PushBack({ 188,157,48,103 });
	injectionanim.PushBack({ 107,157,48,105 });
	injectionanim.PushBack({ 28,157,48,102 });

	injectionanim.loop = false;
	injectionanim.speed = 0.2f;

	//Injection Measurements
	injection.x = 50;
	injection.y = 100;
	injection.w = 48;
	injection.h = 102;

	inject = true;

	return true;

}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	
	graphics = App->textures->Load("TileMap1.png");
	graphicswall = App->textures->Load("FirstLvlMap.png");
	graphicsinjection = App->textures->Load("Injection.png");
	firstlvlmusic = App->audio->LoadMusic("Stage_1_Music.ogg");
	spaceshipdrop = App->audio->LoadSoundEffect("sound8.wav");
	
	App->audio->PlayMusic(firstlvlmusic);
	App->audio->PlaySoundEffect(spaceshipdrop);
	App->audio->PlayMusic(firstlvlmusic);
	App->player->Enable();
	return ret;
}

// UnLoad assets
bool ModuleBackground::CleanUp()
{
	LOG("Unloading first level scene scene");

	App->textures->Unload(graphics);
	App->textures->Unload(graphicswall);
	App->player->Disable();
	App->audio->UnloadSoundEffect(spaceshipdrop);
	spaceshipdrop = nullptr;

	return true;
}
// Update: draw background
update_status ModuleBackground::Update()
{
	animinject();
		// Draw everything --------------------------------------
	App->render->Blit(graphicswall, 0, 0, &wall, 0.75f);
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	App->render->Blit(graphicsinjection, xinject, yinject, &injection, 0.75f);


	if (App->intro->flag)
	{
		int vspeed = 1.5;
		if (App->render->camera.x <= -10600
			&& App->render->camera.x >= -13620)
		{
			App->render->camera.y -= vspeed;
			App->player->position.y -= vspeed;
		}
		
		if (!move)
		{
			App->render->camera.x = 0;
			App->player->position.x = 0;
		}
	}

	

	return UPDATE_CONTINUE;
}

//Dropping animation creation

void ModuleBackground::animinject()
{
	if (yinject >= -4 && inject)
	{
		if (injectionanim.GetCurrentFrameIndex() == 6)
		{
			App->player->Enable();
			right = true;
			inject = false;
		}
		injection = injectionanim.GetCurrentFrame();
	}
	else
	{
		if (!inject)
		{

			if (injectionanim.Done())
			{
				yinject--;
			}
			else
			{
				injection = injectionanim.GetCurrentFrame();
			}
		}
		else
		{
			yinject++;
		}
	}
}