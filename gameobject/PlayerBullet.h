#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "Matrix4.h"

/// <summary>
/// ���L�����̒e
/// </summary>
class PlayerBullet {

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="position">�e�̔��ˈʒu</param>
	/// <param name="v">�e�̃X�s�[�h</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& v);
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
private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0;
	Vector3 v_ = { 0,0,0 };
	bool isDead_ = false;
};