#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "Matrix4.h"

/// <summary>
/// 自キャラの弾
/// </summary>
class PlayerBullet {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">弾の発射位置</param>
	/// <param name="v">弾のスピード</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& v);
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