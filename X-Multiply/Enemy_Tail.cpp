#include "Application.h"
#include "Enemy_Tail.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleBackground.h"
#include "ModuleUI.h"


Enemy_Tail::Enemy_Tail(int x, int y) : Enemy(x, y)
{
	tail_fall.PushBack({ 426, 65, 219, 57 });
	animation = &tail_fall;
	collider = App->collision->AddCollider({ 0, 0, 219, 57 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	tail_death = App->audio->LoadSoundEffect("Audio_Assets/tumour_death.wav");
	points = 1000;
}


void Enemy_Tail::OnCollision(Collider* collider)
{
	App->audio->PlaySoundEffect(tail_death);
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->ui->points += points;
	App->background->taildown = true;
}

bool Enemy_Tail::CleanUp()
{
	LOG("Freeing enemy audio");
	App->audio->UnloadSoundEffect(tail_death);
	tail_death = nullptr;

	return true;
}