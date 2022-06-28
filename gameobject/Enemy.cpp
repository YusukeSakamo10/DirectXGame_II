#include "Enemy.h"
#include "Player.h"
#include <cassert>

void Enemy::Initialize(Model* model, const uint32_t textureHandle, const Vector3& position)
{
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("mario.jpg");
	debugText_ = DebugText::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.matWorld_.TransMatrix(position);
	worldTransform_.TransferMatrix();
	ApproachInit();
	collider = {
	worldTransform_.translation_.x,
	worldTransform_.translation_.y,
	worldTransform_.translation_.z,
	0.5};
	isDead_ = false;
}

void Enemy::Update()
{
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->GetIsDead();
		});
	PhaseUpdate();
	TransformUpdate();
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
	UpdateTranslation(worldTransform_.translation_);
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::PhaseUpdate()
{
	switch (phase_) {
	case Phase::APPROACH:
	default:
		MoveApproach();
		fireTimer_--;
		if (fireTimer_ == 0) {
			Fire();
			fireTimer_ = kFireInterval;
		}
		break;
	case Phase::LEAVE:
		MoveLeave();
		break;
	}
}

void Enemy::DrawDebug(int posX, int posY)
{
	if (!isDrawDebug_)return;
	debugText_->SetPos(posX, posY);
	debugText_->Printf("Pos:(%f,%f,%f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z	
	);
	debugText_->SetPos(posX, posY + 20);
	debugText_->Printf("Phase:  %s", Phase::APPROACH);

}

void Enemy::Fire()
{
	assert(player_);

	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 myPos = worldTransform_.translation_;

	Vector3 dist = playerPos - myPos;

	dist = dist.normalize();
	const float kBulletSpeed = 0.4f;
	Vector3 v = dist * kBulletSpeed;


	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, v);
	bullets_.push_back(std::move(newBullet));


}

void Enemy::ApproachInit()
{
	//発射タイマーを初期化
	fireTimer_ = kFireInterval;
}

void Enemy::OnCollisionEnter()
{
	isDead_ = true;
}


void Enemy::TransformUpdate()
{
	worldTransform_.matWorld_.WorldTransUpdate(
		worldTransform_.scale_,
		worldTransform_.rotation_,
		worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Enemy::MoveApproach(float limit)
{
	worldTransform_.translation_ += v_;
	//if (worldTransform_.translation_.z < limit) phase_ = Phase::LEAVE;
}

void Enemy::MoveLeave(Vector3 v)
{
	worldTransform_.translation_ += v;
}

Vector3 Enemy::GetWorldPosition()
{
	return worldTransform_.translation_;
}

 