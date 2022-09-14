#include"Map.h"
#include"Affine.h"

Map::~Map() {
	delete model_;
}

void Map::Initialize(int stage) {
	//------------------モデル生成-----------------
	std::string a = "cube";
	model_ = Model::CreateFromOBJ(a, false);
	modelSize = 2;


	std::string start = "start";
	startModel_ = Model::CreateFromOBJ(start, false);

	std::string gole = "gole";
	goleModel_ = Model::CreateFromOBJ(gole, false);

	std::string teleport = "teleport";
	teleportModel_ = Model::CreateFromOBJ(teleport, false);

	baseTexture = TextureManager::Load("base.png");

	teleportInTexture = TextureManager::Load("teleportIn.png");
	teleportOutTexture = TextureManager::Load("teleportOut.png");


	//------------------座標設定-------------------
		//ステージごとの要素数
	if (stage == 0) {
		xElement = 12;
		zElement = 12;
	}
	else if (stage == 1) {
		xElement = 14;
		zElement = 14;
	}
	else if (stage == 2) {
		xElement = 8;
		zElement = 6;
	}


	
	for (int x = 0; x < xElement; x++) {
		for (int z = 0; z < zElement; z++) {
		//マップチップ
			worldTransform_[x][z].Initialize();
			//左下が0,0,0
			worldTransform_[x][z].translation_ = Vector3(
				(x * modelSize) - (xElement / 2 * modelSize - modelSize / 2),
				0,
				(z * modelSize) - (zElement / 2 * modelSize - modelSize / 2)
			);
			//行列設定
			Matrix4 matScale = AffineScale(worldTransform_[x][z]);
			Matrix4 matRotaX = AffineRotaX(worldTransform_[x][z]);
			Matrix4 matRotaY = AffineRotaY(worldTransform_[x][z]);
			Matrix4 matRotaZ = AffineRotaZ(worldTransform_[x][z]);
			Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
			Matrix4 matTrans = AffineTrans(worldTransform_[x][z]);
			//掛け
			worldTransform_[x][z].matWorld_ = AffineWorld(matScale, matRota, matTrans);

			//行列の転送
			worldTransform_[x][z].TransferMatrix();

		//土台
			baseWorldTransform_[x][z].Initialize();
			//左下が0,0,0
			baseWorldTransform_[x][z].translation_ = Vector3(
				(x * modelSize) - (xElement / 2 * modelSize - modelSize / 2),
				-2,
				(z * modelSize) - (zElement / 2 * modelSize - modelSize / 2)
			);
			//行列設定
			matScale = AffineScale(baseWorldTransform_[x][z]);
			matRotaX = AffineRotaX(baseWorldTransform_[x][z]);
			matRotaY = AffineRotaY(baseWorldTransform_[x][z]);
			matRotaZ = AffineRotaZ(baseWorldTransform_[x][z]);
			matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
			matTrans = AffineTrans(baseWorldTransform_[x][z]);
			//掛け
			baseWorldTransform_[x][z].matWorld_ = AffineWorld(matScale, matRota, matTrans);

			//行列の転送
			baseWorldTransform_[x][z].TransferMatrix();
		}
	}

	//------------------座標設定-------------------
		//ステージごとの要素数
	if (stage == 0) {
		xElement = 8;
		zElement = 6;

	}
	else if (stage == 1) {
		xElement = 8;
		zElement = 8;
	}
	else if (stage == 2) {
		xElement = 10;
		zElement = 10;
	}
	else if (stage == 3) {
		xElement = 12;
		zElement = 12;
	}
	else if (stage == 4) {
		xElement = 12;
		zElement = 12;
	}
	else if (stage == 5) {
		xElement = 16;
		zElement = 16;
	}



	for (int x = 0; x < xElement; x++) {
		for (int z = 0; z < zElement; z++) {
			//マップチップ
			worldTransform_[x][z].Initialize();
			//左下が0,0,0
			worldTransform_[x][z].translation_ = Vector3(
				(x * modelSize) - (xElement / 2 * modelSize - modelSize / 2),
				0,
				(z * modelSize) - (zElement / 2 * modelSize - modelSize / 2)
			);
			//行列設定
			Matrix4 matScale = AffineScale(worldTransform_[x][z]);
			Matrix4 matRotaX = AffineRotaX(worldTransform_[x][z]);
			Matrix4 matRotaY = AffineRotaY(worldTransform_[x][z]);
			Matrix4 matRotaZ = AffineRotaZ(worldTransform_[x][z]);
			Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
			Matrix4 matTrans = AffineTrans(worldTransform_[x][z]);
			//掛け
			worldTransform_[x][z].matWorld_ = AffineWorld(matScale, matRota, matTrans);

			//行列の転送
			worldTransform_[x][z].TransferMatrix();

			//土台
			baseWorldTransform_[x][z].Initialize();
			//左下が0,0,0
			baseWorldTransform_[x][z].translation_ = Vector3(
				(x * modelSize) - (xElement / 2 * modelSize - modelSize / 2),
				-2,
				(z * modelSize) - (zElement / 2 * modelSize - modelSize / 2)
			);
			//行列設定
			matScale = AffineScale(baseWorldTransform_[x][z]);
			matRotaX = AffineRotaX(baseWorldTransform_[x][z]);
			matRotaY = AffineRotaY(baseWorldTransform_[x][z]);
			matRotaZ = AffineRotaZ(baseWorldTransform_[x][z]);
			matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
			matTrans = AffineTrans(baseWorldTransform_[x][z]);
			//掛け
			baseWorldTransform_[x][z].matWorld_ = AffineWorld(matScale, matRota, matTrans);

			//行列の転送
			baseWorldTransform_[x][z].TransferMatrix();
		}
	}

	//-----------マップチップの読み込み-------------
		//仮で直接書き込み
	for (int x = 0; x < xElement; x++) {
		for (int z = 0; z < zElement; z++) {
			mapchip[x][z] = 1;
		}
	}


	//試しに特定の場所に穴をあける
	//左下が0,0,0
	//1壁 2スタート 3ゴール 4ワープ
	for (int x = 1; x < xElement - 1; x++) {
		for (int z = 1; z < zElement - 1; z++) {
			mapchip[x][z] = 0;
		}
	}


	if (stage == 0) {
		mapchip[1][2] = 2;
		mapchip[6][4] = 3;

	}
	//---------------ステージ2----------------------
	if (stage == 1) {
		mapchip[6][1] = 2;
		mapchip[1][6] = 3;
		mapchip[2][2] = 1;
		mapchip[2][3] = 1;
		mapchip[2][4] = 1;
		mapchip[2][5] = 1;
		mapchip[2][6] = 1;
		mapchip[4][1] = 1;
		mapchip[4][2] = 1;
		mapchip[4][3] = 1;
		mapchip[4][4] = 1;
		mapchip[4][5] = 1;
	}
	//----------------ステージ3-----------------------
	if (stage == 2) {
		mapchip[1][1] = 2;
		mapchip[4][4] = 3;
		mapchip[3][3] = 1;
		mapchip[3][4] = 1;
		mapchip[3][5] = 1;
		mapchip[4][3] = 1;
		mapchip[5][3] = 1;
		mapchip[5][4] = 1;
		mapchip[5][5] = 1;
	}
	//------------------ステージ4------------------------------
	else if (stage == 3)
	{
		mapchip[1][1] = 2;
		mapchip[9][10] = 3;

		mapchip[1][7] = 1;
		mapchip[2][7] = 1;
		mapchip[4][7] = 1;
		mapchip[5][7] = 1;
		mapchip[6][7] = 1;
		mapchip[7][7] = 1;
		mapchip[8][7] = 1;
		mapchip[9][7] = 1;
		mapchip[10][7] = 1;

		mapchip[1][3] = 1;
		mapchip[2][3] = 1;
		mapchip[3][3] = 1;
		mapchip[4][3] = 1;
		mapchip[5][3] = 1;
		mapchip[7][3] = 1;
		mapchip[8][3] = 1;
		mapchip[9][3] = 1;
		mapchip[10][3] = 1;
	}

	//------------------ステージ3------------------------------
	if (stage == 4) {

		mapchip[4][1] = 1;
		mapchip[4][2] = 1;
		mapchip[4][3] = 1;
		mapchip[4][4] = 1;

		mapchip[1][4] = 1;

		mapchip[1][7] = 1;
		mapchip[2][7] = 1;
		mapchip[3][7] = 1;
		mapchip[4][7] = 1;
		mapchip[5][7] = 1;
		mapchip[6][7] = 1;
		mapchip[7][7] = 1;
		mapchip[8][7] = 1;
		mapchip[9][7] = 1;
		mapchip[10][7] = 1;

		mapchip[1][10] = 1;
		mapchip[2][10] = 1;
		mapchip[3][10] = 1;
		mapchip[4][10] = 1;
		mapchip[5][10] = 1;

		mapchip[1][3] = 2;
		mapchip[9][10] = 3;


		mapchip[1][9] = 4;
		mapchip[10][1] = 5;
	}
	//--------------ステージ６----------------
	if (stage == 5) {
		mapchip[1][1] = 2;
		mapchip[14][14] = 3;
		mapchip[13][13] = 1;
		mapchip[13][14] = 1;
		mapchip[14][11] = 1;
		mapchip[13][11] = 1;
		mapchip[12][11] = 1;
		mapchip[12][13] = 1;
		mapchip[11][11] = 1;
		mapchip[10][11] = 1;
		mapchip[10][12] = 1;
		mapchip[10][13] = 1;

		mapchip[6][2] = 1;
		mapchip[6][3] = 1;
		mapchip[6][4] = 1;
		mapchip[6][5] = 1;
		mapchip[6][6] = 1;
		mapchip[6][7] = 1;
		mapchip[6][8] = 1;
		mapchip[6][9] = 1;
		mapchip[6][10] = 1;
		mapchip[6][11] = 1;
		mapchip[6][12] = 1;
		mapchip[6][13] = 1;
		mapchip[6][14] = 1;

		mapchip[3][1] = 1;
		mapchip[3][2] = 1;
		mapchip[3][3] = 1;
		mapchip[3][4] = 1;
		mapchip[3][5] = 1;
		mapchip[3][6] = 1;
		mapchip[3][7] = 1;
		mapchip[3][8] = 1;
		mapchip[3][9] = 1;
		mapchip[3][10] = 1;
		mapchip[3][11] = 1;
		mapchip[3][12] = 1;
		mapchip[3][13] = 1;

		mapchip[8][11] = 1;
		mapchip[7][11] = 1;
		mapchip[8][9] = 1;
		mapchip[7][9] = 1;
		mapchip[9][9] = 1;
		mapchip[10][9] = 1;
		mapchip[11][9] = 1;
		mapchip[12][9] = 1;
		mapchip[13][9] = 1;
		mapchip[14][9] = 1;

		mapchip[14][10] = 4;
		mapchip[10][5] = 5;
		mapchip[9][7] = 1;
		mapchip[9][6] = 1;
		mapchip[9][5] = 1;
		mapchip[9][4] = 1;
		mapchip[9][3] = 1;
		mapchip[9][2] = 1;
		mapchip[9][1] = 1;
		mapchip[11][5] = 1;
		mapchip[10][6] = 1;

		mapchip[7][10] = 6;
		mapchip[1][5] = 7;
	}

	//---------------------------------------

}


void Map::Update() {

}


void Map::FrameDraw(ViewProjection viewProjection) {
	for (int x = 0; x < xElement; x++) {
		for (int z = 0; z < zElement; z++) {
			model_->Draw(baseWorldTransform_[x][z], viewProjection, baseTexture);
		}
	}
	for (int x = 0; x < xElement; x++) {
		model_->Draw(worldTransform_[x][0], viewProjection);
		model_->Draw(worldTransform_[x][zElement - 1], viewProjection);
	}
	for (int z = 0; z < zElement; z++) {
		model_->Draw(worldTransform_[0][z], viewProjection);
		model_->Draw(worldTransform_[xElement - 1][z], viewProjection);
	}

}

void Map::StageDraw(ViewProjection viewProjection) {


	for (int x = 0; x < xElement; x++) {
		for (int z = 0; z < zElement; z++) {
			model_->Draw(baseWorldTransform_[x][z], viewProjection,baseTexture);

			if (mapchip[x][z] == 1) {
				model_->Draw(worldTransform_[x][z], viewProjection);
			}
			else if (mapchip[x][z] == 2) {
				startModel_->Draw(worldTransform_[x][z], viewProjection);
			}
			else if (mapchip[x][z] == 3) {
				goleModel_->Draw(worldTransform_[x][z], viewProjection);
			}
			else if (mapchip[x][z] == 4 || mapchip[x][z] == 5) {
				teleportModel_->Draw(worldTransform_[x][z], viewProjection);
			}
			else if (mapchip[x][z] == 6) {
				teleportModel_->Draw(worldTransform_[x][z], viewProjection,teleportInTexture);
			}
			else if (mapchip[x][z] == 7) {
				teleportModel_->Draw(worldTransform_[x][z], viewProjection,teleportOutTexture);
			}
		}
	}
}