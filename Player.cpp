#include"Player.h"
#include"Affine.h"
#include"Map.h"

Player::~Player() {
	delete model_;
}

void Player::Initialize() {
//------------------モデル生成-----------------
	model_ = Model::CreateFromOBJ("player", false);

//--------座標設定------------
	//初期のプレイヤーのマップチップ座標
	for (int x = 0; x < map_->xElement;x++) {
		for (int z = 0; z < map_->zElement; z++) {
			if (map_->mapchip[x][z] == 2) {
				pos[0] = x;
				pos[1] = z;
			}
		}
	}

	moveTimer_ = moveTime;

	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3((pos[0] * 2) - (map_->xElement - 1), 0, (pos[1] * 2) - (map_->zElement - 1));
	worldTransform_.rotation_ = Vector3(0, 0, 0);

	//行列設定
	Matrix4 matScale = AffineScale(worldTransform_);
	Matrix4 matRotaX = AffineRotaX(worldTransform_);
	Matrix4 matRotaY = AffineRotaY(worldTransform_);
	Matrix4 matRotaZ = AffineRotaZ(worldTransform_);
	Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
	Matrix4 matTrans = AffineTrans(worldTransform_);
	//掛け
	worldTransform_.matWorld_ = AffineWorld(matScale, matRota, matTrans);

	//行列の転送
	worldTransform_.TransferMatrix();

//-----------------------------
	inputMemory.clear();


}

void Player::Entry(Input* input) {
	//入力された方向を配列の後ろに追加していく
	if (input->TriggerKey(DIK_W)) {
		inputMemory.push_back(0);
	}
	if (input->TriggerKey(DIK_S)) {
		inputMemory.push_back(1);
	}
	if (input->TriggerKey(DIK_A)) {
		inputMemory.push_back(2);
	}
	if (input->TriggerKey(DIK_D)) {
		inputMemory.push_back(3);
	}
}

void Player::Move() {
	moveTimer_--;

	
	if (moveTimer_ >= 0) {
		//入力されたキー情報が残っているなら
		if (!inputMemory.empty()) {
			//配列の先頭に入っている方向の処理
		//-----------------
			if (inputMemory.front() == 0) {
				if (map_->mapchip[pos[0]][pos[1] + 1] != 1) {
					
					worldTransform_.translation_ += Vector3(0, 0, 2.0f / moveTime);

					worldTransform_.rotation_ += Vector3( PI/moveTime/2, 0, 0);


					if (moveTimer_ == 0) {
						pos[1]++;
						//ワープ処理
						if (map_->mapchip[pos[0]][pos[1]] == 4) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 5) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
						else if (map_->mapchip[pos[0]][pos[1]] == 5) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 4) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
						else if (map_->mapchip[pos[0]][pos[1]] == 6) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 7) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
					}
				}else if (map_->mapchip[pos[0]][pos[1] + 1] == 1) {
					//配列の先頭を削除
					inputMemory.erase(inputMemory.begin());
					//タイマーの初期化
					moveTimer_ = moveTime;
				}
			}
		//-----------------
			else if (inputMemory.front() == 1) {
				if (map_->mapchip[pos[0]][pos[1] - 1] != 1) {
					worldTransform_.translation_ += Vector3(0, 0, -2.0f/moveTime);
					worldTransform_.rotation_ += Vector3(-PI / moveTime / 2, 0, 0);
					if (moveTimer_ == 0) {
						pos[1]--;
						//ワープ処理
						if (map_->mapchip[pos[0]][pos[1]] == 4) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 5) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
						else if (map_->mapchip[pos[0]][pos[1]] == 5) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 4) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
						else if (map_->mapchip[pos[0]][pos[1]] == 6) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 7) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
					}
					
				}else if (map_->mapchip[pos[0]][pos[1] - 1] == 1) {
					//配列の先頭を削除
					inputMemory.erase(inputMemory.begin());
					//タイマーの初期化
					moveTimer_ = moveTime;
				}
			}
		//-----------------
			else if (inputMemory.front() == 2) {
				if (map_->mapchip[pos[0] - 1][pos[1]] != 1) {
					worldTransform_.translation_ += Vector3(-2.0f/moveTime, 0, 0);
					worldTransform_.rotation_ += Vector3(0, 0, PI / moveTime / 2);
					if (moveTimer_ == 0) {
						pos[0]--;
						//ワープ処理
						if (map_->mapchip[pos[0]][pos[1]] == 4) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 5) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
						else if (map_->mapchip[pos[0]][pos[1]] == 5) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 4) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
						else if (map_->mapchip[pos[0]][pos[1]] == 6) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 7) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
					}
				}else if (map_->mapchip[pos[0] - 1][pos[1]] == 1) {
					//配列の先頭を削除
					inputMemory.erase(inputMemory.begin());
					//タイマーの初期化
					moveTimer_ = moveTime;
				}
			}
		//-----------------
			else if (inputMemory.front() == 3) {
				if (map_->mapchip[pos[0] + 1][pos[1]] != 1) {
					worldTransform_.translation_ += Vector3(2.0f/moveTime, 0, 0);
					worldTransform_.rotation_ += Vector3(0, 0, -PI / moveTime / 2);
					if (moveTimer_ == 0) {
						pos[0]++;
						//ワープ処理
						if (map_->mapchip[pos[0]][pos[1]] == 4) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 5) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
						else if (map_->mapchip[pos[0]][pos[1]] == 5) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 4) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
						else if (map_->mapchip[pos[0]][pos[1]] == 6) {
							for (int x = 0; x < map_->xElement; x++) {
								for (int z = 0; z < map_->zElement; z++) {
									if (map_->mapchip[x][z] == 7) {
										pos[0] = x;
										pos[1] = z;
										worldTransform_.translation_ = map_->worldTransform_[x][z].translation_;
									}
								}
							}
						}
					}
				}else if (map_->mapchip[pos[0] + 1][pos[1]] == 1) {
					//配列の先頭を削除
					inputMemory.erase(inputMemory.begin());
					//タイマーの初期化
					moveTimer_ = moveTime;
				}
			}
		}
	}
	else if (moveTimer_ < 0) {
	//入力されたキー情報が残っているなら
		if (!inputMemory.empty()) {
			//配列の先頭を削除
			inputMemory.erase(inputMemory.begin());
		}
		//タイマーの初期化
		moveTimer_ = moveTime;
		worldTransform_.rotation_ = Vector3(0, 0, 0);
	}


	//行列設定
	Matrix4 matScale = AffineScale(worldTransform_);
	Matrix4 matRotaX = AffineRotaX(worldTransform_);
	Matrix4 matRotaY = AffineRotaY(worldTransform_);
	Matrix4 matRotaZ = AffineRotaZ(worldTransform_);
	Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
	Matrix4 matTrans = AffineTrans(worldTransform_);
	//掛け
	worldTransform_.matWorld_ = AffineWorld(matScale, matRota, matTrans);

	//行列の転送
	worldTransform_.TransferMatrix();

}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

bool Player::isGole() {
	if (map_->mapchip[pos[0]][pos[1]] == 3) {
		return 1;
	}
	return 0;
}