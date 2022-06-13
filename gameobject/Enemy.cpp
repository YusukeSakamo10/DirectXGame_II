#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model, const uint32_t textureHandle, const Vector3& position)
{
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
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
	worldTransform_.translation_ += v_;

}

void Enemy::TransformUpdate()
{
	worldTransform_.matWorld_.WorldTransUpdate(
		worldTransform_.scale_,
		worldTransform_.rotation_,
		worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

 