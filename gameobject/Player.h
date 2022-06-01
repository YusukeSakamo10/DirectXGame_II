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

	/// <summary>
	/// 移動キーの設定
	/// </summary>
	/// <param name="tempNum">0番目: WASD ; 1番目: 矢印キー ; 3+ : カスタム</param>
	/// <param name="moveUp">上方向キー</param>
	/// <param name="moveDown">下方向キー</param>
	/// <param name="moveLeft">左方向キー</param>
	/// <param name="moveRight">右方向キー</param>
	void ChangeControlKey(int tempNum = 0, BYTE moveUp = DIK_W, BYTE moveDown = DIK_S, BYTE moveLeft = DIK_A, BYTE moveRight = DIK_D);


private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	void WorldTransUpdate();
	
	void Move();
	void Rotate();
	void Scale();
	enum KeyConfe {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		KEYEND
	};
	BYTE MoveKeyBinding_[4] = { DIK_W,DIK_S, DIK_A, DIK_D };

};

