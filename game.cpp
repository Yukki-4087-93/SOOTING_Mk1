//-----------------------------------------------------------------------------------------
//
//	ゲーム画面
//	Author;takanoooooooooooooooooooooooooooooooooooooooo
//
//-----------------------------------------------------------------------------------------
#include"input.h"
#include"player.h"
#include"bullet.h"
#include"explosion.h"
#include"enemy.h"
#include"score.h"
#include"sound.h"
#include"time.h"
#include"bg.h"
#include"fade.h"
#include"effect.h"
#include"pause.h"
#include"pop.h"
#include"boss.h"
#include"life.h"

//---------------------------
//グローバル変数
//---------------------------
bool g_bPause = false;

//---------------------------
//ゲーム画面の初期化
//---------------------------
void InitGame(void)
{
	InitBG();					//背景の初期化
	InitPause();				//ポーズの初期化
	InitEffect();
	InitTime();					//タイムの初期化処理
	SetTime(0);					//たいむせっつ
	SetEnemyTime(0);			//たいむ窃盗
	SetEnmBulletTime(0);
	SetBossTime(0);
	SetLastHart(0);
	InitScore();				//スコアの初期化処理
	SetScore(0);				//スコアせっつ
	InitBullet();				//弾の初期化処理
	InitLife();
	InitPlayer();				//プレイヤーの初期化処理
	InitEnemy();				//敵ちゃんの初期化
	InitBoss();
	InitPop();
	InitExplosion();			//爆発の初期化
	g_bPause = false;
//	PlaySound(SOUND_LABEL_BATTLEMEETING_VER_2);
}

//---------------------------
//ゲーム画面の終了処理
//---------------------------
void UninitGame(void)
{
	//StopSound();
	UninitBG();				//終了処理(背景)
	UninitScore();			//終了処理(スコア)
	UninitBullet();			//終了処理（弾）
	UninitEffect();
	UninitEnemy();			//終了処理（敵ちゃん）
	UninitBoss();
	UninitLife();
	UninitPlayer();			//終了処理（プレイヤー）
	UninitExplosion();		//終了処理（爆発）
	UninitPause();
}

//---------------------------
//ゲーム画面の更新処理
//---------------------------
void UpdateGame(void)
{
	if (GetkeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_STRTE) == true || GetJoypadTrigger(JOYKEY_BACK) == true)
	{//Pキーとその他もろもろが押された
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		UpdateBG();					//BackGroundの更新処理
		UpdateScore();				//Scoreの更新処理
		UpdateLife();
		UpdatePlayer();				//playerの更新処理
		UpdateEnemy();				//Enemyの更新処理
		UpdateBoss();				//ボスの更新
		UpdatePop();				//敵出現の更新
		UpdateExplosion();			//Explosionの更新処理
		UpdateBullet();				//Bulletの更新処理
		UpdateEffect();
		AddTime(1);					//Timeの加算処理
		int pTime = GetTime();		//タイムのあああああああああ
		/*if (pTime >= 9360)
		{
			SetFade(MODE_RESULT);
		}*/
	}

	else if (g_bPause == true)
	{
		UpdatePause();
	}
}

//---------------------------
//ゲーム画面の描画
//---------------------------
void DrawGame(void)
{
	DrawBG();					//背景の描画処理
	DrawScore();				//スコアの描画処理
	DrawEnemy();				//敵ちゃんの描画処理
	DrawBoss();
	DrawPlayer();				//プレイヤーの描画処理
	DrawLife();
	DrawBullet();				//弾の描画処理
	DrawEffect();
	DrawExplosion();			//爆発描画処理
	if (g_bPause == true)
	{//ポーズなう
		DrawPause();
	}
}

//---------------------------
//ポーズの有効か否かを設定
//---------------------------
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}