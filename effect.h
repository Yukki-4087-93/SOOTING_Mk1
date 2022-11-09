//-----------------------------------------------------
//
//光ファイバーの処理
//Author;takanooooooooooo
//
//-----------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

//-------------------
//EFFECT構造体の定義
//-------------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 move;						//移動量
	D3DXCOLOR col;							//色だよ
	float fRadius;							//発勁だよ
	int nCounterAnim;						//アニメーシカウンター
	int nPatternAnim;						//アニメーシパターン
	int nLife;								//いのき
	bool bUse;								//爆弾薬使用中か否か
}EFFECT;

//-----------------
//プロトタイプ宣言
//-----------------
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col,float fRadius,int nLife);
EFFECT *GetEffect(void);

#endif // !_EFFECT_H_


