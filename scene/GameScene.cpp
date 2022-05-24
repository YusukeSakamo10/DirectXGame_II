#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

#define X_PI 3.1415f
#define DEGREE_RADIAN(deg) (X_PI * (deg) / 180.0f)
#define RADIAN2DEGREE(radian) radian * 180 / X_PI
float MinNum(float num, float min) { return num > min ? min : num; }

float MaxNum(float num, float max) { return num < max ? max : num; }

float clamp(float num, float min, float max) {
	if (num < min) {
		return min;
	}
	else if (num > max) {
		return max;
	}
	return num;
}


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

	worldTransforms_[PartId::KROOT].scale_ = { 1.0f,1.0f, 1.0f };
	worldTransforms_[PartId::KROOT].rotation_ = { 0,0, 0 };
	worldTransforms_[PartId::KROOT].translation_ = { 0,0,0 };

	worldTransforms_[0].matWorld_.WorldTransUpdate(worldTransforms_[0].scale_, worldTransforms_[0].rotation_, worldTransforms_[0].translation_);

#pragma region キャラクター座標
	//脊椎
	worldTransforms_[PartId::KSPINE].translation_ = { 0, 4.5f,0 };
	worldTransforms_[PartId::KSPINE].parent_ = &worldTransforms_[PartId::KROOT];
	worldTransforms_[PartId::KSPINE].Initialize();

	//上半身
	worldTransforms_[PartId::KCHEST].translation_ = { 0, 0,0 };
	worldTransforms_[PartId::KCHEST].parent_ = &worldTransforms_[PartId::KSPINE];
	worldTransforms_[PartId::KCHEST].Initialize();

	worldTransforms_[PartId::KHEAD].translation_ = { 0, 4.5f,0 };
	worldTransforms_[PartId::KHEAD].parent_ = &worldTransforms_[PartId::KCHEST];
	worldTransforms_[PartId::KHEAD].Initialize();

	worldTransforms_[PartId::KARML].translation_ = { -5.0f, 0,0 };
	worldTransforms_[PartId::KARML].parent_ = &worldTransforms_[PartId::KCHEST];
	worldTransforms_[PartId::KARML].Initialize();

	worldTransforms_[PartId::KARMR].translation_ = { 5.0, 0,0 };
	worldTransforms_[PartId::KARMR].parent_ = &worldTransforms_[PartId::KCHEST];
	worldTransforms_[PartId::KARMR].Initialize();

	//下半身

	worldTransforms_[PartId::KHIP].translation_ = { 0, -4.5f,0 };
	worldTransforms_[PartId::KHIP].parent_ = &worldTransforms_[PartId::KSPINE];
	worldTransforms_[PartId::KHIP].Initialize();

	worldTransforms_[PartId::KLEGL].translation_ = { -5.0f, -4.5f,0 };
	worldTransforms_[PartId::KLEGL].parent_ = &worldTransforms_[PartId::KHIP];
	worldTransforms_[PartId::KLEGL].Initialize();

	worldTransforms_[PartId::KLEGR].translation_ = { +5.0f, -4.5f,0 };
	worldTransforms_[PartId::KLEGR].parent_ = &worldTransforms_[PartId::KHIP];
	worldTransforms_[PartId::KLEGR].Initialize();
#pragma endregion キャラクター座標

	//子どもアップデート
	for (size_t i = 1; i < PartId::kNUMPARTID; i++) {
		worldTransforms_[i].matWorld_.WorldTransUpdate(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);
	}


	//ビュープロジェクションの初期化
	viewProjection_.Initialize();


	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//ライン描画が参照するビュープロジェクションを指定する
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {
	//デバッグカメラの更新
	debugCamera_->Update();

#pragma region ビュー連続変換
	/*
	Vector3 move = { 0,0,0 };

	const float kEyeSpeed = 0.2f;
	move.z = (input_->PushKey(DIK_W) - input_->PushKey(DIK_S)) * kEyeSpeed;
	viewProjection_.eye += move;

	move = { 0,0,0 };
	const float kTargetSpeed = 0.2f;
	move.x = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT)) * kTargetSpeed;
	viewProjection_.target += move;

	const float kUpRotSpeed = 0.05f;
	if (input_->PushKey(DIK_SPACE)) {
		viewAngle += kUpRotSpeed;
		//2PIを超えたら0に戻す
		viewAngle = fmodf(viewAngle, X_PI * 2.0f);
	}

	viewProjection_.up = { cosf(viewAngle), sinf(viewAngle), 0.0f };

	viewProjection_.UpdateMatrix();
	debugText_->SetPos(50, 50);
	debugText_->Printf("eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	debugText_->SetPos(50, 70);
	debugText_->Printf("target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);

	debugText_->SetPos(50, 90);
	debugText_->Printf("up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
	*/
#pragma endregion ビュー連続変換
	
	 Vector3 move = { 0,0,0 };

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move = { -kCharacterSpeed, 0,0 };
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move = { kCharacterSpeed, 0,0 };
	}

	worldTransforms_[PartId::KROOT].translation_, move;


	const float kChestRotSpeed = 0.05f;

	float ChestRotY = (input_->PushKey(DIK_I) - input_->PushKey(DIK_U)) * kChestRotSpeed;
	worldTransforms_[PartId::KCHEST].rotation_.y += ChestRotY;

	const float kHipRotSpeed = 0.05f;

	float HipRotY = (input_->PushKey(DIK_K) - input_->PushKey(DIK_J)) * kHipRotSpeed;
	worldTransforms_[PartId::KHIP].rotation_.y += HipRotY;

	debugText_->SetPos(50, 150);
	debugText_->Printf("Root:(%f,%f,%f)",
		worldTransforms_[PartId::KROOT].translation_.x,
		worldTransforms_[PartId::KROOT].translation_.y,
		worldTransforms_[PartId::KROOT].translation_.z
	);
	debugText_->Print("ArrowKey L & R : Rootを移動", 50, 170);
	debugText_->Print("U Key , I Key : Rotation on Top", 50, 190);
	debugText_->Print("J Key , K Key : Rotation on Bottom", 50, 210);
	worldTransforms_[0].matWorld_.WorldTransUpdate(worldTransforms_[0].scale_, worldTransforms_[0].rotation_, worldTransforms_[0].translation_);
	//子どもアップデート
	for (size_t i = 1; i < PartId::kNUMPARTID; i++) {
		worldTransforms_[i].matWorld_.WorldTransUpdate(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);
	}

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

	for (size_t i = 0; i < kNUMPARTID; i++) {
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}

	for (size_t i = 0; i < maxGrid; i++) {
		float interval = maxGrid;
		float length = interval * (maxGrid - 1);
		float distance = interval * i;
		float StartPosX = distance;
		float StartPosZ = distance;

		float EndPosX = length;
		float EndPosZ = distance;
		float posZ = StartPosX * i;

		//横
		PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, StartPosZ), Vector3(EndPosX, 0, EndPosZ), Vector4(1, 0, 0, 1));

		StartPosX = distance;
		StartPosZ = 0;
		EndPosX = distance;
		EndPosZ = length;
		//縦
		PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(StartPosX, 0, 0), Vector3(EndPosX, 0, EndPosZ), Vector4(0, 0, 1, 1));

	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	//

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

