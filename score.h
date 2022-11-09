//-----------------------------------------------------------------------------------------------------------
//
//�X�R�A�\��
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//--------------
//�}�N����`
//--------------
#define MAX_SCORE				(5)					//���������̔�(��)
#define SCORE_WIDTH				(30)
#define	SCORE_HEIGHT			(50)

//-----------------
//�v���g�^�C�v�錾
//-----------------
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int GetScore(void);

#endif // !_SCORE_H_
