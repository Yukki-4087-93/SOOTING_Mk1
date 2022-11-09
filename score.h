//-----------------------------------------------------------------------------------------------------------
//
//スコア表示
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//--------------
//マクロ定義
//--------------
#define MAX_SCORE				(5)					//扱う数字の箱(個数)
#define SCORE_WIDTH				(30)
#define	SCORE_HEIGHT			(50)

//-----------------
//プロトタイプ宣言
//-----------------
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int GetScore(void);

#endif // !_SCORE_H_
