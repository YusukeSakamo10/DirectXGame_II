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
	collider = {
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z,
		0.8f
	};
	isDead_ = false;
}

void PlayerBullet::Update()
{
	worldTransform_.translation_ += v_;
	worldTransform_.matWorld_.WorldTransUpdate(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();

	
	if (worldTransform_.translation_.x > 150 || worldTransform_.translation_.x < -150 ||
		worldTransform_.translation_.y > 150 || worldTransform_.translation_.y < -150 ||
		worldTransform_.translation_.z > 150 || worldTransform_.translation_.z < -150
		) {
		isDead_ = true;
	}
	UpdateTranslation(worldTransform_.translation_);

}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::OnCollisionEnter()
{
	isDead_ = 0;
}
