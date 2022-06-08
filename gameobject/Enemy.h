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
	void Initialize(Model* model, const Vector3& position);
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
private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0;
	Vector3 v_ = { 0,0,0 };
	bool isDead_ = false;
};
