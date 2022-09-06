#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "DebugCamera.h"
#include <math.h>
#include "WorldTransform.h"
#include "Model.h"

#include "Map.h"
#include "Player.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	int scene;

	float PI = 3.1415;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	ViewProjection viewProjection_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//タイトル用
	uint32_t titlePic = 0;
	Sprite* title;

	//オブジェクト
	Map* map_ = nullptr;
	Player* player_ = nullptr;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	bool isDebugCamearaActive_ = false;

	//カメラ上方向の角度
	float viewAngle = 0.0f;
};
