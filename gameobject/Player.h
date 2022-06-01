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
	/// �ړ��L�[�̐ݒ�
	/// </summary>
	/// <param name="tempNum">0�Ԗ�: WASD ; 1�Ԗ�: ���L�[ ; 3+ : �J�X�^��</param>
	/// <param name="moveUp">������L�[</param>
	/// <param name="moveDown">�������L�[</param>
	/// <param name="moveLeft">�������L�[</param>
	/// <param name="moveRight">�E�����L�[</param>
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

