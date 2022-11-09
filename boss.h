//------------------------------------------------------
//
//BOSS
//Author;takanoooooooooooo
//
//------------------------------------------------------
#ifndef _BOSS_H_
#define _BOSS_H_
#include"main.h"

//------------
//マクロ定義
//------------
#define	MAX_BOSS			(1)							//ボス最大装填数
#define NUM_BOSS			(1)							//ボスの種類
#define BOSS_HISIZE			(200)						//敵の潜水艦のサイズの半分(高さ)
#define BOSS_WDSIZE			(200)						//敵の潜水艦のサイズの半分(横)

//-----------------------
//敵ちゃんの状態
//-----------------------
typedef enum
{
	BOSSSTATE_APPEAR = 0,				//出現状態(点滅)
	BOSSSTATE_NORMAL,					//通常状態
	BOSSSTATE_DAMAGE,					//ダメージ状態
	BOSSSTATE_INVINCIBLE,				//無敵
	BOSSSTATE_MAX
}BOSSSTATE;

//-----------------------
//敵ちゃんの構造体の定義
//-----------------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 move;						//移動
	int nType;								//種類
	int nPattern;							//行動パターン
	BOSSSTATE state;						//状態
	int nCounterState;						//状態管理カウンター
	int nLife;								//体力
	bool bUse;								//敵ちゃんが使用中か否か

}Boss;

//-----------------
//プロトタイプ宣言
//-----------------
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int nType, int nPattern);
Boss *GetBoss(void);
void HitBoss(int nCntBoss, int nDamage);
int GetAliveBoss(void);

#endif // !_BOSS_H_
