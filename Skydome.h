#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"

class Skydome
{
public:
	//void Initialize(const WorldTransform &worldTransform, Model* model);
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

};

