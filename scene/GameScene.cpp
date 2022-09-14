#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include <random>
#include"Affine.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
	delete map_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	scene = 0;
	input_ = Input::GetInstance();
	//タイトル用
	titlePic[0] = TextureManager::Load("title1.png");
	title[0] = Sprite::Create(titlePic[0], { 0, 0 });

	titlePic[1] = TextureManager::Load("title2.png");
	title[1] = Sprite::Create(titlePic[1], { 0, 0 });
	//ステージ選択用
	stage = 0;

	selectStagePic[0] = TextureManager::Load("stage1.png");
	selectStage[0] = Sprite::Create(selectStagePic[0], { 0, 0 });
	selectStageSize[0] = Vector2(400, 400);
	selectStage[0]->SetSize(selectStageSize[0]);
	selectStagePos[0] = Vector2(1280 / 4 * 2 - selectStageSize[0].x / 2, 720 / 2 - selectStageSize[0].y / 2);
	selectStage[0]->SetPosition(selectStagePos[0]);

	selectStagePic[1] = TextureManager::Load("stage2.png");
	selectStage[1] = Sprite::Create(selectStagePic[1], { 0, 0 });
	selectStageSize[1] = Vector2(250, 250);
	selectStage[1]->SetSize(selectStageSize[1]);
	selectStagePos[1] = Vector2(1280 / 4 * 3 - selectStageSize[1].x / 2, 720 / 2 - selectStageSize[1].y / 2);
	selectStage[1]->SetPosition(selectStagePos[1]);


	selectStagePic[2] = TextureManager::Load("stage3.png");
	selectStage[2] = Sprite::Create(selectStagePic[2], { 0, 0 });
	selectStageSize[2] = Vector2(100, 100);
	selectStage[2]->SetSize(selectStageSize[2]);
	selectStagePos[2] = Vector2(1280 / 4 * 4 - selectStageSize[2].x / 2, 720 / 2 - selectStageSize[2].y / 2);
	selectStage[2]->SetPosition(selectStagePos[2]);


	selectStagePic[3] = TextureManager::Load("stage4.png");
	selectStage[3] = Sprite::Create(selectStagePic[3], { 0, 0 });
	selectStageSize[3] = Vector2(-50, -50);
	selectStage[3]->SetSize(selectStageSize[3]);
	selectStagePos[3] = Vector2(1280 / 4 * 5 - selectStageSize[3].x / 2, 720 / 2 - selectStageSize[3].y / 2);
	selectStage[3]->SetPosition(selectStagePos[3]);


	selectStagePic[4] = TextureManager::Load("stage5.png");
	selectStage[4] = Sprite::Create(selectStagePic[4], { 0, 0 });
	selectStageSize[4] = Vector2(-200, -200);
	selectStage[4]->SetSize(selectStageSize[4]);
	selectStagePos[4] = Vector2(1280 / 4 *6 - selectStageSize[4].x / 2, 720 / 2 - selectStageSize[4].y / 2);
	selectStage[4]->SetPosition(selectStagePos[4]);


	selectStagePic[5] = TextureManager::Load("stage6.png");
	selectStage[5] = Sprite::Create(selectStagePic[5], { 0, 0 });
	selectStageSize[5] = Vector2(-350, -350);
	selectStage[5]->SetSize(selectStageSize[5]);
	selectStagePos[5] = Vector2(1280 / 4 * 7 - selectStageSize[5].x / 2, 720 / 2 - selectStageSize[5].y / 2);
	selectStage[5]->SetPosition(selectStagePos[5]);

	selectTimer_ = 0;
	changeStage = 0;

	//クリア
	clearPic = TextureManager::Load("clear.png");
	clear = Sprite::Create(clearPic, { 0, 0 });
	titleButtonPic = TextureManager::Load("titleButton.png");
	titileButton = Sprite::Create(titleButtonPic, { 200, 500 });
	nextButtonPic = TextureManager::Load("nextButton.png");
	nextButton = Sprite::Create(nextButtonPic, { 840, 500 });
	buttonSelectFramePic= TextureManager::Load("buttonSelect.png");
	buttonSelectFrame= Sprite::Create(buttonSelectFramePic, titileButton->GetPosition());

	//-----カメラ設定-----
	{
		//カメラ始点座標を設定
		viewProjection_.eye = {0, 30, -15};
		//カメラの注視点座標設定
		viewProjection_.target = {0, 0, 0};
		//カメラの上方向ベクトル設定
		viewProjection_.up = {0.0f, 1.0f, 0.0f};
		//カメラ垂直方向視野角を設定
		//viewProjection_.fovAngleY = PI/4.0f;
		//アス比を設定
		//viewProjection_.aspectRatio = 1.0f;
		//ニアクリップ距離を設定
		//viewProjection_.nearZ = 52.0f;
		//ファークリップ距離を設定
		//viewProjection_.farZ = 53.0f;
		//ビュープロジェクションの初期化
		viewProjection_.Initialize();
	}

//----デバッグカメラ----
	debugCamera_ = new DebugCamera(1280, 720);

//----軸方向----
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

//---------オブジェクト----------
	//マップ
	map_ = new Map();
	map_->Initialize(stage);

	//プレイヤー
	player_ = new Player();
	player_->SetMap(map_);
	player_->Initialize();
}


void GameScene::Update() {

	if (scene == 0) {//タイトル
		titlePicTimer--;
		if (titlePicTimer <= 0) {
			titlePicTimer = 60;
			if (titlenum == 0) {
				titlenum = 1;
			}
			else if (titlenum == 1)
			{
				titlenum = 0;
			}
		}
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = 1;
		}
	}
	else if (scene == 1) {//ステージ選択

		if (--selectTimer_ < 0) {
			if (input_->TriggerKey(DIK_D)||input_->TriggerKey(DIK_RIGHTARROW)) {
				if (stage < stageMax-1) {
					stage++;
					changeStage = 1;
					selectTimer_ = selectTime;
				}
			}if (input_->TriggerKey(DIK_A) || input_->TriggerKey(DIK_LEFTARROW)) {
				if (stage > 0) {
					stage--;
					changeStage = 2;
					selectTimer_ = selectTime;
				}
			}
		}
		else {
			if (changeStage == 1) {
				for (int i = 0; i < stageMax; i++) {
					if (i < stage) {
						selectStageSize[i] -= Vector2(150.0f / selectTime, 150.0f / selectTime);
						selectStage[i]->SetSize(selectStageSize[i]);
						selectStagePos[i].y = 720.0f / 2.0f - selectStageSize[i].y / 2.0f;
						selectStagePos[i].x -= 1280.0f / 4.0f / selectTime - 1.125f;
						selectStage[i]->SetPosition(selectStagePos[i]);
					}
					else if (i >= stage) {
						selectStageSize[i] += Vector2(150.0f / selectTime, 150.0f / selectTime);
						selectStage[i]->SetSize(selectStageSize[i]);
						selectStagePos[i].y = 720.0f / 2.0f - selectStageSize[i].y / 2.0f;
						selectStagePos[i].x -= 1280.0f / 4.0f / selectTime + 1.125f;
						selectStage[i]->SetPosition(selectStagePos[i]);
					}
				}
			}
			else if (changeStage == 2) {
				for (int i = 0; i < stageMax; i++) {
					if (i > stage) {
						selectStageSize[i] -= Vector2(150.0f / selectTime, 150.0f / selectTime);
						selectStage[i]->SetSize(selectStageSize[i]);
						selectStagePos[i].y = 720.0f / 2.0f - selectStageSize[i].y / 2.0f;
						selectStagePos[i].x += 1280.0f / 4.0f / selectTime + 1.125f;
						selectStage[i]->SetPosition(selectStagePos[i]);
					}
					else if (i <= stage) {
						selectStageSize[i] += Vector2(150.0f / selectTime, 150.0f / selectTime);
						selectStage[i]->SetSize(selectStageSize[i]);
						selectStagePos[i].y = 720.0f / 2.0f - selectStageSize[i].y / 2.0f;
						selectStagePos[i].x += 1280.0f / 4.0f / selectTime - 1.125f;
						selectStage[i]->SetPosition(selectStagePos[i]);
					}
				}
			}
		}
		if (input_->TriggerKey(DIK_SPACE)) {
			map_->Initialize(stage);
			player_->SetMap(map_);
			player_->Initialize();
			scene = 2;
		}
	}
	else if (scene == 2) {//迷路覚える
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = 3;
		}

	}
	else if (scene == 3) {//入力
		player_->Entry(input_);

		if (input_->TriggerKey(DIK_SPACE)) {
			scene = 4;
		}
		if (input_->TriggerKey(DIK_R)) {
			map_->Initialize(stage);
			player_->SetMap(map_);
			player_->Initialize();
			scene = 2;
		}
	}
	else if (scene == 4) {//動く
		player_->Move();
		if (input_->TriggerKey(DIK_R)) {
			map_->Initialize(stage);
			player_->SetMap(map_);
			player_->Initialize();
			scene = 2;
		}
		if (player_->isGole() == true) {
			scene = 5;
		}
	}
	else if (scene == 5) {//クリア画面
		if (input_->TriggerKey(DIK_A) || input_->TriggerKey(DIK_LEFTARROW)) {
			selectButton = 0;
			buttonSelectFrame->SetPosition(titileButton->GetPosition());
		}
		if (stage != stageMax - 1) {
			if (input_->TriggerKey(DIK_D) || input_->TriggerKey(DIK_RIGHTARROW)) {
				selectButton = 1;
				buttonSelectFrame->SetPosition(nextButton->GetPosition());
			}
		}

		if (input_->TriggerKey(DIK_SPACE)) {
			if (selectButton == 0) {
				Initialize();
			}
			else if (selectButton == 1) {
				map_->Initialize(++stage);
				player_->SetMap(map_);
				player_->Initialize();
				scene = 2;
				selectButton = 0;
			}
		}
	}
	

//----------デバッグカメラ------------
	//デバッグカメラの起動
	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_P)) {
		if (isDebugCamearaActive_ == 0) {
			isDebugCamearaActive_ = 1;
		} else if (isDebugCamearaActive_ == 1) {
			isDebugCamearaActive_ = 0;
		}
	}
	#endif
	//デバックカメラの移動
	if (isDebugCamearaActive_ == 1) {
		//更新
		debugCamera_->Update();
		//デバッグカメラのビュー行列とプロジェクション行列をコピー
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//行列の転送
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
		viewProjection_.TransferMatrix();
	}
//---------------------------------------
}


void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	if (scene == 0) {
		

	} else if (scene == 2) {
		map_->StageDraw(viewProjection_);
		player_->Draw(viewProjection_);
	
	} else if (scene == 3) {
		player_->Draw(viewProjection_);
		map_->FrameDraw(viewProjection_);
	
	} else if (scene == 4) {
		map_->StageDraw(viewProjection_);
		player_->Draw(viewProjection_);

	}


	
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	if (scene == 0) {
		title[titlenum]->Draw();
	}

	if (scene == 1) {
		for (int i = 0; i < stageMax; i++) {
			selectStage[i]->Draw();
		}
	}

	if (scene == 5) {
		clear->Draw();
		titileButton->Draw();
		if (stage != stageMax - 1) {
			nextButton->Draw();
		}
		buttonSelectFrame->Draw();
	}


	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}