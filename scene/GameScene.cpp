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
	titlePic = TextureManager::Load("title.png");
	title = Sprite::Create(titlePic, {0, 0});

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
	map_->Initialize();

	//プレイヤー
	player_ = new Player();
	player_->Initialize();
}


void GameScene::Update() {

	if (scene == 0) {
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = 1;
		}

	} else if (scene == 1) {
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = 2;
		}

	} else if (scene == 2) {
		player_->Entry(input_);

		if (input_->TriggerKey(DIK_SPACE)) {
			scene = 3;
		}
	
	} else if (scene == 3) {
		player_->Move();
	
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
		

	} else if (scene == 1) {
		map_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
	
	} else if (scene == 2) {
		player_->Draw(viewProjection_);
	
	} else if (scene == 3) {
		map_->Draw(viewProjection_);
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
		title->Draw();

	} else if (scene == 1) {


	} 


	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}