#pragma once
#include "Model.h"
#include "TextureManager.h"

class Enemy
{
	enum class Phase {
		APPROACH,
		LEAVE,
	};

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="position">�ʒu</param>
	void Initialize(Model* model, const uint32_t textureHandle,const Vector3& position);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection">�J����</param>
	void Draw(const ViewProjection& viewProjection);
	/// <summary>
	/// �e�̗L��
	/// </summary>
	/// <returns></returns>
	bool GetIsDead() const { return isDead_; };
	//	void Attack() override;

	void Move();


private:
	/// <summary>
	/// ���W�̍X�V�Ɠ]��
	/// </summary>
	void TransformUpdate();
	void MoveApproach(float limit = 0.0f);
	void MoveLeave(Vector3 v = {-0.3f,0.1f,0});

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0u;
	Vector3 v_ = { 0,0,-0.6 };
	bool isDead_ = false;
	Phase phase_ = Phase::APPROACH;


public:
	//�Q�b�^�[; �Z�b�^�[
	void SetVelocity(const Vector3& v) { v_ = v; };
};


