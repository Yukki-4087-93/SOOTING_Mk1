//----------------------------------------------------------------------------------------
//
//�����L���O����
//Author;takano
//
//----------------------------------------------------------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//-------------------------
//�����L���O�̍\����
//-------------------------
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXCOLOR col;					//�J���[
	int nScore;						//�X�R�A
}RankScore;

//-------------------------
//�}�N����`
//-------------------------
#define MAX_RANK				(5)				//�����N��

//-------------------------
//�v���g�^�C�v�錾
//-------------------------
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(int nScore);
int GetRanking(void);

#endif // !_RANKING_H_

