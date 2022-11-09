//------------------------------------------------------
//
//エネミー
//Author;takano
//
//------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include"main.h"

//-----------------------
//マクロ定義
//-----------------------
#define	MAX_ENEMY			(1280)						//エネミー最大数
#define NUM_ENEMY			(4)							//エネミーの種類
#define ENEMY_SIZE			(10)						//エネミーのサイズの半分
#define ENEMY_MAXSIZE		(20)						//エネミーのサイズ

//-----------------------
//エネミーの状態
//-----------------------
typedef enum
{
	ENEMYSTATE_NORMAL = 0,				//通常状態
	ENEMYSTATE_DAMAGE,					//ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//-----------------------
//エネミーの構造体の定義
//-----------------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 move;						//移動
	int nType;								//種類
	int nPattern;							//行動パターン
	ENEMYSTATE state;						//状態
	int nCounterState;						//状態管理カウンター
	int nLife;								//体力
	bool bUse;								//エネミーが使用中か否か
	
}Enemy;

//-----------------------
//プロトタイプ宣言
//-----------------------
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType,int nPattern);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
int GetAliveEnemy(void);

#endif // !_ENEMY_H_