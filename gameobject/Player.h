#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>
#include "Collision.h"

#define X_PI 3.1415f
#define DEGREE_RADIAN(deg) (X_PI * (deg) / 180.0f)
#define RADIAN2DEGREE(radian) radian * 180 / X_PI


class Player : public Collision
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, const uint32_t textureHandle);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// プレイヤー描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// 移動キーの設定
	/// </summary>
	/// <param name="tempNum">0番目: WASD ; 1番目: 矢印キー ; 3+ : カスタム</param>
	/// <param name="moveUp">上方向キー</param>
	/// <param name="moveDown">下方向キー</param>
	/// <param name="moveLeft">左方向キー</param>
	/// <param name="moveRight">右方向キー</param>
	void ChangeControlKey(int tempNum = 0, BYTE moveUp = DIK_W, BYTE moveDown = DIK_S, BYTE moveLeft = DIK_A, BYTE moveRight = DIK_D);
	/// <summary>
	/// 移動の限界値の設定
	/// </summary>
	/// <param name="maxY">上方向の限界値</param>
	/// <param name="minY">下方向の限界値</param>
	/// <param name="maxX">右方向の限界値</param>
	/// <param name="minX">左方向の限界値</param>
	void SetMoveLimit(float maxY, float minY, float maxX, float minX);
	/// <summary>
	/// デバックを表示するか
	/// </summary>
	/// <param name="isDrawDebug">trueで表示</param>
	void SetisDrawDebug(bool isDrawDebug) { isDrawDebug_ = isDrawDebug; };
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	void SetParent(WorldTransform& worldTransform) { worldTransform_.parent_ = &worldTransform; }

	void OnCollisionEnter() override;
	//弾のリストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }
	Vector3 GetWorldPosition();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	enum Direction {
		UP  = 0,
		TOP = 0,
		DOWN   = 1,
		BOTTOM = 1,
		LEFT,
		RIGHT,
		DIRECTIONEND
	};
	//移動キー
	BYTE MoveKeyBinding_[DIRECTIONEND] = { DIK_W,DIK_S, DIK_A, DIK_D };
	//移動制限方向
	float MoveLimit[DIRECTIONEND] = { 18,-18,-35,35 };
	bool isDrawDebug_ = false;
	bool isDead_ = false;


	void DrawDebug();
	void WorldTransUpdate();	
	void Move();
	void Rotate();
	void Scale();
};

