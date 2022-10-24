#include "GameScene.h"
#include <cassert>
#include <time.h>

using namespace DirectX;



GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;

	for (int i = 0; i < 50; i++)
	{
		delete object3d[i];
	}

	delete sprite1;
	delete sprite2;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	

	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");
	// テクスチャ2番に読み込み
	Sprite::LoadTexture(2, L"Resources/texture.png");

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成

	srand(time(nullptr));

	for (int i = 0; i < 50; i++)
	{
		randX = rand() % 41 - 20;
		randZ = rand() % 41 - 20;
		objPosition[i] = { randX , 0 ,randZ };
	}


	for (int i = 0; i < 50; i++)
	{
		object3d[i] = Object3d::Create();
	}

	for (int i = 0; i < 50; i++)
	{
		object3d[i]->Update();
	}


	for (int i = 0; i < 50; i++)
	{
		// 座標の変更を反映
		object3d[i]->SetPosition(objPosition[i]);
	}

	// 座標0,0にテクスチャ2番のsprite生成
	sprite1 = Sprite::Create(2, { 0,0 });

	// 座標500,500にテクスチャ2番のsprite生成
	sprite2 = Sprite::Create(2, { 500,500 }, { 1,0,0,1 }, { 0,0 }, false, true);
}

void GameScene::Update()
{
	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得

		//XMFLOAT3 position[50];

	/*	for (int i = 0; i < 50; i++)
		{
			objPosition[i] = object3d[i]->GetPosition();
		}*/

		for (int i = 0; i < 50; i++)
		{
			// 座標の変更を反映
			object3d[i]->SetPosition(objPosition[i]);
		}

		for (int i = 0; i < 50; i++)
		{
			// 移動後の座標を計算
			if (input->PushKey(DIK_UP)) { objPosition[i].y += 1.0f; }
			else if (input->PushKey(DIK_DOWN)) { objPosition[i].y -= 1.0f; }
			if (input->PushKey(DIK_RIGHT)) { objPosition[i].x += 1.0f; }
			else if (input->PushKey(DIK_LEFT)) { objPosition[i].x -= 1.0f; }
		}
		
	}

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { Object3d::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { Object3d::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { Object3d::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { Object3d::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	} 

	// スペースキーを押していたら
	if (input->PushKey(DIK_SPACE)) {
		// 現在の座標を取得
		XMFLOAT2 position = sprite1->GetPosition();
		// 移動後の座標を計算
		position.x += 1.0f;
		// 座標変更を繁栄
		sprite1->SetPosition(position);
	}

	for (int i = 0; i < 50; i++)
	{
		object3d[i]->Update();
	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	// 背景スプライト描画
	// spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	for (int i = 0; i < 50; i++)
	{
		object3d[i]->Draw();
	}

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	// sprite1->Draw();
	// sprite2->Draw();

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
