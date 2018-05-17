#include "Application.h"
#include "EnemyLeftLittleDorsal.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

EnemyLeftLittleDorsal::EnemyLeftLittleDorsal(int x, int y) : Enemy(x, y)
{
	leftlittledorsal.PushBack({ 41, 538, 63, 99 });
	animation = &leftlittledorsal;
	original_y = y;
	collider = App->collision->AddCollider({ 452, 124, 63, 50 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	/*leftdorsal_death = App->audio->LoadSoundEffect("Audio_Assets/Ball_Death.wav");*/
}

void EnemyLeftLittleDorsal::OnCollision(Collider* collider)
{

	//App->audio->PlaySoundEffect(leftdorsal_death);
}


bool EnemyLeftLittleDorsal::CleanUp()
{
	LOG("Freeing enemy audio");
	App->audio->UnloadSoundEffect(leftdorsal_death);
	shrimp_death = nullptr;

	return true;
}