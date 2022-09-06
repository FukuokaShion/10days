#include"Player.h"
#include"Affine.h"

Player::~Player() {
	delete model_;
}

void Player::Initialize() {
//------------------モデル生成-----------------
	std::string a = "player";
	model_ = Model::CreateFromOBJ(a, false);

//--------座標設定------------
	worldTransform_.Initialize();

}

void Player::Entry(Input* input) {
	//入力された方向を配列の後ろに追加していく
	if (input->TriggerKey(DIK_W)) {
		a.push_back(0);
	}
	if (input->TriggerKey(DIK_S)) {
		a.push_back(1);
	}
	if (input->TriggerKey(DIK_A)) {
		a.push_back(2);
	}
	if (input->TriggerKey(DIK_D)) {
		a.push_back(3);
	}
}

void Player::Move() {

	if (--moveTimer_ <= 0) {
		//入力されたキー情報が残っているなら
		if (a.empty() > 0) {
			//配列の先頭に入っている方向の処理
			if (a.front() == 0) {
				worldTransform_.translation_ += Vector3(0, 0, 2);
			}
			if (a.front() == 1) {
				worldTransform_.translation_ += Vector3(0, 0, -2);
			}
			if (a.front() == 2) {
				worldTransform_.translation_ += Vector3(-2, 0, 0);
			}
			if (a.front() == 3) {
				worldTransform_.translation_ += Vector3(2, 0, 0);
			}

			//配列の先頭を削除
			a.erase(a.begin());
			
			//タイマーの初期化
			moveTimer_ = moveTime;
		}
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