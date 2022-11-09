//----------------------------------------------------------------------------------------
//
//ランキング処理
//Author;takanoooooooomononononononononononononnnonononononononononononononononon
//
//----------------------------------------------------------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//-------------------------
//ランキングすこあのKZT
//-------------------------
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXCOLOR col;					//カラー
	int nScore;						//スコア
}RankScore;

//-----------------
//マクロ定義
//-----------------
#define MAX_RANK				(5)				//ランク数

//-----------------
//プロトタイプ宣言
//-----------------
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(int nScore);
int GetRanking(void);

#endif // !_RANKING_H_

