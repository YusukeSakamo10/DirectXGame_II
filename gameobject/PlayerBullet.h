#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "Matrix4.h"

/// <summary>
/// Ž©ƒLƒƒƒ‰‚Ì’e
/// </summary>
class PlayerBullet {

public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

//	void Attack() override;
private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t textureHandle_ = 0;
};