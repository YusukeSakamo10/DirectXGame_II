#include "Skydome.h"

void Skydome::Initialize( Model* model)
{

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 100,100,100 };
	model_ = model;
}

void Skydome::Update()
{
	worldTransform_.matWorld_.WorldTransUpdate(this->worldTransform_.scale_, this->worldTransform_.rotation_, this->worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Skydome::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
