#include "EnemyBullet.h"
#include <cassert>


void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& v)
{
	assert(model);
	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("bullet.jpg");

	v_ = v;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.matWorld_.TransMatrix(worldTransform_.translation_);
	worldTransform_.TransferMatrix();
	collider = {
	worldTransform_.translation_.x,
	worldTransform_.translation_.y,
	worldTransform_.translation_.z,
	0.5
	};
	isDead_ = false;
	
}

void EnemyBullet::Update()
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
	UpdateTranslation(worldTransform_.matWorld_.WorldPosition());
}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void EnemyBullet::OnCollisionEnter()
{
	isDead_ = true;
}
