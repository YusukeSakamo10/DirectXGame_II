#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"

#define X_PI 3.1415f
#define DEGREE_RADIAN(deg) (X_PI * (deg) / 180.0f)
#define RADIAN2DEGREE(radian) radian * 180 / X_PI


class Player
{
public:

	void Initialize(Model* model, const uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// 移動キーの設定
	/// </summary>
	/// <param name="tempNum">0番目: WASD ; 1番目: 矢印キー ; 3+ : カスタム</param>
	/// <param name="moveUp">上方向キー</param>
	/// <param name="moveDown">下方向キー</param>
	/// <param name="moveLeft">左方向キー</param>
	/// <param name="moveRight">右方向キー</param>
	void ChangeControlKey(int tempNum = 0, BYTE moveUp = DIK_W, BYTE moveDown = DIK_S, BYTE moveLeft = DIK_A, BYTE moveRight = DIK_D);
	void SetMoveLimit(int maxY, int minY, int maxX, int minX);

	void SetDrawDebug(bool isDrawDebug = TRUE);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	enum Direction {
		UP  = 0,
		TOP = 0,
		DOWN   = 1,
		BOTTOM = 1,
		LEFT,
		RIGHT,
		END
	};
	BYTE MoveKeyBinding_[4] = { DIK_W,DIK_S, DIK_A, DIK_D };
	int MoveLimit[4] = { 18,-18,-35,35 };


	void WorldTransUpdate();	
	void Move();
	void Rotate();
	void Scale();
};

