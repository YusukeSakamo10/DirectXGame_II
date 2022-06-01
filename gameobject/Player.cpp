#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, const uint32_t textureHandle)
{
	assert(model);

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	model_ = model;
	textureHandle_ = textureHandle;
	ChangeControlKey(1);

	/*
	worldTransform_.scale_ = {0.0f,0.0f,0.0f};
	worldTransform_.rotation_ = {};
	worldTransform_.translation_ = {};
	*/
	worldTransform_.TransferMatrix();
}

void Player::Update()
{
	Move();
	
	worldTransform_.matWorld_.WorldTransUpdate(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


void Player::ChangeControlKey(int tempNum, BYTE moveUp, BYTE moveDown, BYTE moveLeft, BYTE moveRight)
{
	if (tempNum == 0) return;
	if (tempNum == 1) {
		MoveKeyBinding_[UP] = DIK_UP;
		MoveKeyBinding_[DOWN] = DIK_DOWN;
		MoveKeyBinding_[RIGHT] = DIK_RIGHT;
		MoveKeyBinding_[LEFT] = DIK_LEFT;
	}
	else {
		MoveKeyBinding_[UP] = moveUp;
		MoveKeyBinding_[DOWN] = moveDown;
		MoveKeyBinding_[RIGHT] = moveRight;
		MoveKeyBinding_[LEFT] = moveLeft;
	}
}

void Player::WorldTransUpdate()
{
	worldTransform_.matWorld_.WorldTransUpdate(this->worldTransform_.scale_, this->worldTransform_.rotation_, this->worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Player::Move()
{
	Vector3 move = { 0,0,0 };
	float speedX = 0.04f;
	float speedY = 0.04f;
	float spdx = (input_->PushKey(MoveKeyBinding_[RIGHT]) - input_->PushKey(MoveKeyBinding_[LEFT]) ) * speedX;
	float spdy = (input_->PushKey(MoveKeyBinding_[UP])	  - input_->PushKey(MoveKeyBinding_[DOWN]) ) * speedY;
	move.x = speedX;
	move.y = speedY;
	worldTransform_.translation_ += move;

}

void Player::Rotate()
{
}

void Player::Scale()
{
}

