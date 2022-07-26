#pragma once
#include <memory>
#include <list>
#include "gameobject/EnemyBullet.h"

class BulletManager
{
public:
	void Update();
	void Draw();
	void Instantiate(const Vector3& position, const Vector3& speed);


	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;



};

