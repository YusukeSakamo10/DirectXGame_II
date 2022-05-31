#pragma once
#include "3d/WorldTransform.h"
#include "3d/Model.h"
#include "input/Input.h"
#include "2d/DebugText.h"


class Player
{
public:

	void Initialize(Model* model, const uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection);



private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	void Move();


};

