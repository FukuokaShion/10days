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

	int stage;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	  //タイトル用
	uint32_t titlePic[2] = {};
	Sprite* title[2];
	int titlePicTimer = 60;
	int titlenum = 0;
	//ステージ選択用
	uint32_t selectStagePic[6] = {};
	Sprite* selectStage[6];
	Vector2 selectStageSize[6];
	Vector2 selectStagePos[6];
	int stageMax = 6;
	int selectTimer_;
	int selectTime = 60;
	int changeStage;

	//クリア画面用
	uint32_t clearPic = 0;
	Sprite* clear;
	uint32_t titleButtonPic = 0;
	Sprite* titileButton;
	uint32_t nextButtonPic = 0;
	Sprite* nextButton;
	uint32_t buttonSelectFramePic = 0;
	Sprite* buttonSelectFrame;
	int selectButton = 0;

	//オブジェクト
	Map* map_ = nullptr;
	Player* player_ = nullptr;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	bool isDebugCamearaActive_ = false;

	//カメラ上方向の角度
	float viewAngle = 0.0f;
};
