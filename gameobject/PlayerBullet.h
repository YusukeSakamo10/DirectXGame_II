#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "Matrix4.h"

/// <summary>
/// Ž©ƒLƒƒƒ‰‚Ì’e
/// </summary>
class PlayerBullet {

public:
	void Initialize(Model* model, const Vector3& position, const Vector3& v);

	void Update();

	void Draw(const ViewProjection& viewProjection);
	bool GetIsDead() const { return isDead_; };
//	void Attack() override;
private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0;
	Vector3 v_ = { 0,0,0 };
	bool isDead_ = false;
};