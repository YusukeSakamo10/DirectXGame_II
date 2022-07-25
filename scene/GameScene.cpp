#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete modelSkydome_;
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
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0, -10.0f, 0 };

	//画像の読み込み
	textureHandle_ = TextureManager::Load("player.jpg");

	//3Dモデルの生成
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);


	player_ = std::make_unique<Player>();
	player_->Initialize(model_, textureHandle_);


	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	enemy->Initialize(model_, textureHandle_, { 10,10, 100 });
	enemy->SetPlayer(player_.get());
	enemys_.push_back(std::move(enemy));

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//天球
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_);
	//レールカメラ
	railCamera_ = std::make_unique<RailCamera>();
	
	railCamera_->Initialize(Vector3(0,0,-50.0f), Vector3(0, 0, 0));

	player_->SetParent(railCamera_->GetWorldMatrix());

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(false);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//ライン描画が参照するビュープロジェクションを指定する
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {

	//デバック中のみ表示
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0)) {
		//デバッグカメラのスイッチ
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
	//デバックテキストの表示
	player_->SetisDrawDebug(true);
	railCamera_->SetisDrawDebug(true);
	isDebugTextActive_ = true;
	//軸の表示
	AxisIndicator::GetInstance()->SetVisible(true);
#endif // _DEBUG

	if (isDebugCameraActive_) {
		//デバッグカメラの更新
		debugCamera_->Update();
		debugProjection_ = debugCamera_->GetViewProjection();
		viewProjection_.matView = debugProjection_.matView;
		viewProjection_.matProjection = debugProjection_.matProjection;
		viewProjection_.TransferMatrix();
	}
	else {
		//viewProjection_.UpdateMatrix();
		//viewProjection_.TransferMatrix();
	}

	railCamera_->Update();
	viewProjection_.matView = railCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();


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

	enemys_.remove_if([](std::unique_ptr<Enemy>& enemy) {
		return enemy->GetIsDelete();
	});
	

	//プレイヤー
	player_->Update();
	skydome_->Update();
	for (std::unique_ptr<Enemy>& enemy : enemys_) {
		if (enemy) enemy->Update();
	}
	AllCheckCollision();

	//デバッグテキスト関連
	//if (isDebugTextActive_) {
	//	debugText_->SetPos(50, 240);
	//	debugText_->Printf("eye : %f, %f, %f", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	//}
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

	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	for (std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}

	/*
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
	*/
	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	//
	railCamera_->DrawDebug();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::AllCheckCollision()
{
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();

	//複数体の敵の一人から
	for (std::unique_ptr<Enemy>& enemy : enemys_) {
		//一体の弾のリストを取得して
		const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy->GetBullets();

		
#pragma region 自キャラと敵キャラの当たり判定
		if (enemy->Circle3dCollision(enemy->GetCircleCollider(), player_->GetCircleCollider())) {
			enemy->OnCollisionEnter();
		}

#pragma endregion

		//各敵の弾との判定
		for (const std::unique_ptr<EnemyBullet>&enemyBullet : enemyBullets) {

#pragma region 自キャラと敵弾の当たり判定
			if (player_->Circle3dCollision(enemyBullet->GetCircleCollider(), player_->GetCircleCollider())) {
				player_->OnCollisionEnter();
				enemyBullet->OnCollisionEnter();
			}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
			//自弾の数分ループ
			for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
				if (playerBullet->Circle3dCollision(enemyBullet->GetCircleCollider(), playerBullet->GetCircleCollider())) {
					enemyBullet->OnCollisionEnter();
					playerBullet->OnCollisionEnter();
				}
			}
#pragma endregion
		}
		//各敵の弾との判定終わり
		
#pragma region 自弾と敵の判定
		//自弾の数のループ
		for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
			if (playerBullet->Circle3dCollision(enemy->GetCircleCollider(), playerBullet->GetCircleCollider())) {
				enemy->OnCollisionEnter();
				playerBullet->OnCollisionEnter();
			}
		}
#pragma endregion

	}
	//複数の敵の範囲forの終わり

}

void GameScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet)
{
	enemyBullets_.push_back(std::move(enemyBullet));
}

