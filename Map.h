#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Map {
  public:
	~Map();
	void Initialize();
	void Update();
	void StageDraw(ViewProjection viewProjection);
	void FrameDraw(ViewProjection viewProjection);


public:
	//�}�b�v�`�b�v
	static const int xElement = 12;
	static const int zElement = 12;
	int mapchip[xElement][zElement];
	WorldTransform worldTransform_[xElement][zElement];

  private:
	Model* model_ = nullptr;
	float modelSize = NULL;

	Model* startModel_ = nullptr;
	Model* goleModel_ = nullptr;
	Model* teleportModel_ = nullptr;

	uint32_t baseTexture = 0;
	
	//�}�b�v�̗v�f��

	WorldTransform baseWorldTransform_;

};