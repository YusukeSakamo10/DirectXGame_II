#include "Player.h"
#include <cassert>

#define X_PI 3.1415f
#define DEGREE_RADIAN(deg) (X_PI * (deg) / 180.0f)
#define RADIAN2DEGREE(radian) radian * 180 / X_PI
float MinNum(float num, float min) { return num > min ? min : num; }

float MaxNum(float num, float max) { return num < max ? max : num; }

float clamp(float num, float min, float max) {
	if (num < min) {
		return min;
	}
	else if (num > max) {
		return max;
	}
	return num;
}

void Player::Initialize(Model* model, const uint32_t textureHandle)
{
	assert(model);

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	model_ = model;
	textureHandle_ = textureHandle;
	ChangeControlKey(1);
	worldTransform_.Initialize();
	/*
	worldTransform_.scale_ = {0.0f,0.0f,0.0f};
	worldTransform_.rotation_ = {};
	worldTransform_.translation_ = {};
	*/
	//worldTransform_.TransferMatrix();
}

void Player::Update()
{
	Move();

	WorldTransUpdate();
	DrawDebug();
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

void Player::SetMoveLimit(int maxY, int minY, int maxX, int minX)
{
	MoveLimit[TOP] = maxY;
	MoveLimit[BOTTOM] = minY;
	MoveLimit[LEFT] = minX;
	MoveLimit[RIGHT] = maxX;

}

void Player::DrawDebug()
{
	if (!isDrawDebug_)return;
	debugText_->SetPos(50, 150);
	debugText_->Printf("Pos:(%f,%f,%f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z
	);
	debugText_->Print("ArrowKey L & R : Root���ړ�", 50, 170);
	debugText_->Print("U Key , I Key : Rotation on Top", 50, 190);
	debugText_->Print("J Key , K Key : Rotation on Bottom", 50, 210);

}

void Player::WorldTransUpdate()
{
	worldTransform_.matWorld_.WorldTransUpdate(this->worldTransform_.scale_, this->worldTransform_.rotation_, this->worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Player::Move()
{
	Vector3 move = { 0,0,0 };

	float speedX = 0.4f;
	float speedY = 0.4f;
	float spdx = (input_->PushKey(MoveKeyBinding_[RIGHT]) - input_->PushKey(MoveKeyBinding_[LEFT])) * speedX;
	float spdy = (input_->PushKey(MoveKeyBinding_[UP])	  - input_->PushKey(MoveKeyBinding_[DOWN])) * speedY;

	float max = MoveLimit[RIGHT];
	float min = MoveLimit[LEFT];

	worldTransform_.translation_.x = clamp(worldTransform_.translation_.x + spdx, min, max);
	max = MoveLimit[TOP];
	min = MoveLimit[BOTTOM];
	worldTransform_.translation_.y = clamp(worldTransform_.translation_.y + spdy, min, max);
//���ɉ��ɐi�ނ̂ɍ��
	float spdz = (input_->PushKey(DIK_Z)) * speedY;
	move = { 0,0,spdz };
	worldTransform_.translation_ += move;

}

void Player::Rotate()
{
	;
}

void Player::Scale()
{
	;
}
