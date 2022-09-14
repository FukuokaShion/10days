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
	int mapchip[16][16];
	WorldTransform worldTransform_[16][16];

	

  private:
	Model* model_ = nullptr;
	float modelSize = NULL;

	Model* startModel_ = nullptr;
	Model* goleModel_ = nullptr;
	Model* teleportModel_ = nullptr;

	uint32_t baseTexture = 0;
	uint32_t teleportInTexture = 0;
	uint32_t teleportOutTexture = 0;
	
	////土台用
	int baseMapchip[15][15];
	WorldTransform baseWorldTransform_[16][16];
};