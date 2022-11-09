//------------------------------------------------------
//
//�G(�̐����͂𔭌��I)����
//Author;takanoooooooooooo
//
//------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include"main.h"

//------------
//�}�N����`
//------------
#define	MAX_ENEMY			(1280)						//�G�����ő呕�U��
#define NUM_ENEMY			(4)							//�G�����̎��
#define ENEMY_SIZE			(10)						//�G�̐����͂̃T�C�Y�̔���
#define ENEMY_MAXSIZE		(20)						//�G�̐����͂̃T�C�Y

//-----------------------
//�G�����̏��
//-----------------------
typedef enum
{
	ENEMYSTATE_NORMAL = 0,				//�ʏ���
	ENEMYSTATE_DAMAGE,					//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//-----------------------
//�G�����̍\���̂̒�`
//-----------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 move;						//�ړ�
	int nType;								//���
	int nPattern;							//�s���p�^�[��
	ENEMYSTATE state;						//���
	int nCounterState;						//��ԊǗ��J�E���^�[
	int nLife;								//�̗�
	bool bUse;								//�G����񂪎g�p�����ۂ�
	
}Enemy;

//-----------------
//�v���g�^�C�v�錾
//-----------------
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType,int nPattern);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
int GetAliveEnemy(void);

#endif // !_ENEMY_H_