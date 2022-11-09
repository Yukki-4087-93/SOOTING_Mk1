//-----------------------------------------------------------------------------------------------------------
//
//�����Ȃ��ł���EP����
//Author;takanoooooooooooooooo
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _PLAYER_H_													//���̃}�N����`���Ȃ���Ȃ�������
#define _PLAYER_H_													//��d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

//-----------
//�}�N����`
//-----------
#define MAX_PLAYER			(1)							//�v���C���[�̍ő�l��
#define HI_PLAYER			(35)						//�v���C���[�̍���
#define WD_PLAYER			(35)						//�v���C���[�̕�
#define MINUS_PLAYERSIZE	(30)						//�v���C���[�̓����蔻��̍ۂɈ����v���C���[�̃T�C�Y

//-----------------------
//�G�����̏��
//-----------------------
typedef enum
{
	PLAYERSTATE_NORMAL = 0,				//�ʏ���
	PLAYERSTATE_DAMAGE,					//�_���[�W���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//-----------------------
//���̍\���̂̒�`
//-----------------------
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXVECTOR3 rot;							//�v���C���[����
	PLAYERSTATE state;							//���
	int nCounterState;							//��ԊǗ��J�E���^�[
	int nCountTimer;							//���ˏo�I����
	int nPlayerLife;							//���C�t
	float fLength;								//�Ίp���̃����O�����W
	float fAngle;								//�Ίp���̃e�B���_���X�̗�
	bool bUse;									//�킽���Ⴊ�g�p�����ۂ�
}Player;


//-----------------
//�v���g�^�C�v�錾
//-----------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void AddPlayer(int nAdd);
void HitPlayer(int nDamage);
Player *GetPlayer(void);

#endif // !PLAYER_H_
