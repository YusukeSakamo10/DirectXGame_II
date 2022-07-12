#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
//#include "WorldTransform.h"
#include "DebugCamera.h"
#include "gameobject/Player.h"
#include "gameobject/Enemy.h"
#include "Skydome.h"
#include "Camera/RailCamera.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void AllCheckCollision();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 3Dモデル
	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;

	//座標
	ViewProjection viewProjection_;
	ViewProjection debugProjection_;

	//プレイヤー
	std::unique_ptr<Player>player_;
	const int maxGrid = 10;

	std::list<std::unique_ptr<Enemy>> enemys_;

	//天球
	std::unique_ptr<Skydome>skydome_;

	//レールカメラ
	RailCamera *railCamera_ = nullptr;
	WorldTransform worldTransform_;

	//デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	//デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	//デバックテキスト
	bool isDebugTextActive_ = false;
};

