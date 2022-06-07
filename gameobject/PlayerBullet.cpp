#include "PlayerBullet.h"
#include <cassert>


void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& v)
{
	assert(model);
	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("mario.jpg");

	v_ = v;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.matWorld_.TransMatrix(worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void PlayerBullet::Update()
{
	worldTransform_.translation_ += v_;
	worldTransform_.matWorld_.WorldTransUpdate(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();

	
	if (worldTransform_.translation_.z > 50 || worldTransform_.translation_.z < -50) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
