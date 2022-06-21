#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "DebugText.h"

class Enemy
{
	enum class Phase {
		APPROACH,
		LEAVE,
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
	/// <summary>
	/// 弾の有無
	/// </summary>
	/// <returns></returns>
	bool GetIsDead() const { return isDead_; };
	//	void Attack() override;

	void Move();

	void DrawDebug(int posX = 50, int posY = 70);

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
	
	Vector3 v_ = { 0,0,-0.6 };
	bool isDead_ = false;
	bool isDrawDebug_ = true;

	Phase phase_ = Phase::APPROACH;


public:
	//ゲッター; セッター
	void SetVelocity(const Vector3& v) { v_ = v; };
};


