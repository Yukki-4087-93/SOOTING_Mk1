//-----------------------------------------------------------------------------------------------------------
//
//スコア表示
//Author;takanoooooooooooooooo
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//-----------------
//プロトタイプ宣言
//-----------------
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetTime(int nTime);
void SetEnemyTime(int nEnenyTime);
void SetEnmBulletTime(int nEnmBulletTime);
void SetBossTime(int nBossTime);
void SetLastHart(int nOpenMyHart);
void AddTime(int nValue);
int GetTime(void);
int GetEnenyTime(void);
int GetEnmBulletTime(void);
int GetBossTime(void);
int GetOpenMyHart(void);

#endif // !_TIME_H_
