#include "RailCamera.h"

void RailCamera::Initialize(const Vector3& translation, const Vector3& rotation)
{
	worldTransform_.Initialize();
	worldTransform_.translation_ = translation;
	worldTransform_.rotation_ = rotation;
	worldTransform_.TransferMatrix();
	viewProjection_.Initialize();

	debugText_ = DebugText::GetInstance();
}

void RailCamera::Update()
{
	worldTransform_.translation_.z += 0.5f;
	worldTransform_.rotation_;
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();

	viewProjection_.eye = worldTransform_.translation_;
	//ワールド前方ベクトル
	Vector3 forward(0, 0, 1);
	//レールカメラの回転を反映
	forward = worldTransform_.matWorld_.mulVecMat(forward, worldTransform_.matWorld_);

	viewProjection_.target = viewProjection_.eye + forward;

	Vector3 up(0, 1, 0);
	viewProjection_.up = worldTransform_.matWorld_.mulVecMat(up, worldTransform_.matWorld_);
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
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
	debugText_->Print("ArrowKey L & R : Rootを移動", 50, 170);
	debugText_->Print("U Key , I Key : Rotation on Top", 50, 190);
	debugText_->Print("J Key , K Key : Rotation on Bottom", 50, 210);

}

void RailCamera::RePlaceViewProjection(ViewProjection& viewProjection)
{
	viewProjection.eye = viewProjection_.eye;
	viewProjection.target = viewProjection_.target;
	viewProjection.up = viewProjection_.up;

}
