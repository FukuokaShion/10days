#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"

class Map;

class Player {
  public:
	~Player();
	void Initialize();
	void Entry(Input* input);
	void Move();
	void Draw(ViewProjection viewProjection);

	void SetMap(Map* map) { map_ = map; };
	bool isGole();

  private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	
	Map* map_;
	int pos[2];

	float PI = 3.141592;

	//Move—p
	std::vector<int> inputMemory;
	const int  moveTime = 50;
	int moveTimer_ = moveTime;
};