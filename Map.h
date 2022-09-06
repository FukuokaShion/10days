#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Map {
  public:
	~Map();
	void Initialize();
	void Update();
	void Draw(ViewProjection viewProjection);

  private:
	Model* model_ = nullptr;
	
	//マップの要素数
	static const int xElement = 12;
	static const int yElement = 2;
	static const int zElement = 12;
	WorldTransform worldTransform_[xElement][yElement][zElement];

	//マップチップ
	int mapchip[xElement][yElement][zElement];

	float modelSize = NULL;
};