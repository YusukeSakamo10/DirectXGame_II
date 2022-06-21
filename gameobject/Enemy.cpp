#include "Enemy.h"
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
}

void Enemy::Update()
{
	PhaseUpdate();
	TransformUpdate();
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
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
	const float kBulletSpeed = 2.0f;
	Vector3 v(0, 0, kBulletSpeed);

	v = worldTransform_.matWorld_.mulVecMat(v, worldTransform_.matWorld_);

	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, v);
	bullets_.push_back(std::move(newBullet));


}

void Enemy::ApproachInit()
{
	//発射タイマーを初期化
	fireTimer_ = kFireInterval;
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
	if (worldTransform_.translation_.z < limit) phase_ = Phase::LEAVE;
}

void Enemy::MoveLeave(Vector3 v)
{
	worldTransform_.translation_ += v;
}

 