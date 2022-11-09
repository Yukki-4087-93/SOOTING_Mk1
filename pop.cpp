//-----------------------------------------------------------------------------------------------------------
//
//出現処理
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------
#include"pop.h"
#include"enemy.h"
#include"time.h"
#include"boss.h"
#include"sound.h"

//------------------------
//グローバル変数
//------------------------
int g_nPopCount;				//敵が何回出現したかカウントする変数

//-------------------------
//出現の初期化
//-------------------------
void InitPop(void)
{
	g_nPopCount = 0;
	int pTime = GetTime();

	SetEnemy(D3DXVECTOR3(880.0f, 180.0f, 0.0f), 1, 0);
	SetEnemy(D3DXVECTOR3(880.0f, 300.0f, 0.0f), 0, 0);
	SetEnemy(D3DXVECTOR3(880.0f, 400.0f, 0.0f), 2, 0);
	SetEnemy(D3DXVECTOR3(880.0f, 500.0f, 0.0f), 3, 0);

}

//-------------------------
//出現の更新
//-------------------------
void UpdatePop(void)
{
	int pAlive = GetAliveEnemy();
	//int nCountKillPop;
	int pTime = GetTime();
	Enemy *pEnemy = GetEnemy();

	if (pAlive <= 0)
	{
		if (pTime % 240 == 0)
		{
			if (g_nPopCount == 25)
			{
				//サウンドの停止
				StopSound();
				//サウンドの再生
				PlaySound(SOUND_LABEL_NO_NAME);
				SetBoss(D3DXVECTOR3(1200.0f, 400.0f, 0.0f), 0, 1);
				g_nPopCount++;
			}
			else if (g_nPopCount >= 15 && g_nPopCount < 25)
			{
				SetEnemy(D3DXVECTOR3(1200.0f, 50.0f, 0.0f), 0, 7);
				SetEnemy(D3DXVECTOR3(1200.0f, 170.0f, 0.0f), 1, 8);
				SetEnemy(D3DXVECTOR3(1200.0f, 290.0f, 0.0f), 2, 7);
				SetEnemy(D3DXVECTOR3(1200.0f, 310.0f, 0.0f), 3, 8);
				SetEnemy(D3DXVECTOR3(1200.0f, 430.0f, 0.0f), 0, 7);
				SetEnemy(D3DXVECTOR3(1200.0f, 550.0f, 0.0f), 1, 8);
				g_nPopCount++;
			}
			else if (g_nPopCount >= 5 && g_nPopCount < 15)
			{
				SetEnemy(D3DXVECTOR3(1200.0f, 100.0f, 0.0f), 1, 6);
				SetEnemy(D3DXVECTOR3(1200.0f, 250.0f, 0.0f), 2, 5);
				SetEnemy(D3DXVECTOR3(1200.0f, 200.0f, 0.0f), 3, 6);
				SetEnemy(D3DXVECTOR3(1200.0f, 300.0f, 0.0f), 0, 5);
				SetEnemy(D3DXVECTOR3(1200.0f, 400.0f, 0.0f), 1, 6);
				SetEnemy(D3DXVECTOR3(1200.0f, 500.0f, 0.0f), 2, 5);
				SetEnemy(D3DXVECTOR3(1200.0f, 350.0f, 0.0f), 3, 6);
				SetEnemy(D3DXVECTOR3(1200.0f, 450.0f, 0.0f), 0, 5);
				SetEnemy(D3DXVECTOR3(1200.0f, 550.0f, 0.0f), 1, 6);
				g_nPopCount++;
			}
			else if (g_nPopCount < 5)
			{
				SetEnemy(D3DXVECTOR3(880.0f, 180.0f, 0.0f), 1, 3);
				SetEnemy(D3DXVECTOR3(1200.0f, 300.0f, 0.0f), 0, 4);
				SetEnemy(D3DXVECTOR3(1200.0f, 400.0f, 0.0f), 2, 4);
				SetEnemy(D3DXVECTOR3(880.0f, 500.0f, 0.0f), 3, 1);
				g_nPopCount++;
			}
		}
	}
}