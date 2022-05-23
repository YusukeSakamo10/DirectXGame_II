#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include <random>

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

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//乱数範囲の指定
	std::uniform_real_distribution<float> dist(-10.0f, 10.0f);
	std::uniform_real_distribution<float> rot(0, DEGREE_RADIAN(360));


	//画像の読み込み
	textureHandle_ = TextureManager::Load("mario.jpg");

	//3Dモデルの生成
	model_ = Model::Create();

	for (WorldTransform& worldTransform_: worldTransforms_) {
		//ワールドトランスフォームの初期化
		worldTransform_.Initialize();

		worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
		worldTransform_.rotation_ = {DEGREE_RADIAN(rot(engine)),DEGREE_RADIAN(rot(engine)), DEGREE_RADIAN(rot(engine))};
		worldTransform_.translation_ = { dist(engine), dist(engine), dist(engine)};

		worldTransform_.matWorld_.WorldTransUpdate(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
		worldTransform_.TransferMatrix();

	}
	
	//ビュー変換
	viewProjection_.eye = { 0,0,0 };
	viewProjection_.target = { 0,0,0 };


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

	for (size_t i = 0; i < 100; i++) {
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}

	for (size_t i = 0; i < maxGrid; i++) {
		float interval = maxGrid;
		float length = interval * (maxGrid-1);
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
		EndPosZ =length;
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
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

