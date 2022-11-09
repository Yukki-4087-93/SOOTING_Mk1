//------------------------------------------------------
//
//BOSS
//Author;takanoooooooooooo
//
//------------------------------------------------------
#ifndef _BOSS_H_
#define _BOSS_H_
#include"main.h"

//------------
//�}�N����`
//------------
#define	MAX_BOSS			(1)							//�{�X�ő呕�U��
#define NUM_BOSS			(1)							//�{�X�̎��
#define BOSS_HISIZE			(200)						//�G�̐����͂̃T�C�Y�̔���(����)
#define BOSS_WDSIZE			(200)						//�G�̐����͂̃T�C�Y�̔���(��)

//-----------------------
//�G�����̏��
//-----------------------
typedef enum
{
	BOSSSTATE_APPEAR = 0,				//�o�����(�_��)
	BOSSSTATE_NORMAL,					//�ʏ���
	BOSSSTATE_DAMAGE,					//�_���[�W���
	BOSSSTATE_INVINCIBLE,				//���G
	BOSSSTATE_MAX
}BOSSSTATE;

//-----------------------
//�G�����̍\���̂̒�`
//-----------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 move;						//�ړ�
	int nType;								//���
	int nPattern;							//�s���p�^�[��
	BOSSSTATE state;						//���
	int nCounterState;						//��ԊǗ��J�E���^�[
	int nLife;								//�̗�
	bool bUse;								//�G����񂪎g�p�����ۂ�

}Boss;

//-----------------
//�v���g�^�C�v�錾
//-----------------
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int nType, int nPattern);
Boss *GetBoss(void);
void HitBoss(int nCntBoss, int nDamage);
int GetAliveBoss(void);

#endif // !_BOSS_H_
