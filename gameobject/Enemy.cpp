#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model, const uint32_t textureHandle, const Vector3& position)
{
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	debugText_ = DebugText::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.matWorld_.TransMatrix(position);
	worldTransform_.TransferMatrix();
}

void Enemy::Update()
{


	Move();
	TransformUpdate();
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Move()
{
	switch (phase_) {
	case Phase::APPROACH:
	default:
		MoveApproach();
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

 