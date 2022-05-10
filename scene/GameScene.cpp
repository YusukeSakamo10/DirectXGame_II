#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

//void ID_Matrix(float** array, int a);



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
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1200, 730);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	//ライン描画が参照するビュープロジェクションを指定する
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());



	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();




}

void GameScene::Update() {
	//デバッグカメラの更新
	debugCamera_->Update();

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


	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	
	for (size_t i = 0; i < maxGrid; i++) {
		int interval = maxGrid;
		int length = interval * (maxGrid-1);
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
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

/*
void ID_Matrix(float** array, int a)
{


	float **subArrays = {0,};

	for (int i = 0; i < a; i++) {

		for (int j = 0; j < a; j++) {

			subArrays[i][j] = 0;
			if (i == j) {
				subArrays[i][j] = 1;
			}
		}
	}

	array = subArrays;
}

*/