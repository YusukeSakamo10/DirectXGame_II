#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

#define X_PI 3.1415f
#define DEGREE_RADIAN(deg) (X_PI * (deg) / 180.0f)

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();


	//画像の読み込み
	textureHandle_ = TextureManager::Load("mario.jpg");

	//3Dモデルの生成
	model_ = Model::Create();

	//ワールドトランスフォームの初期化
	for (size_t i = 0; i < 3; i++) {
		worldTransforms_[i].Initialize();
	}
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();


	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	//ライン描画が参照するビュープロジェクションを指定する
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	//座標の設定
	for (size_t i = 0; i < 3; i++) {

		worldTransforms_[i].scale_ = { 1.0f, 1.0f, 1.0f };
		switch (i) {
		case 0:
			worldTransforms_[i].translation_ = { 0.0f,-5.0f,10.0f };
			break;
		case 1:
			worldTransforms_[i].translation_ = { -10.0f,5.0f,10.0f };
			break;
		case 2:
			worldTransforms_[i].translation_ = { 10.0f,5.0f,10.0f };
			break;
		};

		//変換行列を求める
		worldTransforms_[i].matWorld_.WorldTransUpdate(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);
		worldTransforms_[i].TransferMatrix();
	}
}

void GameScene::Update() {
	//デバッグカメラの更新
	debugCamera_->Update();
	if (input_->TriggerKey(DIK_SPACE) && !isMove_) {
 		cameraNum_++;

		if (cameraNum_ >= 3) {
			cameraNum_ = 0;
		}

		moveTarget = worldTransforms_[cameraNum_].translation_ - viewProjection_.target;
	//	moveTarget = moveTarget.normalize();
		isMove_ = true;
	}
	
	if (isMove_) {
		if (viewProjection_.target.x == worldTransforms_[cameraNum_].translation_.x &&
			viewProjection_.target.y == worldTransforms_[cameraNum_].translation_.y &&
			viewProjection_.target.z == worldTransforms_[cameraNum_].translation_.z) {
			isMove_ = false;
			timer = 0;
		}
		else {
			if (timer <= maxTime) timer++;
			float t = timer / (float)maxTime;
			moveTarget *= t;
			viewProjection_.target += moveTarget;
		}
	}

	debugText_->SetPos(50, 100);
	debugText_->Printf("target : (%f, %f, %f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);
	viewProjection_.UpdateMatrix();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	for (size_t i = 0; i < 3; i++) {
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

