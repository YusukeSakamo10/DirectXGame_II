#include "RailCamera.h"

void RailCamera::Initialize(const Vector3& translation, const Vector3& rotation)
{
	worldTransform_.translation_ = translation;
	worldTransform_.rotation_ = rotation;
	//worldTransform_.TransferMatrix();

	viewProjection_.Initialize();
	viewProjection_.farZ = 2000.0f;
	debugText_ = DebugText::GetInstance();
}

void RailCamera::Update()
{
	worldTransform_.translation_.z += 0.5f;
	worldTransform_.rotation_;
	worldTransform_.UpdateMatrix();

	viewProjection_.eye.x = worldTransform_.matWorld_.m[3][0];
	viewProjection_.eye.y = worldTransform_.matWorld_.m[3][1];
	viewProjection_.eye.z = worldTransform_.matWorld_.m[3][2];

	//ワールド前方ベクトル
	Vector3 forward(0, 0, 10);
	//レールカメラの回転を反映
	forward = worldTransform_.matWorld_.mulVecMat(forward, worldTransform_.matWorld_);

	viewProjection_.target = viewProjection_.eye + forward;

	Vector3 up(0, 1, 0);
	viewProjection_.up = worldTransform_.matWorld_.mulVecMat(up, worldTransform_.matWorld_);
	viewProjection_.UpdateMatrix();
	//viewProjection_.TransferMatrix();
}

void RailCamera::DrawDebug()
{
	if (!isDrawDebug_)return;
	debugText_->SetPos(50, 300);
	debugText_->Printf("Eye:(%f,%f,%f)",
		viewProjection_.eye.x,
		viewProjection_.eye.y,
		viewProjection_.eye.z
	);
}

void RailCamera::RePlaceViewProjection(ViewProjection& viewProjection)
{
	viewProjection.eye = viewProjection_.eye;
	viewProjection.target = viewProjection_.target;
	viewProjection.up = viewProjection_.up;

}
