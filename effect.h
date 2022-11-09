//-----------------------------------------------------
//
//エフェクト
//Author;takano
//
//-----------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

//-------------------------
//エフェクトの構造体定義
//-------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 move;						//移動量
	D3DXCOLOR col;							//色だよ
	float fRadius;							//半径
	int nCounterAnim;						//アニメーションカウンター
	int nPatternAnim;						//アニメーションパターン
	int nLife;								//ライフ
	bool bUse;								//弾使用中か否か
}EFFECT;

//-------------------------
//プロトタイプ宣言
//-------------------------
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col,float fRadius,int nLife);
EFFECT *GetEffect(void);

#endif // !_EFFECT_H_


