//-----------------------------------------------------
//
//弾の処理
//Author;takano
//
//-----------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//-----------
//マクロ定義
//-----------
#define	MAX_BULLET						(600)					//弾の最大数
#define MYBULLET_SIZE					(5)						//バレットテクスチャの半分
#define BULLET_SIZE						(10)					//弾玉のサイズ
#define EFFECTBULLET_SIZE				(20)					//エフェクトのサイズ
#define EFFECT_RUNNINGMAN_SIZE			(50)					//ランニング弾専用のエフェクトサイズ
#define RUNNINGMAN_WIDTH				(100)					//ランニングマンの横幅
#define RUNNINGMAN_HEIGHT				(100)					//ランニングマンの高さ

//---------------
//弾構造体の定義
//---------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 move;						//移動量
	int nLife;								//寿命
	int nCounterAnim;						//アニメーションカウンター
	int nPatternAnim;						//アニメーションパターン
	int nCounterTime;						//とある弾の発射をカウントする変数
	float fRadius;							//半径
	bool bUse;								//弾が使用中か否か
	int nEp;								//爆弾
	int nTypeBullet;						//特殊弾
	int nPattern;							//誰が弾を使っているか
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
