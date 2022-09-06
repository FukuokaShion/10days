#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"

class Player {
  public:
	~Player();
	void Initialize();
	void Entry(Input* input);
	void Move();
	void Draw(ViewProjection viewProjection);

  private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;

	//Move—p
	std::vector<int> a;
	const int  moveTime = 60 * 1;
	int moveTimer_ = moveTime;
};