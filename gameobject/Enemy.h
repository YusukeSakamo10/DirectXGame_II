#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include <memory>
#include <list>
#include "Collision.h"
class Player;

class Enemy : public Collision
{
	enum class Phase {
		APPROACH,
		LEAVE,
		DEAD
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
	//	void Attack() override;

	void PhaseUpdate();

	void DrawDebug(int posX = 50, int posY = 70);

	/// <summary>
	/// ���C
	/// </summary>
	void Fire();

	void ApproachInit();

	void OnCollisionEnter() override;

	static const int kFireInterval = 60;
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
	DebugText* debugText_;
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	Vector3 v_ = { 0.0f,0.0f,-0.6f };
	bool isDead_ = false;
	bool isDelete_ = false;
	bool isDrawDebug_ = true;

	Phase phase_ = Phase::APPROACH;
	int32_t fireTimer_ = 0;

	Player* player_ = nullptr;
public:
	//�Q�b�^�[; �Z�b�^�[
	void SetVelocity(const Vector3& v) { v_ = v; };
	void SetPlayer(Player* player) { player_ = player; };
	Vector3 GetWorldPosition();
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }
	/// <summary>
	/// �e�̗L��
	/// </summary>
	/// <returns></returns>
	bool GetIsDelete() const { return isDelete_; };

};


