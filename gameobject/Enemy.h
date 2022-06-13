#pragma once
#include "Model.h"
#include "TextureManager.h"

class Enemy
{
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


private:
	/// <summary>
	/// 座標の更新と転送
	/// </summary>
	void TransformUpdate();


private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0u;
	Vector3 v_ = { 0,0,-0.1 };
	bool isDead_ = false;

public:
	//ゲッター; セッター
	void SetVelocity(const Vector3& v) { v_ = v; };
};
