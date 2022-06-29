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
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">位置</param>
	void Initialize(Model* model, const uint32_t textureHandle,const Vector3& position);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">カメラ</param>
	void Draw(const ViewProjection& viewProjection);
	//	void Attack() override;

	void PhaseUpdate();

	void DrawDebug(int posX = 50, int posY = 70);

	/// <summary>
	/// 発砲
	/// </summary>
	void Fire();

	void ApproachInit();

	void OnCollisionEnter() override;

	static const int kFireInterval = 60;
private:
	/// <summary>
	/// 座標の更新と転送
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
	//ゲッター; セッター
	void SetVelocity(const Vector3& v) { v_ = v; };
	void SetPlayer(Player* player) { player_ = player; };
	Vector3 GetWorldPosition();
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }
	/// <summary>
	/// 弾の有無
	/// </summary>
	/// <returns></returns>
	bool GetIsDelete() const { return isDelete_; };

};


