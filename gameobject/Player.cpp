#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, const uint32_t textureHandle)
{
	assert(model);

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	model_ = model;
	textureHandle_ = textureHandle;



}

void Player::Update()
{
	Vector3 move = { 0,0,0 };
	
	float speedX = 0.04f;
	float speedY = 0.04f;
	float spdx = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT)) * speedX;
	float spdy = (input_->PushKey(DIK_UP) - input_->PushKey(DIK_DOWN)) * speedY;

}

void Player::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Player::Move()
{
	Vector3 move = { 0,0,0 };
	float speedX = 0.04f;
	float speedY = 0.04f;
	float spdx = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT)) * speedX;
	float spdy = (input_->PushKey(DIK_UP) - input_->PushKey(DIK_DOWN)) * speedY;
	move.x = speedX;
	move.y = speedY;
	worldTransform_.translation_ += move;

}

