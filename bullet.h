//-----------------------------------------------------
//
//弾の処理
//Author;takanooooooooooo
//
//-----------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//-----------
//マクロ定義
//-----------
#define	MAX_BULLET						(600)					//マガジン最大装填数
#define MYBULLET_SIZE					(5)						//バレットテクスチャの半分太くん
#define BULLET_SIZE						(10)					//弾玉のシンセサイザー
#define EFFECTBULLET_SIZE				(20)					//エフェクト効果のサイズ
#define EFFECT_RUNNINGMAN_SIZE			(50)					//ランニングガードマン専用エフェクトサイズ
#define RUNNINGMAN_WIDTH				(100)					//止まらないDBBの横幅
#define RUNNINGMAN_HEIGHT				(100)					//止まらないDBBの身長

//---------------
//弾構造体の定義
//---------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 move;						//移動量
	int nLife;								//寿命
	int nCounterAnim;						//アニメーシカウンター
	int nPatternAnim;						//アニメーシパターン
	int nCounterTime;						//魂射出！時間
	float fRadius;							//発勁(半径)だよ
	bool bUse;								//弾薬使用中か否か
	int nEp;								//爆弾
	int nTypeBullet;						//特殊弾
	int nPattern;							//誰が弾を使って入鹿
}BULLET;

//-----------------
//プロトタイプ宣言
//-----------------
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nEp,int nTypeBullet, int nPattern);
BULLET *GetBullet(void);

#endif // !_BULLET_H_
