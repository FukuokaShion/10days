#include"Map.h"
#include"Affine.h"

Map::~Map() {
	delete model_;
}

void Map::Initialize() {
//------------------���f������-----------------
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

//------------------���W�ݒ�-------------------
	//�}�b�v�`�b�v
	for (int x = 0; x < xElement; x++) {
		for (int z = 0; z < zElement; z++) {
			worldTransform_[x][z].Initialize();
			//������0,0,0
			worldTransform_[x][z].translation_ = Vector3(
			  (x * modelSize) - (xElement / 2 * modelSize - modelSize / 2),
				0,
			  (z * modelSize) - (zElement / 2 * modelSize - modelSize / 2)
				);
			//�s��ݒ�
			Matrix4 matScale = AffineScale(worldTransform_[x][z]);
			Matrix4 matRotaX = AffineRotaX(worldTransform_[x][z]);
			Matrix4 matRotaY = AffineRotaY(worldTransform_[x][z]);
			Matrix4 matRotaZ = AffineRotaZ(worldTransform_[x][z]);
			Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
			Matrix4 matTrans = AffineTrans(worldTransform_[x][z]);
			//�|��
			worldTransform_[x][z].matWorld_ = AffineWorld(matScale, matRota, matTrans);

			//�s��̓]��
			worldTransform_[x][z].TransferMatrix();
		}
	}
	
	//�y��
	baseWorldTransform_.Initialize();
	baseWorldTransform_.scale_ = Vector3(xElement, 1, zElement);
	baseWorldTransform_.translation_ = Vector3(0, -2, 0);
	//�s��ݒ�
	Matrix4 matScale = AffineScale(baseWorldTransform_);
	Matrix4 matRotaX = AffineRotaX(baseWorldTransform_);
	Matrix4 matRotaY = AffineRotaY(baseWorldTransform_);
	Matrix4 matRotaZ = AffineRotaZ(baseWorldTransform_);
	Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
	Matrix4 matTrans = AffineTrans(baseWorldTransform_);
	//�|��
	baseWorldTransform_.matWorld_ = AffineWorld(matScale, matRota, matTrans);

	//�s��̓]��
	baseWorldTransform_.TransferMatrix();

//-----------�}�b�v�`�b�v�̓ǂݍ���-------------
	//���Œ��ڏ�������
	for (int x = 0; x < xElement; x++) {
		for (int z = 0; z < zElement; z++) {
			mapchip[x][z] = 1;
		}
	}
	

	//�����ɓ���̏ꏊ�Ɍ���������
	//������0,0,0
	//1�� 2�X�^�[�g 3�S�[�� 4���[�v
	for (int x = 1; x < xElement - 1; x++) {
		for (int z = 1; z < xElement - 1; z++) {
			mapchip[x][z] = 0;
		}
	}

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

	mapchip[1][1] = 2;
	mapchip[9][10] = 3;


	mapchip[1][9] = 4;
	mapchip[10][1] = 5;


//---------------------------------------

}

void Map::Update() {

}


void Map::FrameDraw(ViewProjection viewProjection) {
	model_->Draw(baseWorldTransform_, viewProjection, baseTexture);
	for (int x = 0; x < xElement; x++) {
		model_->Draw(worldTransform_[x][0], viewProjection);
		model_->Draw(worldTransform_[x][zElement-1], viewProjection);
	}
	for (int z = 0; z < zElement; z++) {
		model_->Draw(worldTransform_[0][z], viewProjection);
		model_->Draw(worldTransform_[xElement-1][z], viewProjection);
	}

}

void Map::StageDraw(ViewProjection viewProjection){
	model_->Draw(baseWorldTransform_, viewProjection,baseTexture);


	for (int x = 0; x < xElement; x++) {
		for (int z = 0; z < zElement; z++) {
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
		}
	}
}