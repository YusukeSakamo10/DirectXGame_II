#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>
#include "Collision.h"

#define X_PI 3.1415f
#define DEGREE_RADIAN(deg) (X_PI * (deg) / 180.0f)
#define RADIAN2DEGREE(radian) radian * 180 / X_PI


class Player : public Collision
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model, const uint32_t textureHandle);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �v���C���[�`��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V����</param>
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
	/// <summary>
	/// �ړ��̌��E�l�̐ݒ�
	/// </summary>
	/// <param name="maxY">������̌��E�l</param>
	/// <param name="minY">�������̌��E�l</param>
	/// <param name="maxX">�E�����̌��E�l</param>
	/// <param name="minX">�������̌��E�l</param>
	void SetMoveLimit(float maxY, float minY, float maxX, float minX);
	/// <summary>
	/// �f�o�b�N��\�����邩
	/// </summary>
	/// <param name="isDrawDebug">true�ŕ\��</param>
	void SetisDrawDebug(bool isDrawDebug) { isDrawDebug_ = isDrawDebug; };
	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

	void SetParent(WorldTransform& worldTransform) { worldTransform_.parent_ = &worldTransform; }

	void OnCollisionEnter() override;
	//�e�̃��X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }
	Vector3 GetWorldPosition();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	enum Direction {
		UP  = 0,
		TOP = 0,
		DOWN   = 1,
		BOTTOM = 1,
		LEFT,
		RIGHT,
		DIRECTIONEND
	};
	//�ړ��L�[
	BYTE MoveKeyBinding_[DIRECTIONEND] = { DIK_W,DIK_S, DIK_A, DIK_D };
	//�ړ���������
	float MoveLimit[DIRECTIONEND] = { 18,-18,-35,35 };
	bool isDrawDebug_ = false;
	bool isDead_ = false;


	void DrawDebug();
	void WorldTransUpdate();	
	void Move();
	void Rotate();
	void Scale();
};

