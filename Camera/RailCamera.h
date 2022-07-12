#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
class RailCamera
{
public:
	void Initialize(const Vector3 &translation, const Vector3 &rotation);
	void Update();
	void DrawDebug();

	/// <summary>
	/// デバックを表示するか
	/// </summary>
	/// <param name="isDrawDebug">trueで表示</param>
	void SetisDrawDebug(bool isDrawDebug) { isDrawDebug_ = isDrawDebug; };
	void RePlaceViewProjection(ViewProjection &viewProjection);
private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;
	bool isDrawDebug_ = false;
};