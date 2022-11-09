//-----------------------------------------------------
//
//�e�̏���
//Author;takanooooooooooo
//
//-----------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//-----------
//�}�N����`
//-----------
#define	MAX_BULLET						(600)					//�}�K�W���ő呕�U��
#define MYBULLET_SIZE					(5)						//�o���b�g�e�N�X�`���̔���������
#define BULLET_SIZE						(10)					//�e�ʂ̃V���Z�T�C�U�[
#define EFFECTBULLET_SIZE				(20)					//�G�t�F�N�g���ʂ̃T�C�Y
#define EFFECT_RUNNINGMAN_SIZE			(50)					//�����j���O�K�[�h�}����p�G�t�F�N�g�T�C�Y
#define RUNNINGMAN_WIDTH				(100)					//�~�܂�Ȃ�DBB�̉���
#define RUNNINGMAN_HEIGHT				(100)					//�~�܂�Ȃ�DBB�̐g��

//---------------
//�e�\���̂̒�`
//---------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 move;						//�ړ���
	int nLife;								//����
	int nCounterAnim;						//�A�j���[�V�J�E���^�[
	int nPatternAnim;						//�A�j���[�V�p�^�[��
	int nCounterTime;						//���ˏo�I����
	float fRadius;							//����(���a)����
	bool bUse;								//�e��g�p�����ۂ�
	int nEp;								//���e
	int nTypeBullet;						//����e
	int nPattern;							//�N���e���g���ē���
}BULLET;

//-----------------
//�v���g�^�C�v�錾
//-----------------
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nEp,int nTypeBullet, int nPattern);
BULLET *GetBullet(void);

#endif // !_BULLET_H_
