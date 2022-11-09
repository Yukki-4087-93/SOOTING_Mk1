//-----------------------------------------------------
//
//�e�̏���
//Author;takano
//
//-----------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//-----------
//�}�N����`
//-----------
#define	MAX_BULLET						(600)					//�e�̍ő吔
#define MYBULLET_SIZE					(5)						//�o���b�g�e�N�X�`���̔���
#define BULLET_SIZE						(10)					//�e�ʂ̃T�C�Y
#define EFFECTBULLET_SIZE				(20)					//�G�t�F�N�g�̃T�C�Y
#define EFFECT_RUNNINGMAN_SIZE			(50)					//�����j���O�e��p�̃G�t�F�N�g�T�C�Y
#define RUNNINGMAN_WIDTH				(100)					//�����j���O�}���̉���
#define RUNNINGMAN_HEIGHT				(100)					//�����j���O�}���̍���

//---------------
//�e�\���̂̒�`
//---------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 move;						//�ړ���
	int nLife;								//����
	int nCounterAnim;						//�A�j���[�V�����J�E���^�[
	int nPatternAnim;						//�A�j���[�V�����p�^�[��
	int nCounterTime;						//�Ƃ���e�̔��˂��J�E���g����ϐ�
	float fRadius;							//���a
	bool bUse;								//�e���g�p�����ۂ�
	int nEp;								//���e
	int nTypeBullet;						//����e
	int nPattern;							//�N���e���g���Ă��邩
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
