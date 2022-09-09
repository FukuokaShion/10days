#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Map {
  public:
	~Map();
	void Initialize(int stage);
	void Update();
	void StageDraw(ViewProjection viewProjection);
	void FrameDraw(ViewProjection viewProjection);


public:
	//マップチップ
	int xElement;
	int zElement;
	int mapchip[15][15];
	WorldTransform worldTransform_[15][15];

	

  private:
	Model* model_ = nullptr;
	float modelSize = NULL;

	Model* startModel_ = nullptr;
	Model* goleModel_ = nullptr;
	Model* teleportModel_ = nullptr;

	uint32_t baseTexture = 0;
	
	////土台用
	int baseMapchip[15][15];
	WorldTransform baseWorldTransform_[15][15];
};