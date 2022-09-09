#include"Map.h"
#include"Affine.h"

Map::~Map() {
	delete model_;
}

void Map::Initialize(int stage) {
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
		//�X�e�[�W���Ƃ̗v�f��
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
		//�}�b�v�`�b�v
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

		//�y��
			baseWorldTransform_[x][z].Initialize();
			//������0,0,0
			baseWorldTransform_[x][z].translation_ = Vector3(
				(x * modelSize) - (xElement / 2 * modelSize - modelSize / 2),
				-2,
				(z * modelSize) - (zElement / 2 * modelSize - modelSize / 2)
			);
			//�s��ݒ�
			matScale = AffineScale(baseWorldTransform_[x][z]);
			matRotaX = AffineRotaX(baseWorldTransform_[x][z]);
			matRotaY = AffineRotaY(baseWorldTransform_[x][z]);
			matRotaZ = AffineRotaZ(baseWorldTransform_[x][z]);
			matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
			matTrans = AffineTrans(baseWorldTransform_[x][z]);
			//�|��
			baseWorldTransform_[x][z].matWorld_ = AffineWorld(matScale, matRota, matTrans);

			//�s��̓]��
			baseWorldTransform_[x][z].TransferMatrix();
		}
	}

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
		for (int z = 1; z < zElement - 1; z++) {
			mapchip[x][z] = 0;
		}
	}


	if (stage == 0) {
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
	//------------------�X�e�[�W�Q------------------------------
	else if (stage == 1)
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

	//------------------�X�e�[�W3------------------------------
	if (stage == 2) {
		mapchip[1][2] = 2;
		mapchip[6][4] = 3;
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
		}
	}
}