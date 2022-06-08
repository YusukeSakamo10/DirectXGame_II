#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model, const Vector3& position)
{
	assert(model);
	model_ = model;


}
