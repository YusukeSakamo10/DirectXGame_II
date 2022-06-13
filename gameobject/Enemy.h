#pragma once
#include "Model.h"
#include "TextureManager.h"

class Enemy
{
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


private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0u;
	Vector3 v_ = { 0,0,-0.1 };
	bool isDead_ = false;

public:
	//�Q�b�^�[; �Z�b�^�[
	void SetVelocity(const Vector3& v) { v_ = v; };
};
