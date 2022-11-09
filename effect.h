//-----------------------------------------------------
//
//���t�@�C�o�[�̏���
//Author;takanooooooooooo
//
//-----------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

//-------------------
//EFFECT�\���̂̒�`
//-------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 move;						//�ړ���
	D3DXCOLOR col;							//�F����
	float fRadius;							//��������
	int nCounterAnim;						//�A�j���[�V�J�E���^�[
	int nPatternAnim;						//�A�j���[�V�p�^�[��
	int nLife;								//���̂�
	bool bUse;								//���e��g�p�����ۂ�
}EFFECT;

//-----------------
//�v���g�^�C�v�錾
//-----------------
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col,float fRadius,int nLife);
EFFECT *GetEffect(void);

#endif // !_EFFECT_H_


