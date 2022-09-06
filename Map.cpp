#include"Map.h"
#include"Affine.h"

Map::~Map() {
	delete model_;
}

void Map::Initialize() {
//------------------モデル生成-----------------
	std::string a = "cube";
	model_ = Model::CreateFromOBJ(a, false);
	modelSize = 2;

//------------------座標設定-------------------
	for (int y = 0; y < yElement; y++) {
		for (int x = 0; x < xElement; x++) {
			for (int z = 0; z < zElement; z++) {
				worldTransform_[x][y][z].Initialize();
				//左下が0,0,0
				worldTransform_[x][y][z].translation_ = Vector3(
				  (x * modelSize) - (xElement * modelSize / 2),
				  (y * modelSize) - (yElement * modelSize / 2),
				  (z * modelSize) - (zElement * modelSize / 2));
				//行列設定
				Matrix4 matScale = AffineScale(worldTransform_[x][y][z]);
				Matrix4 matRotaX = AffineRotaX(worldTransform_[x][y][z]);
				Matrix4 matRotaY = AffineRotaY(worldTransform_[x][y][z]);
				Matrix4 matRotaZ = AffineRotaZ(worldTransform_[x][y][z]);
				Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
				Matrix4 matTrans = AffineTrans(worldTransform_[x][y][z]);
				//掛け
				worldTransform_[x][y][z].matWorld_ = AffineWorld(matScale, matRota, matTrans);

				//行列の転送
				worldTransform_[x][y][z].TransferMatrix();
			}
		}
	}

//-----------マップチップの読み込み-------------
	//仮で直接書き込み
	for (int y = 0; y < yElement; y++) {
		for (int x = 0; x < xElement; x++) {
			for (int z = 0; z < zElement; z++) {
				mapchip[x][y][z] = 1;
			}
		}
	}

	//試しに特定の場所に穴をあける
	//左下が0,0,0
	for (int x = 1; x < xElement - 1; x++) {
		for (int z = 1; z < xElement - 1; z++) {
			mapchip[x][1][z] = 0;
		}
	}

//---------------------------------------

}

void Map::Update() {

}

void Map::Draw(ViewProjection viewProjection) {
	for (int y = 0; y < yElement; y++) {
		for (int x = 0; x < xElement; x++) {
			for (int z = 0; z < zElement; z++) {
				if (mapchip[x][y][z] == 1) {
					model_->Draw(worldTransform_[x][y][z], viewProjection);
				}
			}
		}
	}
}