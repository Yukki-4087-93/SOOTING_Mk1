//------------------------------------------------------------
//
//タイム情報
//Author;takanoooooooooooooooooooooo
//
//------------------------------------------------------------
#include"time.h"

//---------------
//グローバル変数
//---------------
int g_nTime;													//たぁいむ
int g_nEnemyTime;
int g_nEnmBulletTime;
int g_nBossTime;
int g_nOpenMyHart;

//---------------------
//たぁいむの初期化処理
//---------------------
void InitTime(void)
{
	g_nTime = 0;												//値を初期化
	g_nEnemyTime = 0;											//値を初期化
	g_nEnmBulletTime = 0;
	g_nBossTime = 0;											//値を初期化
	g_nOpenMyHart = 0;
}

//-------------
//Tの終了処理
//-------------
void UninitTime(void)
{
	
}

//-------------------
//たぁいむの更新処理
//-------------------
void UpdateTime(void)
{

}

//----------------
//Timeの描画処理
//----------------
void DrawTime(void)
{
	
}

//----------------
//taimの設定処理
//----------------
void SetTime(int nTime)
{
	g_nTime = nTime;
}

//----------------
//taimの設定処理2
//----------------
void SetEnemyTime(int nEnemyTime)
{
	g_nEnemyTime = nEnemyTime;
}

//----------------
//taimの設定処理3
//----------------
void SetEnmBulletTime(int nEnmBulletTime)
{
	g_nEnmBulletTime = nEnmBulletTime;
}

//----------------
//taimの設定処理4
//----------------
void SetBossTime(int nBossTime)
{
	g_nBossTime = nBossTime;
}

//----------------
//taimの設定処理5
//----------------
void SetLastHart(int nOpenMyHart)
{
	g_nOpenMyHart = nOpenMyHart;
}

//----------------
//taimの加算処理
//----------------
void AddTime(int nValue)
{
	g_nTime += nValue;
	g_nEnemyTime += nValue;
	g_nEnmBulletTime += nValue;
	g_nBossTime += nValue;
	g_nOpenMyHart += nValue;
}

//------------------
//タイムナゲット
//------------------
int GetTime(void)
{
	return g_nTime;
}

//------------------
//エネミナゲット
//------------------
int GetEnenyTime(void)
{
	return g_nEnemyTime;
}

//------------------
//エネミナゲット
//------------------
int GetEnmBulletTime(void)
{
	return g_nEnmBulletTime;
}

//------------------
//ボスナゲット
//------------------
int GetBossTime(void)
{
	return g_nBossTime;
}

//--------------------
//ラストショット
//--------------------
int GetOpenMyHart(void)
{
	return g_nOpenMyHart;
}