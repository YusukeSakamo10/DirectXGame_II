#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& position)
{
	assert(model);
	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("mario.jpg");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.matWorld_.TransMatrix(worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void PlayerBullet::Update()
{
	worldTransform_.matWorld_.WorldTransUpdate(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
